/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: May 19, 2026
 *      Author: sahbi
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"	// driver header file should contain the mcu specific header file


/*
 * Configuration items for user application
 */
typedef struct
{
	uint8_t GPIO_PinNumber;			/*!< possible values from @GPIO_PIN_NUMBERS >*/
	uint8_t GPIO_PinMode;			/*!< possible values from @GPIO_PIN_MODES >*/
	uint8_t GPIO_PinSpeed;			/*!< possible values from @GPIO_PIN_SPEED >*/
	uint8_t GPIO_PinPuPdControl; 	/*!< possible values from @GPIO_PIN_PUPD_CONFIGURATION >*/
	uint8_t GPIO_Pin0Ptype;			/*!< possible values from @GPIO_PIN_OPTYPES >*/
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

/*
 * This is a Handle structure for a GPIO Pin
 */
typedef struct
{
	// pointer to hold the base address of the GPIO peripheral
	// Actual Variable naming = pGPIOBaseAddr , p is pointer indication
	GPIO_RegDef_t *pGPIOx; 	/* <this holds the base address of the GPIO Port to which the pin belongs >*/
	GPIO_PinConfig_t GPIO_PinConfig; 	// This variable hold pin configuration settings
}GPIO_Handle_t ;


/*
 * @GPIO_PIN_MODES
 * GPIO Pin Possible modes
 * Reference Manual : GPIOx_MODER
 */
#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG	3

/*
 * Some other possible modes
 */
#define GPIO_MODE_IT_FT		4 // Interrput : input - > falling edge
#define GPIO_MODE_IT_RT 	5 // Interrupr : input -> Rising edge
#define GPIO_MODE_IT_RFT	6 // Interrupt -> Rising edge falling edge trigger


/*
 * @GPIO_PIN_OPTYPES
 * GPIO Pin possible output types
 * Reference Manual: 8.4.2 GPIO port output type register (GPIOx_OTYPER)
*/
#define GPIO_OP_TYPE_PP 	0 //PUSH PULL MODE
#define GPIO_OP_TYPE_OD		1 //OPEN DRAIN

/*
 * @GPIO_PIN_SPEED
 * GPIO PIN POSSIBLE OUTPUT SPEED
 * Reference Manual: 8.4.3 GPIO port output speed register (GPIOx_OSPEEDR)
*/
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM 	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

/*
 * @GPIO_PIN_PUPD_CONFIGURATION
 * GPIO PIN PULL UP AND PULL DOWN CONFIGURATION MACROS
 * Reference Manual: 8.4.4 GPIO port pull-up/pull-down register (GPIOx_PUPDR)
*/
#define GPIO_NO_PUPD		0	// PULL UP PULL DOWN
#define GPIO_PIN_PU			1	// PULL UP
#define GPIO_PIN_PD			2	// PULL DOWN


/*
 * @GPIO_PIN_NUMBERS
 * GPIO Pin NUmbers
*/
#define GPIO_PIN_NO_0 		0
#define GPIO_PIN_NO_1  		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3 		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5 		5
#define GPIO_PIN_NO_6 		6
#define GPIO_PIN_NO_7  		7
#define GPIO_PIN_NO_8 		8
#define GPIO_PIN_NO_9 		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11 		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13 		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15 		15


/***************************************************************************************
 * 							APIs supported by this driver
 ***************************************************************************************/
/*
 *  Peripheral Clock Setup
 *  Function: to enable or disable peripherial clock control for the given base
 *   address of gpio
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);


/*
 * Init and De-init (Sending back to reset handle)
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value); // value is either 0 or 1
void GPI0_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);// Interrupt configuration
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriotity); // Set the IRQ priority order
void GPIO_IRQHandling(uint8_t PinNumber); // Interrupt handling









#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
