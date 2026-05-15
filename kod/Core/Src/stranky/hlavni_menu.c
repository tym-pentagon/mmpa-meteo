/*
 * hlavni_menu.c
 *
 *  Created on: 30. 4. 2026
 *      Author: markus
 */

#include "main.h"
#include "hlavni_menu.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "obrazky.h"

/* Čtyřúhelníky v menu */
Point ctyruhelniky[][5] = {
	{ {163, 176}, {221, 218}, {311, 188}, {163, 81} },
	{ {222, 223}, {200, 291}, {256, 368}, {312, 193} },
	{ {196, 294}, {124, 294}, {68, 371}, {252, 371} },
	{ {120, 291}, {98, 223}, {8, 193}, {64, 368} },
	{ {99, 218}, {157, 176}, {157, 81}, {9, 188} }
};

uint8_t styl_hodin = 1; /* 0 - čísla vedle sebe, oddělená dvojtečkami; 1 - čísla pod sebou */

void vykresliHorniListuVHlavnimMenu(bool pripojeno, uint16_t ping) {
	/* Horní lišta */
	BSP_LCD_SetFont(&Terminus20Normal);

	const char spojeni_text[] = {
	    0x53, 0x70, 0x6F, 0x6A, 0x65, 0x6E, 0xED, 0x3A, 0x00,  // "Spojení:"
	};
	BSP_LCD_SetTextColor(BARVA_UI_SEKUNDARNI);
	BSP_LCD_DisplayStringAt(PADDING, (VYSKA_HORNI_LISTY_V_HLAVNIM_MENU - 1) / 2 - Terminus20Normal.Height / 2, (uint8_t *)spojeni_text, LEFT_MODE);

	/* Stav spojení */
	BSP_LCD_SetFont(&Terminus20Bold);
	if (pripojeno != 0) {
		const char pripojeno_text[] = {
		    0x70, 0xF8, 0x69, 0x70, 0x6F, 0x6A, 0x65, 0x6E, 0x6F, 0x00,  // "připojeno"
		};
		BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);
		BSP_LCD_DisplayStringAt(PADDING + Terminus20Normal.Width * strlen(spojeni_text), (VYSKA_HORNI_LISTY_V_HLAVNIM_MENU - 1) / 2 - Terminus20Bold.Height / 2, (uint8_t *)pripojeno_text, LEFT_MODE);
	}
	else {
		const char odpojeno_text[] = {
			0x6F, 0x64, 0x70, 0x6F, 0x6A, 0x65, 0x6E, 0x6F, 0x00,  // "odpojeno"
		};
		BSP_LCD_SetTextColor(BARVA_UPOZORNENI);
		BSP_LCD_DisplayStringAt(PADDING + Terminus20Normal.Width * strlen(spojeni_text), (VYSKA_HORNI_LISTY_V_HLAVNIM_MENU - 1) / 2 - Terminus20Bold.Height / 2, (uint8_t *)odpojeno_text, LEFT_MODE);
	}

	/* Ping */
	BSP_LCD_SetFont(&Terminus20Normal);

	const char ping_text[] = {
		0x50, 0x69, 0x6E, 0x67, 0x3A, 0x00,  // "Ping:"
	};

	char ping_buffer[9];
	snprintf(ping_buffer, 9, "%d ms", ping);

	BSP_LCD_SetTextColor(BARVA_UI_SEKUNDARNI);
	BSP_LCD_DisplayStringAt(PADDING + Terminus20Normal.Width * strlen(ping_buffer), (VYSKA_HORNI_LISTY_V_HLAVNIM_MENU - 1) / 2 - Terminus20Normal.Height / 2, (uint8_t *)ping_text, RIGHT_MODE);

	if (ping <= 1000) {
		BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);
	}
	else {
		BSP_LCD_SetTextColor(BARVA_UPOZORNENI);
	}
	BSP_LCD_SetFont(&Terminus20Bold);

	BSP_LCD_DisplayStringAt(PADDING, (VYSKA_HORNI_LISTY_V_HLAVNIM_MENU - 1) / 2 - Terminus20Bold.Height / 2, (uint8_t *)ping_buffer, RIGHT_MODE);

	BSP_LCD_SetTextColor(BARVA_UI_TERCIARNI);
	BSP_LCD_DrawHLine(PADDING, VYSKA_HORNI_LISTY_V_HLAVNIM_MENU - BORDER, SIRKA_DISPLEJE - 2 * PADDING); // Border
}

