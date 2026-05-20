#include "bme280.h"
#include "main.h"

/* --- Koeficienty pro kalibraci --- */
int16_t dig_T2, dig_T3;
uint16_t dig_T1, dig_P1;
int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
uint8_t  dig_H1;
int16_t  dig_H2;
uint8_t  dig_H3;
int16_t  dig_H4;
int16_t  dig_H5;
int8_t   dig_H6;

int32_t t_fine;

int32_t tRaw, pRaw, hRaw;
float Temperature, Pressure, Humidity;

uint8_t config[2]; // Data, která se posílají pomocí funkce HAL_SPI_Transmit()
HAL_StatusTypeDef status; // Stavový kód SPI přenosu

uint8_t dummy = 0xFF;

/* --- Funkce --- */
/* Zdroj: https://controllerstech.com/interface-bme280-with-stm32/ [upraveno] */
void BME280_Set_SPI_Mode(void) {
	/* Přepne do SPI módu */
	HAL_GPIO_WritePin(BME280_MODE_SELECT_GPIO_Port, BME280_MODE_SELECT_Pin, 0);

	/* Vybere SPI adresu */
	HAL_GPIO_WritePin(BME280_A0_GPIO_Port, BME280_A0_Pin, BME280_A0_Status);
	HAL_GPIO_WritePin(BME280_A1_GPIO_Port, BME280_A1_Pin, BME280_A1_Status);
	HAL_GPIO_WritePin(BME280_A2_GPIO_Port, BME280_A2_Pin, BME280_A2_Status);

	HAL_GPIO_WritePin(BME280_NSS_GPIO_Port, BME280_NSS_Pin, 0); // SPI_NSS LOW

	HAL_Delay(10);

	HAL_GPIO_WritePin(BME280_MODE_SELECT_GPIO_Port, BME280_MODE_SELECT_Pin, 1);
	HAL_GPIO_WritePin(BME280_NSS_GPIO_Port, BME280_NSS_Pin, 1); // SPI_NSS HIGH

	HAL_Delay(10);
}

void BME280_NSS_Low(void) {
	/* Vybere SPI adresu */
	HAL_GPIO_WritePin(BME280_A0_GPIO_Port, BME280_A0_Pin, BME280_A0_Status);
	HAL_GPIO_WritePin(BME280_A1_GPIO_Port, BME280_A1_Pin, BME280_A1_Status);
	HAL_GPIO_WritePin(BME280_A2_GPIO_Port, BME280_A2_Pin, BME280_A2_Status);

	HAL_GPIO_WritePin(BME280_NSS_GPIO_Port, BME280_NSS_Pin, 0);
}

void BME280_NSS_High(void) {
	HAL_GPIO_WritePin(BME280_NSS_GPIO_Port, BME280_NSS_Pin, 1);
}

static int BME280_ReadRaw(void) {
	uint8_t raw_data[LENGTH_REG_OUTPUT];
	uint8_t chip_ID;

	// Check the chip ID before reading
	config[0] = REG_ID | 0x80; // Pro čtení

	BME280_NSS_Low();
	HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 1, 10); // Odešle požadavek pro zobrazení ID
	HAL_SPI_TransmitReceive(&BME280_SPI_HANDLE, &dummy, &chip_ID, 1, 10);
	BME280_NSS_High();

	if (chip_ID == EXPECTED_ID) {
		// Read the registers 0xF7 to 0xFE
		config[0] = START_REG_OUTPUT | 0x80; // Pro čtení

		BME280_NSS_Low();
		HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 1, 10);
		HAL_SPI_TransmitReceive(&BME280_SPI_HANDLE, &dummy, raw_data, LENGTH_REG_OUTPUT, HAL_MAX_DELAY);
		BME280_NSS_High();

		/* Calculate the Raw data for the parameters
		 * Here the Pressure and Temperature are in 20 bit format
		 */
		pRaw = (raw_data[0] << 12) | (raw_data[1] << 4) | (raw_data[2] >> 4);
		tRaw = (raw_data[3] << 12) | (raw_data[4] << 4) | (raw_data[5] >> 4);
		hRaw = (raw_data[6] << 8) | (raw_data[7]);

		return 0; // Success
	}

	else return 1;  // Error NUM for debug
}

