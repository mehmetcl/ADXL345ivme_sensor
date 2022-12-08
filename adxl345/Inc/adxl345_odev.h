/*
 * adxl345_odev.h
 *
 *  Created on: 21 May 2022
 *      Author: CLM
 */

#ifndef ADXL345_ODEV_H_
#define ADXL345_ODEV_H_

void CS_Enable (void);
void CS_Disable (void);
void adxl345_init (void);
void adxl345_write (uint8_t address, uint8_t value);
void adxl345_read (uint8_t address, uint8_t *RxData);


#endif /* ADXL345_ODEV_H_ */
