/*
 * 003Led_External_Button.c
 *
 *  Created on: Jul 10, 2026
 *      Author: sahbi
 */


/*
 * 002led_button.c
 *
 *  Created on: Jul 9, 2026
 *      Author: sahbi
 */
#include "stm32f407xx.h"

void delay(void)
{
	for(uint32_t i = 0; i<500000; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed, GpioBtn;
	uint8_t btnStat  = 0;

	// led pin configuration
	GpioLed.pGPIOx = GPIOB;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_Pin0Ptype = GPIO_OP_TYPE_OD;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//GPIO_PeriClockControl(GPIOB, ENABLE);


	// button pin configuration
	GpioBtn.pGPIOx = GPIOB;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	//GpioBtn.GPIO_PinConfig.GPIO_Pin0Ptype = GPIO_OP_TYPE_OD;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOB, ENABLE);
	GPIO_Init(&GpioLed);
	GPIO_Init(&GpioBtn);


	while(1)
	{
		btnStat  = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_13);
		if (btnStat == ENABLE)
		{
			GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_12, DISABLE);
		}else
		{
			GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_12, ENABLE);
		}
	}

}
