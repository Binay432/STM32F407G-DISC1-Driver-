/*
 * stm32f407xx.h
 *
 *  Created on: May 3, 2026
 *      Author: sahbi
 *
 *      This file gonna keep the base address of the various
 *      memeories of the microontrollers, registers and so on !
 *
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include<stdint.h>			// because we have short hand notation data type , like uint32_t
#define __vo volatile

/********************************************START: Processor Specific Details *************************************
 *
 * ARM Cortes Mx Processor NVUC ISERx register Addresses
 */


#define NVIC_ISER0 ( (__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1 ( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2 ( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3 ( (__vo uint32_t*)0xE000E10C )

/*
 * ARM Cortes Mx Processor NVUC ICERx register Addresses
 */
#define NVIC_ICER0 ( (__vo uint32_t*)0XE000E180 )
#define NVIC_ICER1 ( (__vo uint32_t*)0XE000E184 )
#define NVIC_ICER2 ( (__vo uint32_t*)0XE000E188 )
#define NVIC_ICER3 ( (__vo uint32_t*)0XE000E18C )

/*
 * ARM Cortes Mx Processor Priotity Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR (( __vo uint32_t*) 0xE000E400)


/*
 * ARM Cortes Mx Processor number of priority bits implemented in priority register
 */
#define NO_PR_BITS_IMPLIMENTED 		4

/*
 * base addresses of flash and SRAM memories
 * Flash Memory is also known as Main Memory
 * System Memory = ROM
 */
#define FLASH_BASEADDR				0x08000000U   	// By default the compiler treated number as a signed integer but the addresses are unsigned so , U is added
#define SRAM1_BASEADDR              0x20000000U		// 112 KB ( 112 *1024 = 114,688 KB = 0x1C000 in hexadecimal = 0x20000000 + 0x1C000 = 0x2001C000 is the base address of SRAM 2
#define SRAM2_BASEADDR				0x2001C000U
#define ROM_BASEADDR				0x1FFF0000U
#define SRAM           				SRAM1_BASEADDR


/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASEADDR				0x40000000U
#define APB1PERIPH_BASEADDR 		PERIPH_BASEADDR	// For I2C1, I2C2, I2C3, SPI2, SPI3, USART2, USART3, UART4, UART5
#define APB2PERIPH_BASEADDR			0x40010000U		// For SPI1, USART1, USART6, EXTI, SYSCFG

#define AHB1PERIPH_BASEADDR			0x40020000U		// For GPIO port
#define AHB2PERIPH_BASEADDR 		0x50000000U


/*
 * Base Address of peripherals which are hanging on AHB1 bus
 */
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000)	// BASE_ADDRESS + OFFSET, OFFSET here is 0x0000 cz its the first peripherial For AHB1 bus
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR				(AHB1PERIPH_BASEADDR + 0x2000)

#define RCC_BASEADDR 				(AHB1PERIPH_BASEADDR + 0x3800)

/*
 * Base Address of peripherals which are hanging on APB1 bus
 */
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400)	// Support synchronous
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800)

#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00)	// Doesn't support synchronous
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000)


/*
 * Base Address of peripherals which are hanging on APB2 bus
 */
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400)




/*
 * *********************** Peripheral register definition structures *************************************
 * Note : Registers of a peripherals are specific to MCU
 * GPIO_RegDef  = GPIO register definition
 * unit32_t is because the register are of 4 bytes
 * peripheral register are highly volatile in nature, therefore volatile keyword is used
 */


typedef struct
{
	__vo uint32_t MODER;		// GPIO port mode register									Address offset: 0x00
	__vo uint32_t OTYPER;		// GPIO port output type register	 						Address offset: 0x04
	__vo uint32_t OSPEEDR;		// GPIO port output speed register							Address offset: 0x08
	__vo uint32_t PUPDR;		// GPIO port pull-up/pull-down register						Address offset: 0x0C
	__vo uint32_t IDR;			// GPIO port input data register							Address offset: 0x10
	__vo uint32_t ODR;			// GPIO port output data register							Address offset: 0x14
	__vo uint32_t BSRR;			// GPIO port bit set/reset register							Address offset: 0x18
	__vo uint32_t LCKR;			// GPIO port configuration lock register					Address offset: 0x1C
	__vo uint32_t AFR[2]; 		// GPIO alternate function low register  (AFR[0] = AFRL) 	Address offset: 0x20
								// GPIO alternate function high register (AFR[1] = AFRH) 	Address offset: 0x24
}GPIO_RegDef_t;


