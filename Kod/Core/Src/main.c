/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "fatfs.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32_adafruit_lcd.h"
#include "ssd1306.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h" // For va_list var arg functions
#include "stdbool.h"

/* Komunikace */
#include "lora.h"

/* Senzory */
#include "bme280.h"

/* Stránky */
#include "hlavni_menu.h"
#include "atmosfera.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
bool pripojeno = 1;
uint16_t ping = 9999;

Cas predchozi_cas = {2026, 4, 15, 14, 39, 2}; // Čas při předchozí aktualizace hodin
Cas cas = {2026, 4, 15, 14, 39, 2};

uint16_t predchozi_pozice_vyberu = 0;
uint16_t pozice_vyberu = 0;
uint16_t max_pozice_vyberu = 10;

int32_t teplota;
uint32_t vlhkost, tlak;

int32_t teplota_venku;
uint32_t vlhkost_venku, tlak_venku;

bool stisknuto = 0; // Zda bylo stisknuto tlačítko na rotačním enkodéru

/* Proměnné pro FatFs */
FATFS FatFs; 	// FatFs handle
FIL fil; 		// File handle
FRESULT fres;   // Result after operations

uint8_t predchozi_stav_promenne_sd_karta_pripojena = 2;
// Předchozí stav proměnné je nastaven mimo rozsah, protože proměnná ještě nebyla inicializována.

bool vyzkouseno_pripojeni_sd_karty = 0;
bool sd_karta_pripojena = 0;
uint32_t kapacita_sd_karty = 0; // KB
uint32_t zaplneni_sd_karty = 0; // KB

uint8_t strana = 0;

const char nazvy_mesicu[12][10] = {
	{0x6C, 0x65, 0x64, 0x6E, 0x61, 0x00},							// "ledna"
	{0xFA, 0x6E, 0x6F, 0x72, 0x61, 0x00},							// "února"
	{0x62, 0xF8, 0x65, 0x7A, 0x6E, 0x61, 0x00},						// "března"
	{0x64, 0x75, 0x62, 0x6E, 0x61, 0x00},							// "dubna"
	{0x6B, 0x76, 0xEC, 0x74, 0x6E, 0x61, 0x00},						// "května"
	{0xE8, 0x65, 0x72, 0x76, 0x6E, 0x61, 0x00},						// "června"
	{0xE8, 0x65, 0x72, 0x76, 0x65, 0x6E, 0x63, 0x65, 0x00},			// "července"
	{0x73, 0x72, 0x70, 0x6E, 0x61, 0x00},							// "srpna"
	{0x7A, 0xE1, 0xF8, 0xED, 0x00},									// "září"
	{0xF8, 0xED, 0x6A, 0x6E, 0x61, 0x00},							// "října"
	{0x6C, 0x69, 0x73, 0x74, 0x6F, 0x70, 0x61, 0x64, 0x75, 0x00},	// "listopadu"
	{0x70, 0x72, 0x6F, 0x73, 0x69, 0x6E, 0x63, 0x65, 0x00}			// "prosince"
};
/*
 * 0 - hlavní menu
 */

char debug[500];

extern Disk_drvTypeDef  disk;

extern bool can_send_data; // Zda LoRa může posílat data

uint8_t lora_data[DATA_LEN]; // Data pro odeslání

bool mereni = false; // Zda se MCU má ptát senzorů na aktuální hodnoty
// Měří se každou sekundu
// Omezení je z důvodu přehřívání senzorů
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */
void aktualizujCas(Cas *cas);
void aktualizujPoziciVyberu(void);
void tlacitkoStisknuto(void);
void pridatChecksum(uint8_t data[], size_t data_len);
void pripravitDataProOdeslani(void);
bool zkontrolovatChecksum(uint8_t data[], size_t data_len);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* Allow SD card remounting */
DSTATUS disk_reinitialize (
	BYTE pdrv				/* Physical drive number to identify the drive */
)
{
	return disk.drv[pdrv]->disk_initialize(disk.lun[pdrv]);
}

