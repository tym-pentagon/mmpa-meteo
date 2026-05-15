/*
 * lora.c
 *
 *  Created on: 8. 5. 2026
 *      Author: PurpleL1ghtbulb, markus
 */

#include "lora.h"
#include "stdint.h"
#include "stdbool.h"
#include "stm32f7xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim2;

// LoRa   datasheet - https://www.mouser.com/pdfDocs/DS_LLCC68_V10-2.pdf?srsltid=AfmBOoqgLAHkumEmWHl771-ee9YzS_uiDHctigYXl9kTrGpDE34ddVFQ
uint8_t LoRa_SetStandby[] = {0x80, 0x00}; // po resetu do standby RC (takhle to psali v dokumentaci 14.2)
uint8_t LoRa_SetPacketType[] = {0x8A, 0x01}; //packet type = LoRa
uint8_t LoRa_SetRfFrequency[] = {0x86, 0x1B, 0x14, 0x00, 0x00}; //433.25 MH
uint8_t LoRa_SetPaConfig[] = {0x95, 0x02, 0x02, 0x00, 0x01}; //power amplifier = +14dBm
uint8_t LoRa_SetTxParams[] = {0x8E, 0x03, 0x03}; // power = +3dBm, RampTime = 80 mikrosekund
uint8_t LoRa_SetBufferBaseAdress[] = {0x8F, 0x00, 0x00}; //TX i RX používají stejný buffer
uint8_t LoRa_WriteBuffer[DATA_LEN + 2] = {0x0E, 0x00}; // Toto dá data do bufferu a připraví je tak na odeslání, data začínají 3.arg. - nastavuju v main
uint8_t LoRa_SetModulationParams[] = {0x8B, 0x0A, 0x05, 0x06, 0x01}; //SF, BW, CD, lowDataOptimize
uint8_t LoRa_SetPacketParams[] = {0x8C, 0x00, 0x08, 0x00, 0x01, 0x01, 0x00}; //preamble = 8bitů (MSB 0->8 LSB), explicit header(dle Roberta), 5.arg je délka dat které chceme poslat (přepisuju v set_data), CRC on, IQ normal
uint8_t LoRa_SetDioIrqParams[] = {0x08, 0x02, 0x03, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00}; // signály Tx done, RX done a timeout (dal jsem i na DIO1 - nepoužívám) - 0x0001 = TX done, 0x0002 = RX done, 0x0200 = timeout (0x0040 je CRC ERR - nepoužívám)
uint8_t LoRa_WriteRegister_SyncWordMSB[] = {0x0D, 0x07, 0x40, 0x12}; //SyncWord MSB - last arg  (stored in register 0x0740)
uint8_t LoRa_WriteRegister_SyncWordLSB[] = {0x0D, 0x07, 0x41, 0x34}; //SyncWord LSB - last arg  (stored in register 0x0741)
uint8_t LoRa_SetTX[] = {0x83, 0x01, 0xF4, 0x00}; // sets LoRa to TX, 2s timeout ; transmits data in buffer
uint8_t LoRa_SetRX[] = {0x82, 0x04, 0xE2, 0x01}; //sets LoRa to Rx, 00,00,00 means continous Rx (until recieving something), now 5s timeout
uint8_t LoRa_GetRxBufferStatus[] = {0x13, 0x00, 0x00, 0x00}; //returns recieved data length and offset needed to read the data
uint8_t LoRa_ReadBuffer[DATA_LEN+3] = {0x1E}; // from 3.arg (inclusive) are dummy bytes
uint8_t LoRa_ClearIrqStatus[] = {0x02, 0xFF, 0xFF}; //clears all interrupt flags
uint8_t LoRa_GetIrqStatus[] = {0x12, 0x00, 0x00,0x00}; // gets LoRa interrupt status - Rx/Tx done, timeout

// user
uint8_t irq[] = {0x00, 0x00, 0x00, 0x00}; // var for storing the status

typedef enum {
	LORA_TX,
	LORA_WAIT_AFTER_TX,
	LORA_RX,
	LORA_WAIT_AFTER_RX
} LoRa_event_t;

volatile LoRa_event_t LoRa_state = LORA_TX;

void NSS_high() {
	HAL_GPIO_WritePin(LoRa_NSS_GPIO_Port, LoRa_NSS_Pin, 1); // NSS jde do 1
}
void NSS_low() {
	HAL_GPIO_WritePin(LoRa_NSS_GPIO_Port, LoRa_NSS_Pin, 0); // NSS jde do 0
}
void wait_BUSY() {
	while(HAL_GPIO_ReadPin(LoRa_BUSY_GPIO_Port, LoRa_BUSY_Pin) == 1); // wait for LoRa BUSY to go low
}


void transmit_SPI_variable(uint8_t *name, uint16_t len) { //komunikace s LoRou
	wait_BUSY();
	NSS_low();
	HAL_SPI_Transmit(&LORA_SPI_HANDLE, name, len, 100);
	NSS_high();
	wait_BUSY();
}

void transmit_recieve_SPI_variable(uint8_t *Tx_name, uint8_t *Rx_name, uint8_t size) {
	wait_BUSY();
	NSS_low();
	HAL_SPI_TransmitReceive(&LORA_SPI_HANDLE, Tx_name, Rx_name, size, 100);
	NSS_high();
	wait_BUSY();
}

void LoRa_set_data(uint8_t data[], uint8_t len) { // set data for transmission
	LoRa_SetPacketParams[4] = len;
	for (int i = 0; i<len; i++) {
		LoRa_WriteBuffer[i+2] = data[i];
	}
	transmit_SPI_variable(LoRa_SetPacketParams, sizeof(LoRa_SetPacketParams)); //needs to be here because it carries data len
}