void vykresliStavSDKartyVHlavnimMenu() {
	BSP_LCD_SetTextColor(BARVA_UI_TERCIARNI);
	BSP_LCD_DrawHLine(PADDING, VYSKA_DISPLEJE - VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU, SIRKA_DISPLEJE - 2 * PADDING); // Border

	/* Stav SD karty */
	const char pripojovani_sd_karty_text[] = {
	    0x50, 0xF8, 0x69, 0x70, 0x6F, 0x6A, 0x6F, 0x76, 0xE1, 0x6E, 0xED, 0x20, 0x53, 0x44, 0x20, 0x6B,  // "Připojování SD k"
	    0x61, 0x72, 0x74, 0x79, 0x2E, 0x2E, 0x2E, 0x00,  // "arty..."
	};

	BSP_LCD_SetFont(&Terminus20Bold);
	BSP_LCD_DisplayStringAt(0, VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER) / 2 - Terminus20Bold.Height / 2, (uint8_t *)pripojovani_sd_karty_text, CENTER_MODE);
}

void aktualizujStavSDKartyVHlavnimMenu(bool sd_karta_pripojena, uint32_t kapacita_sd_karty, uint32_t zaplneni_sd_karty) {
	BSP_LCD_SetTextColor(BARVA_POZADI);
	BSP_LCD_FillRect(0, VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER), SIRKA_DISPLEJE, VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER);

	if (sd_karta_pripojena) {
		BSP_LCD_DrawBitmap(
			PADDING + (SIRKA_IKONY_SD_KARTY - sd_karta_22x32_16.infoHeader.biWidth) / 2, // Vycentrovat
			VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER) + PADDING,
			(uint8_t *)&sd_karta_22x32_16
		);

		BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);

		char zaplneni_sd_karty_text[20];

		double kapacita_sd_karty_double;
		double zaplneni_sd_karty_double;

		/* Převedu na GB a na double kvůli desetinným místům */
		kapacita_sd_karty_double = kapacita_sd_karty / 1024.0 / 1024.0;
		zaplneni_sd_karty_double = zaplneni_sd_karty / 1024.0 / 1024.0;

		// Převedu na char array, vždy přesně s 1 desetinným místem
		snprintf(zaplneni_sd_karty_text, 20, "%.1f/%.1f GB", zaplneni_sd_karty_double, kapacita_sd_karty_double);

		uint8_t delka_textu_zaplneni_sd_karty = strlen(zaplneni_sd_karty_text);

		if (delka_textu_zaplneni_sd_karty <= 11) {
			BSP_LCD_SetFont(&Terminus18Bold); // Šířka znaku: 10 px

			/* První parametr - pozice x - počítá se zarovnáním k pravé straně displeje - uvádí tedy vzdálenost
			 * pravého okraje textu od pravého okraje displeje.
			 * Text je potřeba zarovnat na střed prázdného prostoru, který je pro text určen.
			 * Začnu s paddingem.
			 * Přičtu (prostor pro text - šířka textu) / 2.
			 * Vydělím 2, protože chci zarovnat na střed.
			 * Kdybych nevydělil 2, byl by text zarovnaný k levé straně.
			 */
			BSP_LCD_DisplayStringAt(PADDING + (MISTO_PRO_TEXT_O_ZAPLNENI_SD_KARTY - Terminus18Bold.Width * delka_textu_zaplneni_sd_karty) / 2, VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER) / 2 - Terminus18Bold.Height / 2, (uint8_t *)zaplneni_sd_karty_text, RIGHT_MODE);
		}
		else if (delka_textu_zaplneni_sd_karty <= 14) {
			BSP_LCD_SetFont(&Terminus14Bold); // Šířka znaku: 8 px
			BSP_LCD_DisplayStringAt(PADDING + (MISTO_PRO_TEXT_O_ZAPLNENI_SD_KARTY - Terminus14Bold.Width * delka_textu_zaplneni_sd_karty) / 2, VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER) / 2 - Terminus14Bold.Height / 2, (uint8_t *)zaplneni_sd_karty_text, RIGHT_MODE);
		}
		else {
			BSP_LCD_SetFont(&Terminus12Bold); // Šířka znaku: 6 px
			BSP_LCD_DisplayStringAt(PADDING + (MISTO_PRO_TEXT_O_ZAPLNENI_SD_KARTY - Terminus12Bold.Width * delka_textu_zaplneni_sd_karty) / 2, VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER) / 2 - Terminus12Bold.Height / 2, (uint8_t *)zaplneni_sd_karty_text, RIGHT_MODE);
		}

		/* Progressbar */
		double procent_sd_karty_zaplneno = zaplneni_sd_karty_double / kapacita_sd_karty_double;
		uint16_t sirka_zaplnene_casti_progressbaru = (SIRKA_PROGRESSBARU - 2 * BORDER) * procent_sd_karty_zaplneno;

		BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);
		BSP_LCD_DrawRect(SIRKA_IKONY_SD_KARTY + 2 * PADDING, VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER) / 2 - VYSKA_PROGRESSBARU / 2, SIRKA_PROGRESSBARU - 2 * BORDER, VYSKA_PROGRESSBARU); // Obrys
		BSP_LCD_FillRect(SIRKA_IKONY_SD_KARTY + 2 * PADDING + BORDER, VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER) / 2 - VYSKA_PROGRESSBARU / 2 + BORDER, sirka_zaplnene_casti_progressbaru, VYSKA_PROGRESSBARU - 2 * BORDER); // Výplň
	}
	else {
		BSP_LCD_SetTextColor(BARVA_UPOZORNENI);

		const char sd_karta_odpojena_text[] = {
		    0x53, 0x44, 0x20, 0x6B, 0x61, 0x72, 0x74, 0x61, 0x20, 0x6F, 0x64, 0x70, 0x6F, 0x6A, 0x65, 0x6E,  // "SD karta odpojen"
		    0x61, 0x00,  // "a"
		};

		BSP_LCD_SetFont(&Terminus20Bold);
		BSP_LCD_DisplayStringAt(0, VYSKA_DISPLEJE - (VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER) / 2 - Terminus20Bold.Height / 2, (uint8_t *)sd_karta_odpojena_text, CENTER_MODE);
	}
}