/*
 * **************************** RCC peripheral register***********************
 */

typedef struct
{
	__vo uint32_t CR;			// RCC clock control register									Address offset: 0x00
	__vo uint32_t PLLCFGR;		// RCC PLL configuration register								Address offset: 0x04
	__vo uint32_t CFGR;			// RCC clock configuration register								Address offset: 0x08
	__vo uint32_t CIR;			// RCC clock interrupt register									Address offset: 0x0C
	__vo uint32_t AHB1RSTR;		// RCC AHB1 peripheral reset register							Address offset: 0x10
	__vo uint32_t AHB2RSTR;		// RCC AHB2 peripheral reset register							Address offset: 0x14
	__vo uint32_t AHB3RSTR;		// RCC AHB2 peripheral reset register							Address offset: 0x18
		 uint32_t RESERVED0; 	// Reserved, 0x1C

	__vo uint32_t APB1RSTR;		// RCC APB1 peripheral reset register							Address offset: 0x20
	__vo uint32_t APB2RSTR;
		 uint32_t RESERVED1; 	// Reserved, 0x28
		 uint32_t RESERVED2; 	// Reserved, 0x2C

	__vo uint32_t AHB1ENR;		// RCC AHB1 peripheral clock register							Address offset: 0x30
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
		 uint32_t RESERVED3; 	//  Reserved, 0x3C


	__vo uint32_t APB1ENR;		// RCC APB1 peripheral clock enable register					Address offset: 0x40
	__vo uint32_t APB2ENR;
	 	 uint32_t RESERVED4; 	//  Reserved, 0x48
	 	 uint32_t RESERVED5; 	//  Reserved, 0x4C

	__vo uint32_t AHB1LPENR;	// RCC AHB1 peripheral clock enable in low power mode register	Address offset: 0x50
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
		 uint32_t RESERVED6; 	//  Reserved, 0x5C

	__vo uint32_t APB1LPENR;	// RCC APB1 peripheral clock enable in low power mode register	Address offset: 0x60
	__vo uint32_t APB2LPENR;
	 	 uint32_t RESERVED7; 	//  Reserved, 0x68
	 	 uint32_t RESERVED8; 	//  Reserved, 0x6C

	__vo uint32_t BDCR;			// RCC Backup domain control register							Address offset: 0x70
	__vo uint32_t CSR;			// RCC clock control & status register							Address offset: 0x74
	 	 uint32_t RESERVED9; 	//  Reserved, 0x78
	 	 uint32_t RESERVED10; 	//  Reserved, 0x7C

	__vo uint32_t SSCGR;		// RCC spread spectrum clock generation register				Address offset: 0x80
	__vo uint32_t PLLI2SCFGR;	// RCC PLLI2S configuration register							Address offset: 0x84
	__vo uint32_t PLLSAICFGR;	// RCC PLL configuration register								Address offset: 0x88
	__vo uint32_t DCKCFGR;		// RCC Dedicated Clock Configuration Register					Address offset: 0x8C
}RCC_RegDef_t;


/*
 * **************************** EXTI peripheral register***********************
 */

typedef struct
{
	__vo uint32_t IMR; 			// Interrupt mask register 				Address offset: 0x00
	__vo uint32_t EMR; 			// Event mask register 					Address offset: 0x04
	__vo uint32_t RTSR; 		// Rising trigger selection register 	Address offset: 0x08
	__vo uint32_t FTSR; 		// Falling trigger selection register	Address offset: 0x0C
	__vo uint32_t SWIER; 		// Software interrupt event register	Address offset: 0x10
	__vo uint32_t PR; 			// Pending register						Address offset: 0x14
}EXTI_RegDef_t;


