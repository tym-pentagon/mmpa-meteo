/*
 * lora.h
 *
 *  Created on: 8. 5. 2026
 *      Author: PurpleL1ghtbulb, markus
 */

#ifndef LORA_LORA_H_
#define LORA_LORA_H_

/**
 * 							NÁVOD
 *******************************************************************
 *	1) zadej kolik bytů přenášíš v "DATA_LEN"
 *	2) data dej do proměnné "pending_data" (array, length = DATA_LEN); při nenaplnění se zbytek bere jako 0
 *			- pokud chceš z nějakého důvodu poslat méně bytů, ve volání funkce "LoRa_set_data(data[], len)" lze nastavit libovolnou délku dat
 *	optional : 3) zavolej funkci "LoRa_set_data(data[], len) někde před "LoRa_send_data()"- momentálně automaticky ve whilu (nutno asi odstranit při tomto typu užití)
 *	3/4) po přijetí data najdeš v "data_recieved" (když budeš mít štěstí)
 *
 */

#include "stdint.h"
#include "stm32f7xx_hal.h"

/* --- Definice pinů --- */
extern SPI_HandleTypeDef LORA_SPI_HANDLE;

#define LoRa_NSS_GPIO_Port			SPI2_NSS_GPIO_Port
#define LoRa_NSS_Pin				SPI2_NSS_Pin


#define DATA_LEN 61  // kolik bytů posíláme

void LoRa_init();
void LoRa_set_data(uint8_t data[], uint8_t len);
void LoRa_loop();

void LoRa_TIM2_interrupt_handler();
void LoRa_DIO1_interrupt_handler();

#endif /* LORA_LORA_H_ */
