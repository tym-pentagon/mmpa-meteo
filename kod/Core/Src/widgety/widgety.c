/*
 * widgety.c
 *
 *  Created on: 1. 5. 2026
 *      Author: markus
 */

#include "main.h"
#include "widgety.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "obrazky.h"

void horniLista(char nadpis_stranky[]) {
	/* Domeček */
	BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);

	BSP_LCD_DrawBitmap(
		VYSKA_HORNI_LISTY / 2 - domecek_40x38_16.infoHeader.biWidth / 2, // Vycentrovat
		VYSKA_HORNI_LISTY / 2 - domecek_40x38_16.infoHeader.biHeight / 2,
		(uint8_t *)&domecek_40x38_16
	);

	/* Rámec pro nadpis stránky */
	BSP_LCD_DrawRect(VYSKA_HORNI_LISTY - 1, 0, SIRKA_DISPLEJE - VYSKA_HORNI_LISTY, VYSKA_HORNI_LISTY);

	/* Rámec pro domeček */
	BSP_LCD_SetTextColor(BARVA_VYBER);
	BSP_LCD_DrawRect(0, 0, VYSKA_HORNI_LISTY, VYSKA_HORNI_LISTY);

	/* Nadpis stránky */
	BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);
	BSP_LCD_SetFont(&Terminus24Bold);

	BSP_LCD_DisplayStringAt((VYSKA_HORNI_LISTY - 1) / 2, VYSKA_HORNI_LISTY / 2 - Terminus24Bold.Height / 2, (uint8_t *)nadpis_stranky, CENTER_MODE);
}
