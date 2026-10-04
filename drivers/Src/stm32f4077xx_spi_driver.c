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
void SPI_Init(SPI_Handle_t *pSPIHandle);
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
