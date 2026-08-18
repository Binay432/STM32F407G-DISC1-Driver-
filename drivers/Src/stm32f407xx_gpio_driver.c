/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: May 19, 2026
 *      Author: sahbi
 */

#include "stm32f407xx_gpio_driver.h" 	// driver source file should contain driver header file





/*
 *  Peripheral Clock Setup
 */

/****************************************************************
 * @fu				- GPIO_PeripheralControl
 *
 * @brief 			- This function enables or disables peripheral clock for the given GPIO Port
 *
 * @param[in]		- base address of the gpio peripheral
 *
 * @param[in]		- ENABLE or DISABLE macros
 *
 * @return			- None
 *
 * @Note 			- None
 *
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}
	}
}


/*
 * Init and De-init (Sending back to reset handle)
 */

/****************************************************************
 * @fu				- GPIO_Init
 *
 * @brief 			- This function configure the given port
 *
 * @param[in]		- gpio_hanGPIO_Handle_t contains the base address and configuration
 *
 * @return			- None
 *
 * @Note 			- GPIO_Handle_t struct is in driver header file
 *
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	// 1. Configure the gpio pin mode

		// If the pin mode is not interrupt mode
	if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		// 2 represent number of bits, since pinmode is of 2 bits long, thus the in number is multiplied by 2
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle ->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing the required pin before setting
		pGPIOHandle->pGPIOx->MODER |= temp;	// setting
	}else
	{
		// this part will code later: interrupt mode
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// 1. Configure the FTSR
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

			// Clear the corresponding RTSR bit
			EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// 1. Configure the RTSR
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

			// Clear the corresponding FTSR bit
			EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			// 1. Configure the FTSR
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

			// SET the corresponding RTSR bit
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}

		// 2. Configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)/4;
		uint8_t temp2 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)%4;
		uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG ->EXTICR[temp1] = portCode << (temp2 * 4);


		// 3. Enable the EXTI interrupt delivery using IMR (Interrupt Mask Register)
		EXTI->IMR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	// 2. Configure the speed
	temp = 0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle ->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	// 3. Configure the pupd settings
	temp = 0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle ->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR |= temp;


	// 4. Configure the output type
		// Need single bit
	temp = 0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_Pin0Ptype << (2* pGPIOHandle ->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	// 5. Configure the alt functionality : Pin mode is alt mode
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		// 1. Out of two alt register (GPIOx_AFRL (0-7) and GPIOx_AFRH (8-15): one to be choosen
		// AFR[2] - set in register header file, with AFR[1] as the AFRH
		// 4 bits dedicated by each pin
		// ref: udemy : 97
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /8; // to choose which alt register, 1 for higher and 0 for lower
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber %8; // the bit to be set
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4*temp2)); // Clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2));
	}
}

/****************************************************************
 * @fu				- GPIO_DeInit
 *
 * @brief 			- This function reset the given port
 *
 * @param[in]		- pGPIOx, the base address of the port
 *
 * @return			- None
 *
 * @Note 			- De initialize the port means , resetting all the register of the port
 * 					- In order to reset all the register of the port/peripheral, we have to refer to the respective RCC register of the port/peripheral
 * 					- For GPIO PORT , RCC_AHB1RSTR should be used
 * 					- Resetting mean -> make 1 then back to 0,
 *
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if (pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}else if (pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}else if (pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}

/*
 * Data read and write
 */
/****************************************************************
 * @fu				- GPIO_ReadFromInputPin
 *
 * @brief 			- This function read the status of the given pin number of the given port
 *
 * @param[in]		- base address of the gpio peripheral
 *
 * @param[in]		- pin number
 *
 * @return			- boolean value either 1 or 0 in 1 byte value
 *
 * @Note 			- None
 *
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}

/****************************************************************
 * @fu				- GPIO_ReadFromInputPort
 *
 * @brief 			- This function read of the given port
 *
 * @param[in]		- base address of the gpio peripheral
 *
 * @return			- 16 bits value
 *
 * @Note 			- None
 *
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}

/****************************************************************
 * @fu				- PIO_WriteToOutputPin
 *
 * @brief 			- This function write the bit value to the corresponding pin number of the port
 *
 * @param[in]		- pGPIOx :  base address of the port
 * 					- PinNumber : Corresponding pin number at which the bit value to be write
 * 					- Value : Either 0 or 1
 *
 * @return			- None
 *
 * @Note 			- None
 *
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		// write 1 to the output data register at the bit field corresponding to the pin number of the given port
		pGPIOx->ODR |= (1<<PinNumber);
	}else
	{
		// write 0
		pGPIOx->ODR &= ~(1<<PinNumber);
	}
}

/****************************************************************
 * @fu				- GPI0_WriteToOutputPort
 *
 * @brief 			- This function write the value to the corresponding port
 *
 * @param[in]		- pGPIOx :  base address of the port
 * 					- Value : 16 bit value
 *
 * @return			- None
 *
 * @Note 			- None
 *
 */
void GPI0_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx ->ODR = Value;
}

/****************************************************************
 * @fu				- GPIO_ToggleOutputPin
 *
 * @brief 			- This function toggle the value to the corresponding pin of the port
 *
 * @param[in]		- pGPIOx :  base address of the port
 * 					- PinNumber : Corresponding pin number
 *
 * @return			- None
 *
 * @Note 			- None
 *
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx ->ODR ^= (1<<PinNumber);
}



/*
 * IRQ IT Configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (IRQNumber <= 31)
		{
			// progrma ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);

		} else if  (IRQNumber > 31 && IRQNumber < 64)
		{
			// program ISER1 register

			*NVIC_ISER1 |= (1 << IRQNumber%32 );

		} else if  (IRQNumber >= 64 && IRQNumber < 96)
		{
			// program ISER2 register
			*NVIC_ISER2 |= (1 << IRQNumber%64 );
		}
	}else
	{
		if (IRQNumber <= 31)
		{
			// progrma ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);

		} else if  (IRQNumber > 31 && IRQNumber < 64)
		{
			// program ICER1 register

			*NVIC_ICER1 |= (1 << IRQNumber%32 );

		} else if  (IRQNumber >= 64 && IRQNumber < 96)
		{
			// program ICER2 register
			*NVIC_ICER2 |= (1 << IRQNumber%64 );
		}
	}
}

/*
 * Set the IRQ Priority order
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriotity)
{
	// 1. Find oyt the ipr register
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber%4;

	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriotity << (8*iprx_section));

}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	// Clear the exti pr register corresponding to the pin number
	if (EXTI->PR & (1 << PinNumber))
	{
		// clear the pending register
		EXTI->PR |= ( 1 << PinNumber);

	}
}
