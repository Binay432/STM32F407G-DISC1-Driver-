/*
 * 006pi_txonly_arduino.c
 *
 *  Created on: Oct 6, 2026
 *      Author: sahbi
 */



/*
 * A test code just to test the spi tx
 * Problem : Test the spi_senddata api to send the string 'Hello World'
 * and use the below configuration
 * SPI-2 Master mode
 * SCLK = max possible
 * DFF = 0 and DFF = 1
 *
 *
 *
 * Solution  : Pin required?
 * 				: Since no slave management, only MOSI and sck will be needed
 *
 *
 * Steps :
 * 		1. Find the GPIO pins over which SPI2 Can communicate
 * 			: 1. Consult the data sheet
 * 			: 2. PB14 ---> MISO
 * 			: 3. PB15 ---> MOSI
 * 			: 4. PB13 ---> SCLK
 * 			: 5. PB12 ---> NSS
 * 			: ALT Function mode: 5
 */
#include "stm32f407xx.h"
#include <string.h>



void delay(void)
{
	for(uint32_t i = 0; i<500000; i++);
}

void SPI2_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_Pin0Ptype = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; // OPTIONAL
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	//MOSI
//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
//	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);
}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; // 8MHz clk
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8ITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW ;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;	//HARDWARE slave management enabled for NSS pin as for this test we have no slave


	SPI_Init(&SPI2handle);
}

void GPIOButtonInit()
{
	GPIO_Handle_t GpioBtn;

	// button pin configuration
	GpioBtn.pGPIOx = GPIOA;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	//GpioBtn.GPIO_PinConfig.GPIO_Pin0Ptype = GPIO_OP_TYPE_OD;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; // Already a pull down resistor connected to push buttom

	GPIO_Init(&GpioBtn);
}
int main(void)
{
	char user_data[] = "Hello World!";
	// function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	// peripheral configuration
	SPI2_Inits();

	SPI_SSOEConfig(SPI2, ENABLE);

	while(1)
	{
		while(! (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)));

		delay();
		// Just initializing the SPI doesn't mean the spi is enabled ,
		//for this it has dedicated bit (bit 6) ,
		//cz if it's enable while initializing , spi will be busy for communication , rather that configuration .
		SPI_PeriClockControl(SPI2, ENABLE);

		// First send length information
		uint8_t dataLen = strlen(user_data);
		SPI_SendData(SPI2, &dataLen, 1);
		// Send the data
		SPI_SendData(SPI2, (uint8_t*)user_data,strlen(user_data));

		// Confirm SPI is not busy
		while( SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG ));

		// Disable the SPI2 peripheral
		SPI_PeriClockControl(SPI2, DISABLE);

	}


	return 0;
}