void aktualizujCas(Cas *cas) {
	/* Tato funkce se spustí každou sekundu, vždy aktualizuje proměnnou cas */
	cas->sekundy ++;

	if (cas->sekundy >= 60) {
		cas->sekundy = 0;
		cas->minuty ++;

		if (cas->minuty >= 60) {
			cas->minuty = 0;
			cas->hodiny ++;

			if (cas->hodiny >= 24) {
				cas->hodiny = 0;
				cas->den ++;

				if (
					(cas->den >= 31 && (		// Měsíce se 31 dny
						cas->mesic == 1 ||		// Leden
						cas->mesic == 3 ||		// Březen
						cas->mesic == 5 || 		// Květen
						cas->mesic == 7 ||		// Červenec
						cas->mesic == 8 ||		// Srpen
						cas->mesic == 10 ||		// Říjen
						cas->mesic == 12		// Prosinec
					)) ||
					(cas->den > 30 && (			// Měsíce se 30 dny
						cas->mesic == 4 ||		// Duben
						cas->mesic == 6 ||		// Červen
						cas->mesic == 9 || 		// Září
						cas->mesic == 11		// Listopad
					)) ||
					(cas->den >= 29 && cas->rok % 4 == 0 && cas->rok % 100 != 0 && cas->rok % 400 == 0) ||	// Únor v přestupném roku
					cas->den >= 28																			// Únor v nepřestupném roku
				) {
					cas->den = 0;
					cas->mesic ++;

					if (cas->mesic >= 12) {
						cas->mesic = 1;
						cas->rok ++;
					}
				}
			}
		}
	}
}

void aktualizujPoziciVyberu(void) {
	if (TIM3->CNT % 2 == 0 && TIM3->CNT != pozice_vyberu * 2) {
		predchozi_pozice_vyberu = pozice_vyberu;

		if (TIM3->CNT > 65000) { // Underflow
			TIM3->CNT = (max_pozice_vyberu + 1) * 2 - ((65536 - TIM3->CNT) % ((max_pozice_vyberu + 1) * 2));
		}

		if (TIM3->CNT > max_pozice_vyberu * 2) {
			TIM3->CNT = TIM3->CNT % ((max_pozice_vyberu + 1) * 2);
		}

		pozice_vyberu = TIM3->CNT / 2;

		if (strana == 0) {
			aktualizujPoziciVyberuVHlavnimMenu(predchozi_pozice_vyberu, pozice_vyberu);
		}

		/* Vypíše na debug displej */
		char pozice_vyberu_buffer[6];
		snprintf(pozice_vyberu_buffer, 6, "%d", pozice_vyberu);

		ssd1306_SetCursor(122, 0);
		ssd1306_WriteString(pozice_vyberu_buffer, &Terminus12Bold, 1);
		ssd1306_UpdateScreen();
	}
}

void tlacitkoStisknuto(void) {
	ssd1306_SetCursor(122, 13);
	ssd1306_WriteString("1", &Terminus12Bold, 1);
	ssd1306_UpdateScreen(); // Vykreslí na OLED displej

	if (strana == 0) {
		if (pozice_vyberu == 0) {
			strana = 1;
			vykresliStrankuAtmosfera(&predchozi_pozice_vyberu, &pozice_vyberu, &max_pozice_vyberu);
		}
	}
	else if (strana == 1) {
		if (pozice_vyberu == 0) {
			strana = 0;
			predchozi_stav_promenne_sd_karta_pripojena = 2; // Mimo rozsah, protože spodní lišta potřebuje znovu vykreslit
			vykresliHlavniMenu(pripojeno, ping, cas, &predchozi_pozice_vyberu, &pozice_vyberu, &max_pozice_vyberu, vyzkouseno_pripojeni_sd_karty);
		}
	}

	ssd1306_SetCursor(122, 13);
	ssd1306_WriteString("0", &Terminus12Bold, 1);
	ssd1306_UpdateScreen(); // Vykreslí na OLED displej
}

