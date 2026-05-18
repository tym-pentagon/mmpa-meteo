/*
 * atmosfera.h
 *
 *  Created on: 1. 5. 2026
 *      Author: markus
 */

#ifndef SRC_STRANKY_ATMOSFERA_H_
#define SRC_STRANKY_ATMOSFERA_H_

#include "main.h"
#include "stdbool.h"

void konverzeNamerenychHodnotSigned(int32_t hodnota, uint32_t delitel, uint8_t pocet_desetinnych_mist, char *vystup, uint8_t delka_vystupu);
void konverzeNamerenychHodnotUnsigned(uint32_t hodnota, uint32_t delitel, uint8_t pocet_desetinnych_mist, char *vystup, uint8_t delka_vystupu);
void aktualizujHodnotyNaStranceAtmosfera(int32_t teplota, uint32_t vlhkost, uint32_t tlak, int32_t teplota_venku, uint32_t vlhkost_venku, uint32_t tlak_venku);
void vykresliStrankuAtmosfera(uint16_t *predchozi_pozice_vyberu, uint16_t *pozice_vyberu, uint16_t *max_pozice_vyberu);

#endif /* SRC_STRANKY_ATMOSFERA_H_ */
