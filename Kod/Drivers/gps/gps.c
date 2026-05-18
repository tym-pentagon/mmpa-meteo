/*
 * gps.c
 *
 *  Created on: 18. 5. 2026
 *      Author: markus
 */

#include "main.h"
#include "gps.h"
#include "stm32f7xx_hal.h"
#include "stdbool.h"
#include "string.h"

uint8_t rx_char;
volatile uint16_t rx_char_index = 0;
char zprava[128];
volatile bool zprava_pripravena = false;

typedef enum {
	INVALID,
	GGA,
	GSA,
	GSV,
	RMC,
	VTG
} packet_t;

packet_t typ_packetu;

volatile Cas cas;

uint8_t charToInt(char input) {
	uint8_t output = input - '0';
	return output;
}

void gps_init() {
	HAL_UART_Receive_IT(&GPS_UART_HANDLE, &rx_char, 1);
}

void gps_loop() {
	if (zprava_pripravena) {
		zprava_pripravena = false;

		char *argument = strtok(zprava, ",");

		for (size_t i = 0; argument != NULL; i ++) { // Limit: 100 položek (ochrana proti případnému zacyklení)
			if (i == 0) {
				char typ_packetu_str[4];
				memcpy(typ_packetu_str, argument + 3, 3);
				typ_packetu_str[3] = '\0';

				if (strncmp(typ_packetu_str, "RMC", 3) == 0) {
					typ_packetu = RMC;
				}
			}

			if (i == 1 && typ_packetu == RMC && strlen(argument) >= 6) {
				cas.hodiny = charToInt(argument[0]) * 10 + charToInt(argument[1]);
				cas.minuty = charToInt(argument[2]) * 10 + charToInt(argument[3]);
				cas.sekundy = charToInt(argument[4]) * 10 + charToInt(argument[5]);
			}

			if (i == 9 && typ_packetu == RMC && strlen(argument) >= 6) {
				cas.den = charToInt(argument[0]) * 10 + charToInt(argument[1]);
				cas.mesic = charToInt(argument[2]) * 10 + charToInt(argument[3]);
				cas.rok = 2000 + charToInt(argument[4]) * 10 + charToInt(argument[5]);
			}

			argument = strtok(NULL, ","); // Přejde na další argument
		}

		typ_packetu = INVALID;
	}
}
