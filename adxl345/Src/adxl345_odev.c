/*
 * adxl345.c
 *
 *  Created on: 21 May 2022
 *      Author: CLM
 */


#include "spi.h"
#include "adxl345_odev.h"
#include "stm32f411xx_gpio.h"




void CS_Enable (void)
{
	gpio_bsrr_pin(GPIOA,NULL ,GPIO_SET_PIN_4);

}

void CS_Disable (void)
{
	gpio_bsrr_pin(GPIOA, GPIO_SET_PIN_4,NULL);
}



void adxl345_write (uint8_t address, uint8_t value)
{
    uint8_t data[2];
    data[0] = address|0x40;
    data[1] = value;

    CS_Enable ();  						// veri gönderimi için cs low çek
    SPI_Transmission(SPI1, data, 2);  	// data gonderme
    CS_Disable ();  					// veri gondermi sonrası cs high çek
}


void adxl345_read (uint8_t address, uint8_t *RxData)
{
    address |= 0x80;
    address |= 0x40;

    CS_Enable ();  							// spi konuşma için veri gönderimi için cs low çek
    SPI_Transmission(SPI1, &address, 1); 	// data gonderme
    SPI_Receive(SPI1, RxData, 6); 			// 6 byte data okudugunu dogrula
    CS_Disable ();							// veri gondermi sonrası cs high çek
}



void adxl345_init (void)
{
	//ADXL345 Confog ayarları yapılmalı
    adxl345_write (0x31, 0x01);  // data_format
    adxl345_write (0x2d, 0x00);  // tüm bitleri sıfırlıyor.
    adxl345_write (0x2d, 0x08);  // measure moduna çekiyoruz.
}
