/*
 * hlavni_menu.h
 *
 *  Created on: 30. 4. 2026
 *      Author: markus
 */

#ifndef SRC_STRANKY_HLAVNI_MENU_H_
#define SRC_STRANKY_HLAVNI_MENU_H_

#include "main.h"
#include "stdbool.h"

void aktualizujStavSDKartyVHlavnimMenu(bool sd_karta_pripojena, uint32_t kapacita_sd_karty, uint32_t zaplneni_sd_karty);
void aktualizujHodinyVHlavnimMenu(Cas cas, Cas *predchozi_cas);
void aktualizujPoziciVyberuVHlavnimMenu(uint16_t predchozi_pozice_vyberu, uint16_t pozice_vyberu);
uint8_t vykresliHlavniMenu(uint8_t pripojeno, uint16_t ping, Cas cas, uint16_t *predchozi_pozice_vyberu, uint16_t *pozice_vyberu, uint16_t *max_pozice_vyberu);

/* Rozměry konkrétních prvků */
// Všechny rozměry jsou včetně borderů, bez paddingu
#define VYSKA_HORNI_LISTY_V_HLAVNIM_MENU		32

#define VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU		37
#define VYSKA_PROGRESSBARU						(VYSKA_SPODNI_LISTY_V_HLAVNIM_MENU - BORDER - 2 * PADDING)
#define SIRKA_PROGRESSBARU 						172
#define SIRKA_IKONY_SD_KARTY					32
#define MISTO_PRO_TEXT_O_ZAPLNENI_SD_KARTY		(SIRKA_DISPLEJE - 4 * PADDING - SIRKA_IKONY_SD_KARTY - SIRKA_PROGRESSBARU)

#endif /* SRC_STRANKY_HLAVNI_MENU_H_ */
