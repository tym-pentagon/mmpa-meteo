/*
 * gps.h
 *
 *  Created on: 18. 5. 2026
 *      Author: markus
 */

#ifndef GPS_GPS_H_
#define GPS_GPS_H_

void gps_init();
void gps_loop();
void gps_UART_RxCpltCallback_handler();

#endif /* GPS_GPS_H_ */