uint8_t stavSD(void) {
	/* Získá stav SD karty - zda je připojena, jakou má kapacitu a kolik je na ní volného místa */

	f_mount(NULL, "", 1); // Nejprve odpojí

	// 4. NOW initialize disk
	if (disk_reinitialize(0) != RES_OK) {
		vyzkouseno_pripojeni_sd_karty = 1;
		sd_karta_pripojena = 0; // SD karta je odpojena
	}
	else {
		fres = f_mount(&FatFs, "", 1); // 1 = mount now

		if (fres != FR_OK) {
			// Otevře filesystém
			vyzkouseno_pripojeni_sd_karty = 1;
			sd_karta_pripojena = 0; // SD karta je odpojena
		}
		else {
			vyzkouseno_pripojeni_sd_karty = 1;
			sd_karta_pripojena = 1; // SD karta je připojena

			// Získá statistiky o zaplnění úložiště
			DWORD free_clusters, free_sectors, total_sectors;

			FATFS* getFreeFs;

			fres = f_getfree("", &free_clusters, &getFreeFs);
			if (fres != FR_OK) {
				return 1; // Nelze přečíst údaje o zaplnění úložiště
			}

			// Formula comes from ChaN's documentation
			total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
			free_sectors = free_clusters * getFreeFs->csize;

			kapacita_sd_karty = (total_sectors / 2);
			zaplneni_sd_karty = (total_sectors / 2 - free_sectors / 2);
		}
	}

	if (strana == 0 && sd_karta_pripojena != predchozi_stav_promenne_sd_karta_pripojena) { // Pokud je uživatel v hlavním menu
		predchozi_stav_promenne_sd_karta_pripojena = sd_karta_pripojena;
		aktualizujStavSDKartyVHlavnimMenu(sd_karta_pripojena, kapacita_sd_karty, zaplneni_sd_karty);
	}

	return 0; // Funkce úspěšně skončila
}

void pridatChecksum(uint8_t data[], size_t data_len) {
	uint8_t crc = 0;

	for (size_t i = 0; i < data_len - 1; i ++) {
		crc ^= data[i];
	}

	data[data_len - 1] = crc;
}

void pripravitDataProOdeslani() {
	memset(lora_data, 0, DATA_LEN); // Vynuluje data pro odeslání

	lora_data[7] = (teplota >> 24) & 0xFF; // MSB
	lora_data[8]  = (teplota >> 16) & 0xFF;
	lora_data[9] = (teplota >> 8)  & 0xFF;
	lora_data[10] = teplota & 0xFF;         // LSB

	lora_data[11] = (vlhkost >> 24) & 0xFF; // MSB
	lora_data[12]  = (vlhkost >> 16) & 0xFF;
	lora_data[13] = (vlhkost >> 8)  & 0xFF;
	lora_data[14] = vlhkost & 0xFF;         // LSB

	lora_data[15] = (tlak >> 24) & 0xFF; // MSB
	lora_data[16]  = (tlak >> 16) & 0xFF;
	lora_data[17] = (tlak >> 8)  & 0xFF;
	lora_data[18] = tlak & 0xFF;         // LSB

	pridatChecksum(lora_data, DATA_LEN);

	LoRa_set_data(lora_data, sizeof(lora_data));
}

bool zkontrolovatChecksum(uint8_t data[], size_t data_len) {
	uint8_t crc = 0;

	for (size_t i = 0; i < data_len - 1; i ++) {
		crc ^= data[i];
	}

	if (data[data_len - 1] == crc) {
		return true; // Checksum sedí
	}
	else {
		return false; // Checksum nesedí
	}
}

