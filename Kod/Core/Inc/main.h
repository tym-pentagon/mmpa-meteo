/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "spi.h"
#include "stm32_adafruit_lcd.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct {
	uint16_t rok;
	uint8_t mesic;
	uint8_t den;

	uint8_t hodiny;
	uint8_t minuty;
	uint8_t sekundy;
} Cas;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define SIRKA_DISPLEJE							320
#define VYSKA_DISPLEJE							480

/* Barvy */
#define BARVA_POZADI 							RGB888TORGB565(0, 0, 0)
#define BARVA_UI_PRIMARNI 						RGB888TORGB565(18, 255, 3)
#define BARVA_UI_SEKUNDARNI 					RGB888TORGB565(255, 255, 255)
#define BARVA_UI_TERCIARNI 						RGB888TORGB565(112, 112, 112)
#define BARVA_VYBER 							RGB888TORGB565(255, 0, 255)
#define BARVA_UPOZORNENI 						RGB888TORGB565(253, 25, 2)
#define BARVA_PINU_SD_KARTY 					RGB888TORGB565(200, 166, 32)

/* Globální rozměry - platí pro všechny UI prvky */
#define PADDING									2
#define MEZERA									20 // Širší mezera mezi UI elementy
#define BORDER									1 // Pozn.: Slouží pouze pro výpočty, vykreslování širších borderů není implementováno
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
uint8_t stavSD(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SD_CS_Pin GPIO_PIN_4
#define SD_CS_GPIO_Port GPIOE
#define LCD_RS_Pin GPIO_PIN_0
#define LCD_RS_GPIO_Port GPIOF
#define ENC_SW_Pin GPIO_PIN_5
#define ENC_SW_GPIO_Port GPIOC
#define ENC_SW_EXTI_IRQn EXTI9_5_IRQn
#define LoRa_BUSY_Pin GPIO_PIN_1
#define LoRa_BUSY_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_7
#define LCD_D4_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_8
#define LCD_D5_GPIO_Port GPIOE
#define LCD_D6_Pin GPIO_PIN_9
#define LCD_D6_GPIO_Port GPIOE
#define LCD_D7_Pin GPIO_PIN_10
#define LCD_D7_GPIO_Port GPIOE
#define LoRa_RESET_Pin GPIO_PIN_12
#define LoRa_RESET_GPIO_Port GPIOE
#define LoRa_DIO1_Pin GPIO_PIN_15
#define LoRa_DIO1_GPIO_Port GPIOE
#define LoRa_DIO1_EXTI_IRQn EXTI15_10_IRQn
#define SPI2_NSS_Pin GPIO_PIN_12
#define SPI2_NSS_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOB
#define BME280_MODE_SELECT_Pin GPIO_PIN_10
#define BME280_MODE_SELECT_GPIO_Port GPIOD
#define LCD_D0_Pin GPIO_PIN_14
#define LCD_D0_GPIO_Port GPIOD
#define LCD_D1_Pin GPIO_PIN_15
#define LCD_D1_GPIO_Port GPIOD
#define SPI3_A0_Pin GPIO_PIN_2
#define SPI3_A0_GPIO_Port GPIOG
#define SPI3_A1_Pin GPIO_PIN_3
#define SPI3_A1_GPIO_Port GPIOG
#define SPI3_A2_Pin GPIO_PIN_4
#define SPI3_A2_GPIO_Port GPIOG
#define SPI3_NSS_Pin GPIO_PIN_15
#define SPI3_NSS_GPIO_Port GPIOA
#define LCD_D2_Pin GPIO_PIN_0
#define LCD_D2_GPIO_Port GPIOD
#define LCD_D3_Pin GPIO_PIN_1
#define LCD_D3_GPIO_Port GPIOD
#define LCD_RD_Pin GPIO_PIN_4
#define LCD_RD_GPIO_Port GPIOD
#define LCD_WR_Pin GPIO_PIN_5
#define LCD_WR_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_7
#define LCD_CS_GPIO_Port GPIOD
#define LCD_Reset_Pin GPIO_PIN_9
#define LCD_Reset_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */
#define GPS_UART_HANDLE huart2
#define LORA_SPI_HANDLE hspi2
#define BME280_SPI_HANDLE hspi3
#define SD_SPI_HANDLE hspi4
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
