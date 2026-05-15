#ifndef BME280_H
#define BME280_H

#include "main.h"

/* --- Definice pinů --- */
extern SPI_HandleTypeDef BME280_SPI_HANDLE;

#define BME280_NSS_GPIO_Port		SPI3_NSS_GPIO_Port
#define BME280_NSS_Pin				SPI3_NSS_Pin

#define BME280_A0_GPIO_Port			SPI3_A0_GPIO_Port
#define BME280_A0_Pin				SPI3_A0_Pin
#define BME280_A0_Status			1

#define BME280_A1_GPIO_Port			SPI3_A1_GPIO_Port
#define BME280_A1_Pin				SPI3_A1_Pin
#define BME280_A1_Status			0

#define BME280_A2_GPIO_Port			SPI3_A2_GPIO_Port
#define BME280_A2_Pin				SPI3_A2_Pin
#define BME280_A2_Status			0

/* --- Registry --- */
/* Výstup */
#define START_REG_OUTPUT   0xF7 // -> REG_PRESS_MSB
#define LENGTH_REG_OUTPUT  8    // 0xF7 + 8 = 0xFE -> REG_TEMP_XLSB

/* Konfigurace a ovládání */
#define REG_CONFIG         0xF5
#define REG_CTRL_MEAS      0xF4
#define REG_STATUS         0xF3
#define REG_CTRL_HUM       0xF2
#define REG_RESET          0xE0
#define REG_ID             0xD0

/* Kalibrace */
#define START_REG_CALIB    0x88 // Počáteční registr
#define LENGTH_REG_CALIB   25   // 0x88 + 25 = 0xA1 -> koncový registr

#define START_REG_CALIB_2  0xE1 // Počáteční registr
#define LENGTH_REG_CALIB_2 7    // 0xE1 + 7 = 0xE7 -> koncový registr

/* --- Hodnoty registrů --- */
#define EXPECTED_ID        0x60 // Čekáme, že REG_ID bude mít hodnotu 0x60
#define RESET_SIGNAL       0xB6 // Pokud do registru REG_RESET zapíšeme hodnotu 0xB6, BME280 se resetuje

/* --- Možnosti konfigurace --- */
/* Zdroj: https://chatgpt.com/ [upraveno] */
typedef enum {
	OSRS_0   = 0b000, // Oversampling vypnut
	OSRS_1   = 0b001,
	OSRS_2   = 0b010,
	OSRS_4   = 0b011,
	OSRS_8   = 0b100,
	OSRS_16  = 0b101
} Oversampling;

typedef enum {
    MODE_SLEEP  = 0b00,
    MODE_FORCED = 0b01,
    MODE_NORMAL = 0b11
} Mode; // Power mode

typedef enum {
    T_SB_0p5   = 0b000,
    T_SB_62p5  = 0b001,
    T_SB_125   = 0b010,
    T_SB_250   = 0b011,
    T_SB_500   = 0b100,
    T_SB_1000  = 0b101,
    T_SB_10  = 0b110,
    T_SB_20  = 0b111
} StandbyTime; // V milisekundách

typedef enum {
    IIR_OFF = 0b000,
    IIR_2   = 0b001,
    IIR_4   = 0b010,
    IIR_8   = 0b011,
    IIR_16  = 0b100
} Filter;

/* --- Veřejné prototypy funkcí --- */
void BME280_Measure(int32_t *temperature, uint32_t *humidity, uint32_t *pressure);
int BME280_Config(uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h, uint8_t mode, uint8_t t_sb, uint8_t filter);

#endif /* BME280_H */