/*
 * **************************** SYSCFG peripheral register***********************
 */

typedef struct
{
	__vo uint32_t MEMRMP; 			// SYSCFG memory remap register									Address offset: 0x00
	__vo uint32_t PMC; 				// SYSCFG peripheral mode configuration registeR				Address offset: 0x04
	__vo uint32_t EXTICR[4]; 		// SYSCFG external interrupt configuration register 0-3 		Address offset: 0x08 - 0x14
		uint32_t RESERVED1[2]; 		// Reserve 1 													Reserved Address : 0x18-0x1c
	__vo uint32_t CMPCR; 			// Compensation cell control register							Address offset: 0x20
		uint32_t RESERVED2[2]; 		// Reserve 2													Reserved Address : 0x24-0x2c
	__vo uint32_t CFGR; 			// 																Address offset : 0x2C
}SYSCFG_RegDef_t;


/*
 * **************************** SPI peripheral register Definition ***********************
 */
typedef struct
{
	__vo uint32_t CR1; 			// SPI control register 1 					Address offset: 0x00
	__vo uint32_t CR2; 			// SPI control register 2 					Address offset: 0x04
	__vo uint32_t SR; 			// SPI status register 						Address offset: 0x08
	__vo uint32_t DR; 			// SPI data register						Address offset: 0x0C
	__vo uint32_t CRCPR; 		// SPI CRC polynomial register				Address offset: 0x10
	__vo uint32_t RXCRCR; 		// SPI RX CRC register						Address offset: 0x14
	__vo uint32_t TXCRCR;		// SPI TX CRC register						Address offset: 0x18
	__vo uint32_t I2SCFGR;		// SPI_I2S configuration register			Address offset: 0x1C
	__vo uint32_t I2SPR;		// SPI_I2S prescaler register 				Address offset: 0x20
}SPI_RegDef_t;

/*
 *  Peripheral definition ( Peripherals base address type casted to xx_RegDef_t )
 *  Application: it can be used to for simple access to peripheral register
 *  For example:
 *  	To access base address of GPIOA we have to write as:
 *  	GPIO_Reg_Def_t *pGPIOA = (GPIO_Reg_Def_t*)0x40020000;
 *  Instead we can make it simple via:
 *  		GPIO_Reg_Def_t *pGPIOA = GPIOA;
 *  	where GPIOA is:
 *  		#define GPIOA (((GPIO_Reg_Def_t*)GPIOA_BASE))
 */

#define GPIOA 		((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB 		((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC 		((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD 		((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOD 		((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE 		((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF 		((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG 		((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH 		((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI 		((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC 		((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI 		((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG		((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define SPI1 		((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2 		((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3 		((SPI_RegDef_t*)SPI3_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 * By default MCUS are designed to save power by keeping peripherals "asleep" (clock-gated) until you explicitly enable them.
 * Every peripheral (GPIO, USART, SPI, I2C, ADC, Timer, etc.) sits on a bus (AHB1, AHB2, APB1, APB2) and has its own clock signal
 * By default, after reset, almost all peripheral clocks are disabled to minimize power consumption.
 * If we try to configure or use a peripheral's registers without enabling its clock first,
 * the writes to those registers will either be ignored or read back as garbage — the peripheral is essentially "frozen" with no clock pulses
 * driving its internal logic.
 */
#define GPIOA_PCLK_EN()	(RCC->AHB1ENR |= (1<<0));
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1<<1));
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1<<2));
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1<<3));
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1<<4));
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1<<5));
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1<<6));
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1<<7));
#define GPIOI_PCLK_EN() (RCC->AHB1ENR |= (1<<8));


/*
 * Clock Enable Macros for I2Cx peripherals
*/
#define I2C1_PCLK_EN()	(RCC->APB1ENR |= (1<<21));
#define I2C2_PCLK_EN()	(RCC->APB1ENR |= (1<<22));
#define I2C3_PCLK_EN()	(RCC->APB1ENR |= (1<<23));

