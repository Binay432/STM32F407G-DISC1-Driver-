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
	// Enable the spi peripheral clock
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	// 1. configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR ;

	// 2. configure the bus
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// BIDI mode should be cleared
		tempreg &= ~( 1<< SPI_CR1_BIDIMODE);
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// BIDI mode(15 bit of SPI_CR1) should be set
		tempreg |= ( 1<<SPI_CR1_BIDIMODE );
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		// BIDI mode should be cleared
		tempreg &= ~( 1<< SPI_CR1_BIDIMODE);

		// RXONLY bit(10) must be set
		tempreg |= ( 1<< SPI_CR1_RXONLY);
	}

	// 3. configure the speed
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	// 4. configure the data frame format
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	// 5. configure the cpol
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	// 6. configure the cpha
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	// 7. configure the ssm
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempreg;
}
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * SPI_PeripheralControl
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
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= ( 1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &= ~( 1 << SPI_CR1_SPE);
	}
}


void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= ( 1 << SPI_CR1_SSI);
	}else
	{
		pSPIx->CR1 &= ~( 1 << SPI_CR1_SSI);
	}
}
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
	* @Note 			- This is a blocking call cz of 2 while loop
	*
 */

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if (pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while  (Len > 0)
	{
		// 1. wait until TXE is set
		// if it's set as 1, (pSPIx->SR & (1<<1)) will be 0
				//		while(!(pSPIx->SR & (1<<1)));
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// 2. Check the bit 16 bit in CR1
			// Logic : Check the DFF bit (11) in SPI_CR1 register
		if((pSPIx->CR1 & (1<<SPI_CR1_DFF)))
		{
			// 16 bit DFF
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len-- ;
			Len--;
			(uint16_t*)pTxBuffer++;
		}else
		{
			// 8 bit DFF
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}

	}
}
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