static int TrimRead(void) {
	uint8_t trimdata[LENGTH_REG_CALIB + LENGTH_REG_CALIB_2];

	// Read NVM from 0x88 to 0xA1 (25 bytes)
	config[0] = START_REG_CALIB | 0x80; // Pro čtení

	BME280_NSS_Low();
	HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 1, 10);
	status = HAL_SPI_TransmitReceive(&BME280_SPI_HANDLE, &dummy, trimdata, LENGTH_REG_CALIB, HAL_MAX_DELAY);
	BME280_NSS_High();

	if (status != HAL_OK) {
		return 1;  // Error NUM for debug
	}

	// Read NVM from 0xE1 to 0xE7 (7 bytes)
	config[0] = START_REG_CALIB_2 | 0x80; // Pro čtení

	BME280_NSS_Low();
	HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 1, 10);
	status = HAL_SPI_TransmitReceive(&BME280_SPI_HANDLE, &dummy, trimdata + 25, LENGTH_REG_CALIB_2, HAL_MAX_DELAY);
	BME280_NSS_High();

	if (status != HAL_OK) {
		return 2;  // Error NUM for debug
	}

	// Temperature coefficients
	dig_T1 = (uint16_t)(trimdata[1] << 8 | trimdata[0]);
	dig_T2 = (int16_t)(trimdata[3] << 8 | trimdata[2]);
	dig_T3 = (int16_t)(trimdata[5] << 8 | trimdata[4]);

	// Pressure coefficients
	dig_P1 = (uint16_t)(trimdata[7] << 8 | trimdata[6]);
	dig_P2 = (int16_t)(trimdata[9] << 8 | trimdata[8]);
	dig_P3 = (int16_t)(trimdata[11] << 8 | trimdata[10]);
	dig_P4 = (int16_t)(trimdata[13] << 8 | trimdata[12]);
	dig_P5 = (int16_t)(trimdata[15] << 8 | trimdata[14]);
	dig_P6 = (int16_t)(trimdata[17] << 8 | trimdata[16]);
	dig_P7 = (int16_t)(trimdata[19] << 8 | trimdata[18]);
	dig_P8 = (int16_t)(trimdata[21] << 8 | trimdata[20]);
	dig_P9 = (int16_t)(trimdata[23] << 8 | trimdata[22]);

	// Humidity coefficients
	dig_H1 = trimdata[24];
	dig_H2 = (int16_t)(trimdata[26] << 8 | trimdata[25]);
	dig_H3 = trimdata[27];
	dig_H4 = (int16_t)((trimdata[28] << 4) | (trimdata[29] & 0x0F));
	dig_H5 = (int16_t)((trimdata[30] << 4) | ((trimdata[29] >> 4) & 0x0F));
	dig_H6 = (int8_t)trimdata[31];

	return 0; // Success
}