/*
 * Clock Enable Macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()	(RCC->APB2ENR |= (1<<12));
#define SPI2_PCLK_EN()	(RCC->APB1ENR |= (1<<14));
#define SPI3_PCLK_EN()	(RCC->APB1ENR |= (1<<15));

/*
 *
 * Clock Enable Macros for USARTx peripherals
*/
#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1<<4));
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1<<17));
#define USART3_PCLK_EN()	(RCC->APB1ENR |= (1<<18));
#define UART4_PCLK_EN()		(RCC->APB1ENR |= (1<<19));
#define UART5_PCLK_EN()		(RCC->APB1ENR |= (1<<20));
#define USART6_PCLK_EN()	(RCC->APB2ENR |= (1<<5));

/*
 * Clock Enable Macros for SYSCFG peripherals
*/
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1<<14));


/*
 * Clock Disable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI()	(RCC->AHB1ENR &= ~(1<<0));
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1<<1));
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1<<2));
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1<<3));
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1<<4));
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1<<5));
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1<<6));
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1<<7));
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~(1<<8));


/*
 * Clock Disable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()	(RCC->APB1ENR &= ~(1<<21));
#define I2C2_PCLK_DI()	(RCC->APB1ENR &= ~(1<<22));
#define I2C3_PCLK_DI()	(RCC->APB1ENR &= ~(1<<23));


/*
 * Clock Disable Macros for USARTx peripherals
*/
#define USART1_PCLK_DI()	(RCC->APB2ENR &= ~(1<<4));
#define USART2_PCLK_DI()	(RCC->APB1ENR &= ~(1<<17));
#define USART3_PCLK_DI()	(RCC->APB1ENR &= ~(1<<18));
#define UART4_PCLK_DI()		(RCC->APB1ENR &= ~(1<<19));
#define UART5_PCLK_DI()		(RCC->APB1ENR &= ~(1<<20));
#define USART6_PCLK_DI()	(RCC->APB2ENR &= ~(1<<5));

/*
 * Clock Disable Macros for SYSCFG peripherals
*/
#define SYSCFG_PCLK_DI()	(RCC->APB2ENR &= ~(1<<14));


/*
 * Macros to reset GPIOx peripherals
 * Note - A technique in a c language, to execute multiple C statement using single C macro
 * 		- No semicol, after while,  cz while calling the macros, a semicolumn is added
 * 		- This technique is called do..while..condition..0 loop
*/
#define GPIOA_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~(1<<0));}while(0)
#define GPIOB_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~(1<<1));}while(0)
#define GPIOC_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~(1<<2));}while(0)
#define GPIOD_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<3)); (RCC->AHB1RSTR &= ~(1<<3));}while(0)
#define GPIOE_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~(1<<4));}while(0)
#define GPIOF_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<5)); (RCC->AHB1RSTR &= ~(1<<5));}while(0)
#define GPIOG_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<6)); (RCC->AHB1RSTR &= ~(1<<6));}while(0)
#define GPIOH_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<7)); (RCC->AHB1RSTR &= ~(1<<7));}while(0)
#define GPIOI_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<8)); (RCC->AHB1RSTR &= ~(1<<8));}while(0)


/*
 * return port code for given GPIOx base address
 */
#define GPIO_BASEADDR_TO_CODE(port)	(	(port == GPIOA)?0:\
										(port == GPIOB)?1:\
										(port == GPIOC)?2:\
										(port == GPIOD)?3:\
										(port == GPIOE)?4:\
										(port == GPIOF)?5:\
										(port == GPIOG)?6:\
										(port == GPIOH)?7:0 )

/*
 * IRQ(Interrupt Request) Number of STM32F407xx MCU
 */
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40


/*
 * Macros for all the possible priority levels
 */
#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI15		15



/*
 * Some generic macros
 */
#define ENABLE			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET 	SET
#define GPIO_PIN_RESET	RESET



#include "stm32f407xx_gpio_driver.h"

#endif /* INC_STM32F407XX_H_ */
