/*
 * spi.h
 *
 *  Created on: 12 May 2022
 *      Author: CLM
 */

#ifndef SPI_H_
#define SPI_H_

#include<stdint.h>
#include"stm32f411xx.h"

typedef struct {
	uint8_t mode;
	uint8_t direction;
	uint8_t data_size;
	uint8_t cpol;
	uint8_t cpha;
	uint8_t nss;
	uint8_t baudrate_press;
	uint8_t first_bit;
}SPI_Config_t;


typedef struct {
	SPI_RegDef_t *pSPIx;
	SPI_Config_t spi_config;
}SPI_Handle_t;

#define ENABLE							1
#define DISABLE							0

#define SPI_DEV_SLAVE					0
#define SPI_DEV_MASTER					1

#define SPI_SSM_DISABLE					0
#define SPI_SSM_ENABLE					1

#define SPI_DIRECTION_2LINES			0
#define SPI_DIRECTION_2LINES_RXONLY 	1
#define SPI_DIRECTION_1LINE				2

#define SPI_DATASIZE_8BIT				0
#define	SPI_DATASIZE_16BIT				1

#define SPI_POLARITY_LOW				0
#define	SPI_POLARITY_HIGH				1

#define SPI_PHASE_LOW					0
#define	SPI_PHASE_HIGH					1

#define SPI_MSB_FIRST					0
#define SPI_LSB_FIRST					1

#define IKI								0b000
#define	DORT							0b001
#define	SEKIZ							0b010
#define	ONALTI							0b011
#define	OTUZIKI							0b100
#define	ATMISDORT						0b101
#define	YUZYIRMISEKIZ					0b110
#define	IKIYUZELLIALTI					0b111




typedef enum {SPI_CR1_CPHA,SPI_CR1_CPOL,SPI_CR1_MSTR,SPI_CR1_BR,
	SPI_CR1_SPE=6,SPI_CR1_LSB_FIRST,SPI_CR1_SSI,SPI_CR1_SSM,
	SPI_CR1_RXONLY,SPI_CR1_DFF,SPI_CR1_CRCNEXT,SPI_CR1_CRCEN,
	SPI_CR1_BIDIOE,SPI_CR1_BIDIMODE}SPI_CR1;

typedef enum {SPI_BR_PR2,SPI_BR_PR4,SPI_BR_PR8,SPI_BR_PR16,SPI_BR_PR32,SPI_BR_PR64,
	SPI_BR_PR128,SPI_BR_PR256}SPI_BR;

typedef enum {SPI_SR_RXNE,SPI_SR_TXE,SPI_SR_CHSIDE,SPI_SR_UDR,
				SPI_SR_CRCERR,SPI_SR_MODF,SPI_SR_OVR,SPI_SR_BSY,SPI_SR_FRE}SPI_SR;


void spi_init(SPI_Handle_t* phandlespi);
void spi_clock_enable(SPI_RegDef_t *pSPIx);
void spi_enable_disable(SPI_RegDef_t *pSPIx, int status);
void SPI_Receive (SPI_RegDef_t *pSPIx,uint16_t *data,int size);
void SPI_Transmission(SPI_RegDef_t *pSPIx,uint16_t *data, int size);


#endif /* SPI_H_ */
