/*
 * stm32f4077xx_spi_driver.c
 *
 *  Created on: Sep 7, 2026
 *      Author: sahbi
 */

#include "stm32f4077xx_spi_driver.h"

/*
 *  Peripheral Clock Setup
 *
 *  *****************************************************************
	* @fu				-
	*
	* @brief 			-
	*
	* @param[in]		-
	*
	* @param[in]		-
	*
	* @return			- None
	*
	* @Note 			- None
	*
 */


void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if (pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}else if (pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if (pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}else if (pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}
}


/*
 * Init and De-init (Sending back to reset handle)
*****************************************************************
	* @fu				-
	*
	* @brief 			-
	*
	* @param[in]		-
	*
	* @param[in]		-
	*
	* @return			- None
	*
	* @Note 			- None
	*
 *
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// Configure the SPI_CR1
	// Temporary register to store settings
	uint32_t tempreg = 0;

	// 1. configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;

	// 2. configure the bus
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// BIDI mode should be cleared
		tempreg &= ~( 1<< 15);
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// BIDI mode(15 bit of SPI_CR1) should be set
		tempreg |= ( 1<<15 );
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		// BIDI mode should be cleared
		tempreg &= ~( 1<< 15);

		// RXONLY bit(10) must be set
		tempreg |= ( 1<<10 );
	}

	// 3. configure the speed
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;

	// 4. configure the data frame format
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << 11;

	// 5. configure the cpol
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << 1;

	// 6. configure the cpha
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << 0;

	// 7. configure the ssm
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << 9;

	pSPIHandle->pSPIx->CR1 = tempreg;
}
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data Send and Receive
 * Can have 3 different methodologies (Polling, Interrupt, DMA)
 * pTxBuffer --> Address of the tx data buffer
 * Len --> how many bytes this api should send
 *
 * *****************************************************************
	* @fu				-
	*
	* @brief 			-
	*
	* @param[in]		-
	*
	* @param[in]		-
	*
	* @return			- None
	*
	* @Note 			- None
	*
 */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);


/*
 * IRQ Configuration and ISR handling
 *
 *****************************************************************
 * @fu				-
 *
 * @brief 			-
 *
 * @param[in]		-
 *
 * @param[in]		-
 *
 * @return			- None
 *
 * @Note 			- None
 *
 */

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);// Interrupt configuration
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriotity); // Set the IRQ priority order
void SPI_IRQHandling(SPI_Handle_t *pHandle); // Interrupt handling


/*
 * Other Peripheral Control APIs
  *****************************************************************
 * @fu				-
 *
 * @brief 			-
 *
 * @param[in]		-
 *
 * @param[in]		-
 *
 * @return			- None
 *
 * @Note 			- None
 *
 */
