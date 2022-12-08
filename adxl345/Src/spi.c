/*
 * spi.c
 *
 *  Created on: 12 May 2022
 *      Author: CLM
 */
#include "spi.h"

void spi_clock_enable(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
		SPI1_CLOCK_EN();
	else if (pSPIx == SPI2)
		SPI2_CLOCK_EN();
	else if (pSPIx == SPI3)
		SPI3_CLOCK_EN();
}

void spi_init(SPI_Handle_t* phandle_spi){

	spi_clock_enable(phandle_spi->pSPIx);

	uint32_t temp_cr1=0;
	//spı mode
	temp_cr1 |= phandle_spi->spi_config.mode << SPI_CR1_MSTR;
	phandle_spi->pSPIx->CR1 |= temp_cr1;

	temp_cr1=0;
	//directıonal
	if (phandle_spi->spi_config.direction == SPI_DIRECTION_2LINES){

		temp_cr1 &=~ phandle_spi->spi_config.direction << SPI_CR1_RXONLY;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if ( phandle_spi->spi_config.direction == SPI_DIRECTION_2LINES_RXONLY ){
		temp_cr1 |= phandle_spi->spi_config.direction << SPI_CR1_RXONLY;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if (phandle_spi->spi_config.direction == SPI_DIRECTION_1LINE ){
		temp_cr1 &= ~((phandle_spi->spi_config.direction)-1) << SPI_CR1_RXONLY;
		temp_cr1 |= ((phandle_spi->spi_config.direction)-1) << SPI_CR1_BIDIMODE;
		temp_cr1 |= ((phandle_spi->spi_config.direction)-1) << SPI_CR1_BIDIOE;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}

	//datasize
	temp_cr1=0;
	temp_cr1 |= phandle_spi->spi_config.cpol << SPI_CR1_DFF;
	phandle_spi->pSPIx->CR1 |= temp_cr1;
	//cpah
	temp_cr1=0;
	temp_cr1 |= phandle_spi->spi_config.cpha << SPI_CR1_CPHA;
	phandle_spi->pSPIx->CR1 |= temp_cr1;
	//cpol
	temp_cr1=0;
	temp_cr1 |= phandle_spi->spi_config.cpol << SPI_CR1_CPOL;
	phandle_spi->pSPIx->CR1 |= temp_cr1;
	//software slave
	temp_cr1=0;
	if(phandle_spi->spi_config.nss == SPI_SSM_ENABLE)
	{
		temp_cr1 |= phandle_spi->spi_config.mode << SPI_CR1_SSM;
		temp_cr1 |= (1u << SPI_CR1_SSI);
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}

	// baudrate control
	temp_cr1=0;
	if (phandle_spi->spi_config.baudrate_press == IKI){

		temp_cr1 |= phandle_spi->spi_config.baudrate_press << SPI_CR1_BR;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if (phandle_spi->spi_config.baudrate_press == SEKIZ){

		temp_cr1 |= phandle_spi->spi_config.baudrate_press << SPI_CR1_BR;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if (phandle_spi->spi_config.baudrate_press == ONALTI){

		temp_cr1 |= phandle_spi->spi_config.baudrate_press << SPI_CR1_BR;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if (phandle_spi->spi_config.baudrate_press == OTUZIKI){

		temp_cr1 |= phandle_spi->spi_config.baudrate_press << SPI_CR1_BR;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if (phandle_spi->spi_config.baudrate_press == ATMISDORT){

		temp_cr1 |= phandle_spi->spi_config.baudrate_press << SPI_CR1_BR;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if (phandle_spi->spi_config.baudrate_press == YUZYIRMISEKIZ){

		temp_cr1 |= phandle_spi->spi_config.baudrate_press << SPI_CR1_BR;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if (phandle_spi->spi_config.baudrate_press == IKIYUZELLIALTI){

		temp_cr1 |= phandle_spi->spi_config.baudrate_press << SPI_CR1_BR;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}

	//firstbit
	temp_cr1=0;
	if (phandle_spi->spi_config.first_bit == SPI_MSB_FIRST)
	{
		temp_cr1 &=~ phandle_spi->spi_config.first_bit << SPI_CR1_LSB_FIRST;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}
	else if (phandle_spi->spi_config.first_bit == SPI_LSB_FIRST)
	{
		temp_cr1 |= phandle_spi->spi_config.first_bit << SPI_CR1_LSB_FIRST;
		phandle_spi->pSPIx->CR1 |= temp_cr1;
	}



}


void spi_enable_disable(SPI_RegDef_t *pSPIx, int status)
{
	if (status == ENABLE)
		pSPIx->CR1 |= ENABLE << SPI_CR1_SPE;
	else if (status == DISABLE)
		pSPIx->CR1 |= DISABLE << SPI_CR1_SPE;

}

void SPI_Receive (SPI_RegDef_t *pSPIx,uint16_t *data,int size)
{
    while (size)
    {
        while (((pSPIx->SR)&(1u<<SPI_SR_BSY))) {};
        *(volatile uint8_t *)&pSPIx->DR = 0;
        while (!((pSPIx->SR) &(1u<<SPI_SR_RXNE))){};

        *data++= *(volatile uint8_t *)&pSPIx->DR;
        size--;
    }
}

void SPI_Transmission(SPI_RegDef_t *pSPIx,uint16_t *data, int size)
{

    int i=0;
    while (i<size)
    {
    	while(!(pSPIx->SR & (1U<<SPI_SR_TXE)));
        *(volatile uint8_t *)&pSPIx->DR = data[i];
        i++;
    }
    while (!((pSPIx->SR)&(1U<<SPI_SR_TXE))){};
    while (((pSPIx->SR)&(1u<<SPI_SR_BSY))){};



}