void aktualizujHodinyVHlavnimMenu(Cas cas, Cas *predchozi_cas) {
	BSP_LCD_SetFont(&Terminus32Bold);
	BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);

	if (predchozi_cas->hodiny != cas.hodiny) {
		char hodiny_buffer[4];
		snprintf(hodiny_buffer, 4, "%02d", cas.hodiny);
		// 0 - prázdná místa vyplnit nulami, 2 - délka čísla, d - kladné celé číslo

		BSP_LCD_DisplayStringAt(0, 240 - 16 - 30, (uint8_t *)hodiny_buffer, CENTER_MODE);

		predchozi_cas->hodiny = cas.hodiny;
	}

	if (predchozi_cas->minuty != cas.minuty) {
		char minuty_buffer[4];
		snprintf(minuty_buffer, 4, "%02d", cas.minuty);

		BSP_LCD_DisplayStringAt(0, 240 - 16, (uint8_t *)minuty_buffer, CENTER_MODE);

		predchozi_cas->minuty = cas.minuty;
	}

	if (predchozi_cas->sekundy != cas.sekundy) {
		char sekundy_buffer[4];
		snprintf(sekundy_buffer, 4, "%02d", cas.sekundy);

		BSP_LCD_DisplayStringAt(0, 240 - 16 + 30, (uint8_t *)sekundy_buffer, CENTER_MODE);

		predchozi_cas->sekundy = cas.sekundy;
	}
}

void aktualizujPoziciVyberuVHlavnimMenu(uint16_t predchozi_pozice_vyberu, uint16_t pozice_vyberu) {
	/* Překreslí původní výběr */
	BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);
	BSP_LCD_DrawPolygon(ctyruhelniky[predchozi_pozice_vyberu], 4);

	/* Vykreslí nový výběr */
	BSP_LCD_SetTextColor(BARVA_VYBER);
	BSP_LCD_DrawPolygon(ctyruhelniky[pozice_vyberu], 4);
}

