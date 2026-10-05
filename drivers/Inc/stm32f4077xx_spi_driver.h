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

/*
 * @SPI DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER  1
#define SPI_DEVICE_MODE_SLA		0


/*
 * @SPI_BusConfig: SPI_CR1 - BIT 15  (O -BIDIRECTIONAL ) AND 14, 10 (Simplex)
 *
 */

#define SPI_BUS_CONFIG_FD						1
#define SPI_BUS_CONFIG_HD						2
//#define SPI_BUS_CONFIG_SIMPLEX_TXONLY			3 // no need of it , as it is a full duplex with MISO removed
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY			3


/*
 * @SPI_SclkSpeed : SPI_CR1 (BIT 3 TO 5)
 */
#define SPI_SCLK_SPEED_DIV2						0 // DIV2 = Divided by 2
#define SPI_SCLK_SPEED_DIV4						1
#define SPI_SCLK_SPEED_DIV8						2
#define SPI_SCLK_SPEED_DIV16					3
#define SPI_SCLK_SPEED_DIV32					4
#define SPI_SCLK_SPEED_DIV64					5
#define SPI_SCLK_SPEED_DIV128					6
#define SPI_SCLK_SPEED_DIV256					7

/*
 *@SPI_DFF: SPI_CR1 : BIT 11
 */
#define SPI_DFF_8ITS 		0	//DEFAULT
#define SPI_DFF_16BITS		1

/*
 * @SPI_CPOL: SPI1_CPOL: BIT 1
 */
#define SPI_CPOL_HIGH		1
#define SPI_CPOL_LOW 		0

/*
 * @SPI_CPHA: SPI1_CR1: BIT 0
 */
#define SPI_CPHA_HIGH		1
#define SPI_CPHA_LOW		0


/*
 * @SPI_SSM": SP1_CR1: Bit 9
 */
#define SPI_SSM_EN		1
#define SPI_SSM_DI		0 // default


/*
 *	SPI related status flags definition
 */
#define SPI_TXE_FLAG 	( 1 << SPI_SR_TXE)


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
void SPI_Init(SPI_Handle_t *pSPIHandle);
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
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);




#endif /* INC_STM32F4077XX_SPI_DRIVER_H_ */