__weak void LoRa_Rx_callback(uint8_t data[], uint8_t len) {
    /* Defaultně prázdné */
}

void LoRa_process_data() {
	/* Stores data in data_recieved and toggles LED */
	uint8_t RecRxBufferStatus[4]; //store here
	transmit_recieve_SPI_variable(LoRa_GetRxBufferStatus, RecRxBufferStatus, 4);

	// RecRxBufferStatus[3] = FIFO offset, RecRxBufferStatus[2] = payload length
	uint8_t payload_len = RecRxBufferStatus[2];
	LoRa_ReadBuffer[1] = RecRxBufferStatus[3]; // gets the FiFo offset - knows where to start reading data

	// Read actual data
	uint8_t RecReadBuffer[3 + payload_len];

	transmit_recieve_SPI_variable(LoRa_ReadBuffer, RecReadBuffer, 3 + payload_len);

	uint8_t data_received[DATA_LEN]; // Recieved data

 	for (uint8_t i = 0; i < payload_len; i++) {
 		data_received[i] = RecReadBuffer[3+i]; //get the data (first 3 bytes of RecReadBuffer are status and dummy)
	}

 	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);

 	LoRa_Rx_callback(data_received, sizeof(data_received));
}

void LoRa_init() {
	NSS_high();

	/* LoRa reset on startup */
	HAL_GPIO_WritePin(LoRa_RESET_GPIO_Port, LoRa_RESET_Pin, 0);
	HAL_Delay(5);
	HAL_GPIO_WritePin(LoRa_RESET_GPIO_Port, LoRa_RESET_Pin, 1);
	HAL_Delay(10); // Wait for chip to boot
	wait_BUSY();

	/* Trasmit all the variables and config through SPI */
	transmit_SPI_variable(LoRa_SetStandby, sizeof(LoRa_SetStandby));
	transmit_SPI_variable(LoRa_SetPacketType, sizeof(LoRa_SetPacketType));
	transmit_SPI_variable(LoRa_SetRfFrequency, sizeof(LoRa_SetRfFrequency));
	transmit_SPI_variable(LoRa_SetPaConfig, sizeof(LoRa_SetPaConfig));
	transmit_SPI_variable(LoRa_SetTxParams, sizeof(LoRa_SetTxParams));
	transmit_SPI_variable(LoRa_SetBufferBaseAdress, sizeof(LoRa_SetBufferBaseAdress));
	transmit_SPI_variable(LoRa_SetModulationParams, sizeof(LoRa_SetModulationParams));
	transmit_SPI_variable(LoRa_SetDioIrqParams, sizeof(LoRa_SetDioIrqParams));
	transmit_SPI_variable(LoRa_WriteRegister_SyncWordMSB, sizeof(LoRa_WriteRegister_SyncWordMSB));
	transmit_SPI_variable(LoRa_WriteRegister_SyncWordLSB, sizeof(LoRa_WriteRegister_SyncWordLSB));
}

void LoRa_start_Rx() {
	/* Starts Rx */
	transmit_SPI_variable(LoRa_ClearIrqStatus, sizeof(LoRa_ClearIrqStatus));
	transmit_SPI_variable(LoRa_SetRX, sizeof(LoRa_SetRX));
}

void LoRa_send_data() {
	/* Transmits WriteBuffer and starts Tx */
	transmit_SPI_variable(LoRa_WriteBuffer, sizeof(LoRa_WriteBuffer));
	transmit_SPI_variable(LoRa_ClearIrqStatus, sizeof(LoRa_ClearIrqStatus));
	transmit_SPI_variable(LoRa_SetTX, sizeof(LoRa_SetTX));
}

void LoRa_loop() {
	/* Tato funkce se spouští z hlavního cyklu a obstarává všechny přenosy LoRa */
	switch (LoRa_state) {
		case LORA_TX:
			LoRa_send_data();
			LoRa_state = LORA_WAIT_AFTER_TX;
			break;

		case LORA_WAIT_AFTER_TX:
			break;

		case LORA_RX:
			LoRa_start_Rx();
			LoRa_state = LORA_WAIT_AFTER_RX;
			break;

		case LORA_WAIT_AFTER_RX:
			break;
	}
}

void LoRa_DIO1_interrupt_handler() {
	transmit_recieve_SPI_variable(LoRa_GetIrqStatus, irq, 4);

	if (irq[3] & 0x01) {
	    // TX done (data transmitted)
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
		LoRa_state = LORA_RX; // Už může přijímat data
	}

	if (irq[3] & 0x02) {
	    // RX done (data received)
	    LoRa_process_data();

	    /* Start timer to interrupt */
	    __HAL_TIM_SET_COUNTER(&htim2, 0);
	    HAL_TIM_Base_Start_IT(&htim2);
	}

	if (irq[2] & 0x02) {
	    // Timeout
		if (LoRa_state == LORA_WAIT_AFTER_TX) {
			// Nepodařilo se odeslat packet
			// TODO: Error handling
		}
		if (LoRa_state == LORA_WAIT_AFTER_RX) {
			LoRa_state = LORA_TX;
		}
	}

	transmit_SPI_variable(LoRa_ClearIrqStatus, sizeof(LoRa_ClearIrqStatus));
}

void LoRa_TIM2_interrupt_handler() {
	/* LoRa může odesílat data */
	LoRa_state = LORA_TX;
	HAL_TIM_Base_Stop_IT(&htim2);
}