uint8_t vykresliHlavniMenu(uint8_t pripojeno, uint16_t ping, Cas cas, uint16_t *predchozi_pozice_vyberu, uint16_t *pozice_vyberu, uint16_t *max_pozice_vyberu, bool vyzkouseno_pripojeni_sd_karty) {
	BSP_LCD_Clear(BARVA_POZADI);
	BSP_LCD_SetBackColor(BARVA_POZADI);

	vykresliHorniListuVHlavnimMenu(pripojeno, ping);

	/* Pentagon */
	BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI);

	Point pentagon[5] = {
		{160, 180},
		{217, 221},
		{195, 289},
		{125, 289},
		{103, 221}
	};

	BSP_LCD_DrawPolygon(pentagon, 5);

	*max_pozice_vyberu = 4;
	*pozice_vyberu = *pozice_vyberu % (*max_pozice_vyberu + 1);
	*predchozi_pozice_vyberu = *pozice_vyberu;

	/* Čtyřúhelníky */
	for (uint8_t i = 0; i < 5; i ++) {
		if ((uint16_t)i == *pozice_vyberu) {
			BSP_LCD_SetTextColor(BARVA_VYBER); // Dočasná změna barvy
		}

		BSP_LCD_DrawPolygon(ctyruhelniky[i], 4);

		if ((uint16_t)i == *pozice_vyberu) {
			BSP_LCD_SetTextColor(BARVA_UI_PRIMARNI); // Nastaví zpět primární barvu UI
		}
	}

	/* Ikony */
	BSP_LCD_DrawBitmap(
		215 - oblak_44x34_16.infoHeader.biWidth / 2, // Vycentrovat
		167 - oblak_44x34_16.infoHeader.biHeight / 2,
		(uint8_t *)&oblak_44x34_16
	);

	BSP_LCD_DrawBitmap(
		245 - vitr_41x42_16.infoHeader.biWidth / 2, // Vycentrovat
		271 - vitr_41x42_16.infoHeader.biHeight / 2,
		(uint8_t *)&vitr_41x42_16
	);

	BSP_LCD_DrawBitmap(
		160 - magnet_52x26_16.infoHeader.biWidth / 2, // Vycentrovat
		333 - magnet_52x26_16.infoHeader.biHeight / 2,
		(uint8_t *)&magnet_52x26_16
	);

	/* Hodiny */
	if (styl_hodin == 0) {
		char hodiny_buffer[12];
		snprintf(hodiny_buffer, 12, "%02d:%02d:%02d", cas.hodiny, cas.minuty, cas.sekundy);
		// 0 - prázdná místa vyplnit nulami, 2 - délka čísla, d - kladné celé číslo

		BSP_LCD_SetFont(&Terminus20Bold);
		BSP_LCD_DisplayStringAt(0, 240 - 10, (uint8_t *)hodiny_buffer, CENTER_MODE);
	}
	else if (styl_hodin == 1) {
		char hodiny_buffer[4];
		snprintf(hodiny_buffer, 4, "%02d", cas.hodiny);
		// 0 - prázdná místa vyplnit nulami, 2 - délka čísla, d - kladné celé číslo

		char minuty_buffer[4];
		snprintf(minuty_buffer, 4, "%02d", cas.minuty);

		char sekundy_buffer[4];
		snprintf(sekundy_buffer, 4, "%02d", cas.sekundy);

		BSP_LCD_SetFont(&Terminus32Bold);

		BSP_LCD_DisplayStringAt(0, 240 - 16 - 30, (uint8_t *)hodiny_buffer, CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 240 - 16, (uint8_t *)minuty_buffer, CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 240 - 16 + 30, (uint8_t *)sekundy_buffer, CENTER_MODE);
	}
	else {
		Error_Handler(); // Neplatný styl hodin
		return 1;
	}

	if (vyzkouseno_pripojeni_sd_karty) {
		BSP_LCD_SetTextColor(BARVA_UI_TERCIARNI);
		BSP_LCD_DrawHLine(PADDING, VYSKA_DISPLEJE - VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU, SIRKA_DISPLEJE - 2 * PADDING); // Border

		stavSD();
	}
	else {
		vykresliStavSDKartyVHlavnimMenu();
	}

	return 0; // Funkce úspěšně skončila
}
