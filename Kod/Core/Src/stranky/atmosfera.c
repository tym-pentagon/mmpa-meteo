/*
 * atmosfera.c
 *
 *  Created on: 1. 5. 2026
 *      Author: markus
 */

#include "main.h"
#include "atmosfera.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "obrazky.h"
#include "widgety.h"
#include "math.h"
#include "stdlib.h"

char teplota_hodnota_text[20];
char vlhkost_hodnota_text[20];
char tlak_hodnota_text[20];

char teplota_venku_hodnota_text[20];
char vlhkost_venku_hodnota_text[20];
char tlak_venku_hodnota_text[20];

void konverzeNamerenychHodnotSigned(int32_t hodnota, uint32_t delitel, uint8_t pocet_desetinnych_mist, char *vystup, uint8_t delka_vystupu) {
	bool pozitivni = false;

	if (hodnota >= 0) {
		pozitivni = true;
	}

	if (pocet_desetinnych_mist > 3) {
		pocet_desetinnych_mist = 3; // Limit počtu desetinných míst
	}

	int32_t nasobek_deseti = 1;

	for (uint8_t i = pocet_desetinnych_mist; i > 0; i --) {
		nasobek_deseti *= 10;
	}

	int32_t vynasobena_hodnota = (hodnota * nasobek_deseti + delitel / 2) / delitel;

	int32_t cela_cast = abs(vynasobena_hodnota / nasobek_deseti);
	int32_t desetinna_cast = abs(vynasobena_hodnota % nasobek_deseti);

	snprintf(
		vystup,
		delka_vystupu,
		"%s%ld,%0*ld",
		pozitivni ? "" : "-",
        (long)cela_cast,
        pocet_desetinnych_mist,
        (long)desetinna_cast
	);
}

void konverzeNamerenychHodnotUnsigned(uint32_t hodnota, uint32_t delitel, uint8_t pocet_desetinnych_mist, char *vystup, uint8_t delka_vystupu) {
	if (pocet_desetinnych_mist > 3) {
		pocet_desetinnych_mist = 3; // Limit počtu desetinných míst
	}

	int32_t nasobek_deseti = 1;

	for (uint8_t i = pocet_desetinnych_mist; i > 0; i --) {
		nasobek_deseti *= 10;
	}

	int32_t vynasobena_hodnota = (hodnota * nasobek_deseti + delitel / 2) / delitel;

	int32_t cela_cast = abs(vynasobena_hodnota / nasobek_deseti);
	int32_t desetinna_cast = abs(vynasobena_hodnota % nasobek_deseti);

	snprintf(
		vystup,
		delka_vystupu,
		"%ld,%0*ld",
        (long)cela_cast,
        pocet_desetinnych_mist,
        (long)desetinna_cast
	);
}

void vykresliHodnotyNaStranceAtmosfera() {
	BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);
	BSP_LCD_SetFont(&Terminus20Bold);

	BSP_LCD_DisplayStringAt(PADDING + 3 * 10, VYSKA_HORNI_LISTY + 2 * PADDING + 32, (uint8_t *)teplota_hodnota_text, RIGHT_MODE);
	BSP_LCD_DisplayStringAt(PADDING + 3 * 10, VYSKA_HORNI_LISTY + 3 * PADDING + 32 + 20, (uint8_t *)vlhkost_hodnota_text, RIGHT_MODE);
	BSP_LCD_DisplayStringAt(PADDING + 3 * 10, VYSKA_HORNI_LISTY + 4 * PADDING + 32 + 2 * 20, (uint8_t *)tlak_hodnota_text, RIGHT_MODE);

	BSP_LCD_DisplayStringAt(PADDING + 3 * 10, VYSKA_HORNI_LISTY + 5 * PADDING + 2 * 32 + 3 * 20 + MEZERA, (uint8_t *)teplota_venku_hodnota_text, RIGHT_MODE);
	BSP_LCD_DisplayStringAt(PADDING + 3 * 10, VYSKA_HORNI_LISTY + 6 * PADDING + 2 * 32 + 4 * 20 + MEZERA, (uint8_t *)vlhkost_venku_hodnota_text, RIGHT_MODE);
	BSP_LCD_DisplayStringAt(PADDING + 3 * 10, VYSKA_HORNI_LISTY + 7 * PADDING + 2 * 32 + 5 * 20 + MEZERA, (uint8_t *)tlak_venku_hodnota_text, RIGHT_MODE);
}

void aktualizujHodnotyNaStranceAtmosfera(int32_t teplota, uint32_t vlhkost, uint32_t tlak, int32_t teplota_venku, uint32_t vlhkost_venku, uint32_t tlak_venku) {
	konverzeNamerenychHodnotSigned(teplota, 100, 2, teplota_hodnota_text, sizeof(teplota_hodnota_text));
	konverzeNamerenychHodnotUnsigned(vlhkost, 1024, 3, vlhkost_hodnota_text, sizeof(vlhkost_hodnota_text));
	konverzeNamerenychHodnotUnsigned(tlak, 256, 1, tlak_hodnota_text, sizeof(tlak_hodnota_text));

	konverzeNamerenychHodnotSigned(teplota_venku, 100, 2, teplota_venku_hodnota_text, sizeof(teplota_venku_hodnota_text));
	konverzeNamerenychHodnotUnsigned(vlhkost_venku, 1024, 3, vlhkost_venku_hodnota_text, sizeof(vlhkost_venku_hodnota_text));
	konverzeNamerenychHodnotUnsigned(tlak_venku, 256, 1, tlak_venku_hodnota_text, sizeof(tlak_venku_hodnota_text));

	vykresliHodnotyNaStranceAtmosfera();
}