void LoRa_Rx_callback(uint8_t data_received[], uint8_t len) {
	if (!zkontrolovatChecksum(data_received, len)) {
		// Checksum nesedí
		// TODO: Error handling
	}

	teplota_venku =
		(int32_t)(
			((uint32_t)data_received[7] << 24) |
			((uint32_t)data_received[8] << 16) |
			((uint32_t)data_received[9] << 8)  |
			((uint32_t)data_received[10])
		);

	vlhkost_venku =
		((uint32_t)data_received[11] << 24) |
		((uint32_t)data_received[12] << 16) |
		((uint32_t)data_received[13] << 8)  |
		((uint32_t)data_received[14]);

	tlak_venku =
		((uint32_t)data_received[15] << 24) |
		((uint32_t)data_received[16] << 16) |
		((uint32_t)data_received[17] << 8)  |
		((uint32_t)data_received[18]);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC3_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_SPI4_Init();
  MX_FATFS_Init();
  MX_TIM13_Init();
  MX_TIM2_Init();
  MX_SPI3_Init();
  MX_SPI2_Init();
  MX_TIM11_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  LoRa_init();

  HAL_ADC_Start(&hadc3);

  if (BSP_LCD_Init() != LCD_OK) {
  	Error_Handler(); // Inicializace LCD selhala
  	return 1;
  }

  HAL_TIM_Base_Start_IT(&htim11); // Inicializace timeru pro přerušení každou sekundu
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // Inicializace timeru k rotačnímu enkodéru
  TIM3->CNT = 0; // Počáteční vynulování

  ssd1306_Init(); // Inicializace OLED displeje

  /* Inicializace BME280 */
  if (BME280_Config(OSRS_16, OSRS_16, OSRS_16, MODE_NORMAL, T_SB_1000, IIR_16) != 0) {
	  Error_Handler();
  }

  /* Debug pozice výběru */
  char pozice_vyberu_text[] = {
	0x50, 0x6F, 0x7A, 0x69, 0x63, 0x65, 0x20, 0x76, 0xFD, 0x62, 0xEC, 0x72, 0x75, 0x3A, 0x00,  // "Pozice výběru:"
  };

  ssd1306_SetCursor(0, 0);
  ssd1306_WriteString(pozice_vyberu_text, &Terminus12Normal, 1);

  ssd1306_SetCursor(122, 0);
  ssd1306_WriteString("0", &Terminus12Bold, 1); // Počáteční pozice výběru je vždy 0

  /* Debug stisknuto */
  char stisknuto_text[] = {
    0x53, 0x74, 0x69, 0x73, 0x6B, 0x6E, 0x75, 0x74, 0x6F, 0x3A, 0x00,  // "Stisknuto:"
  };

  ssd1306_SetCursor(0, 13);
  ssd1306_WriteString(stisknuto_text, &Terminus12Normal, 1);

  ssd1306_SetCursor(122, 13);
  ssd1306_WriteString("0", &Terminus12Bold, 1);

  ssd1306_UpdateScreen(); // Vykreslí na OLED displej

  vykresliHlavniMenu(pripojeno, ping, cas, &predchozi_pozice_vyberu, &pozice_vyberu, &max_pozice_vyberu, vyzkouseno_pripojeni_sd_karty);

  stavSD();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (mereni) {
		  BME280_Measure(&teplota, &vlhkost, &tlak);
		  pripravitDataProOdeslani();
		  mereni = false;
	  }

	  LoRa_loop();

	  aktualizujPoziciVyberu();
	  if (stisknuto == 1) {
		  stisknuto = 0;
		  tlacitkoStisknuto();
	  }

	  stavSD();

	  if (strana == 0) { // Hlavní menu
		  aktualizujHodinyVHlavnimMenu(cas, &predchozi_cas);
	  }
	  if (strana == 1) { // Atmosféra
		  aktualizujHodnotyNaStranceAtmosfera(teplota, vlhkost, tlak, teplota_venku, vlhkost_venku, tlak_venku);
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == ENC_SW_Pin) {
		stisknuto = 1;
	}
	if (GPIO_Pin == LoRa_DIO1_Pin) {
		LoRa_DIO1_interrupt_handler();
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2) {
		LoRa_TIM2_interrupt_handler();
	}

    if (htim->Instance == TIM11) {
        // Kód, který se spustí každou sekundu:
    	mereni = true;
    	aktualizujCas(&cas);
    }
}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
