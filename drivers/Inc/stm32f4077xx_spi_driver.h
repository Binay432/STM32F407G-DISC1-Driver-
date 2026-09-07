/*
 * stm32f4077xx_spi_driver.h
 *
 *  Created on: Sep 7, 2026
 *      Author: sahbi
 */

#ifndef INC_STM32F4077XX_SPI_DRIVER_H_
#define INC_STM32F4077XX_SPI_DRIVER_H_


#include "stm32f407xx.h"
/*
 *  Configuration  structure for SPIx peripheral
 */
typedef struct
{
	uint8_t SPI_DeviceMode;			// SPI either slave or master mode
	uint8_t SPI_BusConfig; 			// Half duplex, Full duplex , Simplex
	uint8_t SPI_SclkSpeed; 			// Serial Clock Speed
	uint8_t SPI_DFF; 				// Data Frame Format (8 bit vs 16 bit)
	uint8_t SPI_CPOL;				// Sclk Polarity
	uint8_t SPI_CPHA;				// Sclk Phase
	uint8_t SPI_SSM; 				// Type of slave management ( hardware or software)
}SPI_Config_t;


/*
 * Handle structure for SPIx Peripheral
 */
typedef struct
{
	SPI_RegDef_t	*pSPIx;
	SPI_Config_t	SPIConfig;
}SPI_Handle_t;



/*****************************************************************************
 * 								API's supported by this driver
 * ***************************************************************************
 */
/*
 *  Peripheral Clock Setup
 *  Function: to enable or disable peripherial clock control for the given base
 *   address of SPI
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);


/*
 * Init and De-init (Sending back to reset handle)
 */
void SPI_Init(SPI_RegDef_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data Send and Receive
 * Can have 3 different methodologies (Polling, Interrupt, DMA)
 * pTxBuffer --> Address of the tx data buffer
 * Len --> how many bytes this api should send
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);


/*
 * IRQ Configuration and ISR handling
 */

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);// Interrupt configuration
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriotity); // Set the IRQ priority order
void SPI_IRQHandling(SPI_Handle_t *pHandle); // Interrupt handling


/*
 * Other Peripheral Control APIs
 */





#endif /* INC_STM32F4077XX_SPI_DRIVER_H_ */