void vykresliPopiskyKHodnotam(uint8_t offset_y) {
	BSP_LCD_SetFont(&Terminus20Normal);
	BSP_LCD_SetTextColor(BARVA_UI_SEKUNDARNI);

	/* Text "Teplota vzduchu:" */
	const char teplota_vzduchu_text[] = {
		0x54, 0x65, 0x70, 0x6C, 0x6F, 0x74, 0x61, 0x20, 0x76, 0x7A, 0x64, 0x75, 0x63, 0x68, 0x75, 0x3A,  // "Teplota vzduchu:"
		0x00,  // ""
	};
	BSP_LCD_DisplayStringAt(PADDING, offset_y, (uint8_t *)teplota_vzduchu_text, LEFT_MODE);

	/* Text "°C" */
	const char stupne_celsia_text[] = {
	    0xB0, 0x43, 0x00,  // "°C"
	};
	BSP_LCD_DisplayStringAt(PADDING + 2, offset_y, (uint8_t *)stupne_celsia_text, RIGHT_MODE);

	/* Text "Vlhkost vzduchu:" */
	const char vlhkost_vzduchu_text[] = {
		0x56, 0x6C, 0x68, 0x6B, 0x6F, 0x73, 0x74, 0x20, 0x76, 0x7A, 0x64, 0x75, 0x63, 0x68, 0x75, 0x3A,  // "Vlhkost vzduchu:"
		0x00,  // ""
	};
	BSP_LCD_DisplayStringAt(PADDING, offset_y + PADDING + 20, (uint8_t *)vlhkost_vzduchu_text, LEFT_MODE);

	/* Text "%" */
	const char procenta_text[] = {
	    0x25, 0x00,  // "%"
	};
	BSP_LCD_DisplayStringAt(PADDING + 10, offset_y + PADDING + 20, (uint8_t *)procenta_text, RIGHT_MODE);

	/* Text "Atmosférický tlak:" */
	const char atmosfericky_tlak_text[] = {
		0x41, 0x74, 0x6D, 0x6F, 0x73, 0x66, 0xE9, 0x72, 0x69, 0x63, 0x6B, 0xFD, 0x20, 0x74, 0x6C, 0x61,  // "Atmosférický tla"
		0x6B, 0x3A, 0x00,  // "k:"
	};
	BSP_LCD_DisplayStringAt(PADDING, offset_y + 2 * PADDING + 2 * 20, (uint8_t *)atmosfericky_tlak_text, LEFT_MODE);

	/* Text "Pa" */
	const char pascaly_text[] = {
	    0x50, 0x61, 0x00,  // "Pa"
	};
	BSP_LCD_DisplayStringAt(PADDING, offset_y + 2 * PADDING + 2 * 20, (uint8_t *)pascaly_text, RIGHT_MODE);
}

void vykresliStrankuAtmosfera(uint16_t *predchozi_pozice_vyberu, uint16_t *pozice_vyberu, uint16_t *max_pozice_vyberu) {
	*max_pozice_vyberu = 0;
	*pozice_vyberu = 0;
	*predchozi_pozice_vyberu = 0;

	BSP_LCD_Clear(BARVA_POZADI);
	BSP_LCD_SetBackColor(BARVA_POZADI);

	char atmosfera_text[] = {
	    0x41, 0x74, 0x6D, 0x6F, 0x73, 0x66, 0xE9, 0x72, 0x61, 0x00,  // "Atmosféra"
	};

	horniLista(atmosfera_text);

	/* Uvnitř */
	BSP_LCD_SetFont(&Terminus32Bold);
	BSP_LCD_SetTextColor(BARVA_UI_SEKUNDARNI);

	const char uvnitr_text[] = {
	    0x55, 0x76, 0x6E, 0x69, 0x74, 0xF8, 0x00,  // "Uvnitř"
	};
	BSP_LCD_DisplayStringAt(0, VYSKA_HORNI_LISTY + PADDING, (uint8_t *)uvnitr_text, CENTER_MODE);

	vykresliPopiskyKHodnotam(VYSKA_HORNI_LISTY + 2 * PADDING + 32);

	/* Venku */
	BSP_LCD_SetFont(&Terminus32Bold);
	BSP_LCD_SetTextColor(BARVA_UI_SEKUNDARNI);

	const char venku_text[] = {
	    0x56, 0x65, 0x6E, 0x6B, 0x75, 0x00,  // "Venku"
	};
	BSP_LCD_DisplayStringAt(0, VYSKA_HORNI_LISTY + 4 * PADDING + 32 + 3 * 20 + MEZERA, (uint8_t *)venku_text, CENTER_MODE);

	vykresliPopiskyKHodnotam(VYSKA_HORNI_LISTY + 5 * PADDING + 2 * 32 + 3 * 20 + MEZERA);
}
