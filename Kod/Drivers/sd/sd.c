/*
 * sd.c
 *
 *  Created on: 19. 5. 2026
 *      Author: markus
 */

#include "stdbool.h"
#include "sd.h"
#include "fatfs.h"

/* Proměnné pro FatFs */
FATFS FatFs; 	// FatFs handle
FIL fil; 		// File handle
FRESULT fres;   // Result after operations

volatile bool sd_karta_pripojena = 0;
volatile uint32_t kapacita_sd_karty = 0; // KB
volatile uint32_t zaplneni_sd_karty = 0; // KB

/* Allow SD card remounting */
extern Disk_drvTypeDef disk;

DSTATUS disk_reinitialize (
	BYTE pdrv				/* Physical drive number to identify the drive */
)
{
	return disk.drv[pdrv]->disk_initialize(disk.lun[pdrv]);
}

uint8_t stavSD(void) {
	/* Získá stav SD karty - zda je připojena, jakou má kapacitu a kolik je na ní volného místa */

	f_mount(NULL, "", 1); // Nejprve odpojí

	// NOW initialize disk
	if (disk_reinitialize(0) != RES_OK) {
		sd_karta_pripojena = 0; // SD karta je odpojena
	}
	else {
		fres = f_mount(&FatFs, "", 1); // 1 = mount now

		if (fres != FR_OK) {
			// Otevře filesystém
			sd_karta_pripojena = 0; // SD karta je odpojena
		}
		else {
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

	return 0; // Funkce úspěšně skončila
}