static int32_t BME280_compensate_T_int32(int32_t adc_T) {
	int32_t var1, var2, T;
	var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1)))>> 12) *((int32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

static uint32_t BME280_compensate_H_int32(int32_t adc_H) {
	int32_t v_x1_u32r;
	v_x1_u32r = (t_fine - ((int32_t)76800));
	v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) *\
			v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r *\
					((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) +\
							((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)dig_H2) +\
					8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *\
			((int32_t)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (uint32_t)(v_x1_u32r>>12);
}

static uint32_t BME280_compensate_P_int64(int32_t adc_P) {
	int64_t var1, var2, P;
	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)dig_P6;
	var2 = var2 + ((var1*(int64_t)dig_P5)<<17);
	var2 = var2 + (((int64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
	if (var1 == 0) {
		return 0; // avoid exception caused by division by zero
	}
	P = 1048576-adc_P;
	P = (((P<<31)-var2)*3125)/var1;
	var1 = (((int64_t)dig_P9) * (P>>13) * (P>>13)) >> 25;
	var2 = (((int64_t)dig_P8) * P) >> 19;
	P = ((P + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);
	return (uint32_t)P;
}

void BME280_Measure(int32_t *temperature, uint32_t *humidity, uint32_t *pressure) {
    if (BME280_ReadRaw() == 0) {
        if (tRaw == 0x800000) {
        	*temperature = 0; // temp disabled
        }
        else {
        	*temperature = BME280_compensate_T_int32(tRaw) - 5 * 100; // Po vydělení 100 ve °C
        	// Dočasná kompenzace kvůli ohřívání senzoru
        }

        if (hRaw == 0x8000) {
        	*humidity = 0; // humidity disabled
        }
        else {
        	*humidity = BME280_compensate_H_int32(hRaw); // Po vydělení 1024 v %
        }

        if (pRaw == 0x800000) {
        	*pressure = 0; // pressure disabled
        }
        else {
			*pressure = BME280_compensate_P_int64(pRaw) + 256 * 5 * 5; // Po vydělení 256 v Pa
			// Dočasná kompenzace kvůli ohřívání senzoru
        }
    }
    else {
        // if the device is detached
        *temperature = 0;
        *humidity    = 0;
        *pressure    = 0;
    }
}

int BME280_Config(uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h, uint8_t mode, uint8_t t_sb, uint8_t filter) {
	BME280_Set_SPI_Mode();

	uint8_t kontrola_dat = 0;     // Co se opravdu uložilo do registrů
	// Pokud nebudou proměnné souhlasit, data jsou poškozená

	/* --- Resetuje zařízení --- */
	config[0] = REG_RESET & 0x7F; // Pro zápis
	config[1] = RESET_SIGNAL;

	BME280_NSS_Low();
	status = HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 2, 20);
	BME280_NSS_High();
	if (status != HAL_OK) {
		return 2;  // Error NUM for debug
	}

	HAL_Delay(100); // Nutné pro zachování stability

	/* --- Do REG_CTRL_HUM zapíšeme `osrs_h` --- */
	config[0] = REG_CTRL_HUM & 0x7F; // Pro zápis
	config[1] = osrs_h;

	BME280_NSS_Low();
	status = HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 2, 20);
	BME280_NSS_High();
	if (status != HAL_OK) {
		return 3;
	}

	HAL_Delay(100);

	// Kontrola zapsaných dat
	config[0] = REG_CTRL_HUM | 0x80; // Pro čtení

	BME280_NSS_Low();
	HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 1, 10);
	HAL_SPI_TransmitReceive(&BME280_SPI_HANDLE, &dummy, &kontrola_dat, 1, 10); // Přečte data z registru a uloží je do proměnné `kontrola_dat`
	BME280_NSS_High();

	if (config[1] != kontrola_dat) {
		return 4;  // Error NUM for debug
	}

	/* --- Do REG_CONFIG zapíšeme `t_sb` a `filter` --- */
	config[0] = REG_CONFIG & 0x7F; // Pro zápis
	config[1] = (t_sb << 5) | (filter << 2);

	BME280_NSS_Low();
	status = HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 2, 20);
	BME280_NSS_High();
	if (status != HAL_OK) {
		return 5;  // Error NUM for debug (kódy 3 a 4 si necháváme pro BME280)
	}

	HAL_Delay(100);

	// Kontrola zapsaných dat
	config[0] = REG_CONFIG | 0x80; // Pro čtení

	BME280_NSS_Low();
	HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 1, 10);
	HAL_SPI_TransmitReceive(&BME280_SPI_HANDLE, &dummy, &kontrola_dat, 1, 10); // Přečte data z registru a uloží je do proměnné `kontrola_dat`
	BME280_NSS_High();

	if ((config[1] & 0xFC) != (kontrola_dat & 0xFC)) {
		return 6;  // Error NUM for debug
	}

	/* --- Do REG_CTRL_MEAS zapíšeme `osrs_t`, `osrs_p` a `mode` --- */
	config[0] = REG_CTRL_MEAS & 0x7F; // Pro zápis
	config[1] = (osrs_t << 5) | (osrs_p << 2) | mode;

	BME280_NSS_Low();
	status = HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 2, 20);
	BME280_NSS_High();
	if (status != HAL_OK) {
		return 7;  // Error NUM for debug
	}

	HAL_Delay(100);

	// Kontrola zapsaných dat
	config[0] = REG_CTRL_MEAS | 0x80; // Pro čtení

	BME280_NSS_Low();
	HAL_SPI_Transmit(&BME280_SPI_HANDLE, config, 1, 10);
	HAL_SPI_TransmitReceive(&BME280_SPI_HANDLE, &dummy, &kontrola_dat, 1, 10);
	BME280_NSS_High();
	if (config[1] != kontrola_dat) {
		return 8;  // Error NUM for debug
	}

	// Read the Trimming parameters
	if (TrimRead() != 0) {
		return 1;
	}

	return 0;  // Bez chyby
}
