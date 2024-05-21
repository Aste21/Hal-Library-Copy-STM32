/*
 * hulk.h
 *
 *  Created on: Mar 26, 2024
 *      Author: es-4
 */

#ifndef INC_HULK_H_
#define INC_HULK_H_

#include <stdint.h>
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <ctype.h>

typedef uint16_t pin_t;
typedef struct
{
	volatile uint32_t AHB2_tt;
}AHB2_t;

typedef struct
{
	volatile uint32_t APB1_tt;
}APB1_t;

typedef struct
{
	volatile uint32_t PWR_CR2_tt;
}PWR_CR2_t;

#define MODE_BIT_LENGTH				2
#define MODE_INPUT_m				0x00000000u
#define MODE_OUTPUT_m 				0x00000001u
#define MODE_ALTERNATE_FUNCTION_m 	0x00000002u
#define MODE_ANALOG_m				0x00000003u

#define TYPE_BIT_LENGTH				1
#define TYPE_PUSH_PULL				0x00000000u
#define TYPE_OPEN_DRAIN				0x00000001u

#define SPEED_BIT_LENGTH			2
#define SPEED_LOW					0x00000000u
#define SPEED_MEDIUM				0x00000001u
#define SPEED_HIGH					0x00000002u
#define SPEED_VERY_HIGH				0x00000003u

#define PULL_BIT_LENGTH				2
#define NO_PULL						0x00000000u
#define PULL_UP						0x00000001u
#define PULL_DOWN					0x00000002u


#define DATA_BITS_8					0x00000000u
#define DATA_BITS_9					0x00000001u
#define DATA_BITS_7					0x00000002u

#define STOP_BIT_LENGTH				2
#define STOP_BITS_1					0x00000000u
#define STOP_BITS_2					0x00000002u
#define STOP_BITS_RESET				0x00000000u

#define DMAT_BIT_LENGTH				1
#define DISABLE_DMAT				0x00000000u
#define ENABLE_DMAT					0x00000001u

#define DMAR_BIT_LENGTH				1
#define DISABLE_DMAR				0x00000000u
#define ENABLE_DMAR					0x00000001u

#define RE_BIT_LENGTH				1
#define DISABLE_RECEIVER			0x00000000u
#define ENABLE_RECEIVER				0x00000001u

#define TE_BIT_LENGTH				1
#define DISABLE_TRANSMITTER			0x00000000u
#define ENABLE_TRANSMITTER			0x00000001u

#define UE_BIT_LENGTH				1
#define DISABLE_LPUART				0x00000000u
#define ENABLE_LPUART				0x00000001u

#define CLASSIC_BRR					115200

#define DISABLE_STATE				0x00000000u
#define ENABLE_STATE				0x00000001u

#define AF_8						0x00000008u



#define PIN_1						((pin_t)1<<0)
#define PIN_2						((pin_t)1<<1)
#define PIN_3						((pin_t)1<<2)
#define PIN_4						((pin_t)1<<3)
#define PIN_5						((pin_t)1<<4)
#define PIN_6						((pin_t)1<<5)
#define PIN_7						((pin_t)1<<6)
#define PIN_8						((pin_t)1<<7)
#define PIN_9						((pin_t)1<<8)
#define PIN_10						((pin_t)1<<9)
#define PIN_11						((pin_t)1<<10)
#define PIN_12						((pin_t)1<<11)
#define PIN_13						((pin_t)1<<12)
#define PIN_14						((pin_t)1<<13)
#define PIN_15 						((pin_t)1<<14)
#define PIN_16 						((pin_t)1<<15)

#define GPIOA_m 					((GPIOx_t*)0x48000000)
#define GPIOB_m 					((GPIOx_t*)0x48000400)
#define GPIOC_m 					((GPIOx_t*)0x48000800)
#define GPIOD_m 					((GPIOx_t*)0x48000C00)
#define GPIOE_m 					((GPIOx_t*)0x48001000)
#define GPIOF_m 					((GPIOx_t*)0x48001400)
#define GPIOG_m 					((GPIOx_t*)0x48001800)
#define GPIOH_m 					((GPIOx_t*)0x48001C00)

#define TIM6_m						((TIMx_t*)0x40001000)

#define LPUART_m					((LPUART_t*)0x40008000)

#define RCC_m						(0x40021000)

#define AHB2_OFFSET					(0x4C)
#define AHB2						((AHB2_t*)(RCC_m+AHB2_OFFSET))

#define APB1ENR1_OFFSET 			(0x58)
#define APB1ENR1_m					((APB1_t*)(RCC_m+APB1ENR1_OFFSET))

#define APB1ENR2_OFFSET 			(0x5C)
#define APB1ENR2_m					((APB1_t*)(RCC_m+APB1ENR2_OFFSET))


#define PWR_m						(0x40007000)
#define PWR_CR2_OFFSET				(0x04)
#define PWR_CR2						((PWR_CR2_t*)(PWR_m+PWR_CR2_OFFSET))

#define RSTVALCALC(N)				(((1<<N)-1))

#define BIT(x)						(1U << (x))
#define SETBIT(P, B)				((P) |= BIT(B))
#define CLRBIT(P, B)				((P) &= ~BIT(B))
#define RSTSETTING(P, B, N)			((P) &= ~(RSTVALCALC(N) << B))
#define SETSETTING(P, B, S)			((P) |= ((S) << (B)))

#define CHANGESETTING(P, B, N, S) \
    do { \
        RSTSETTING(P, B, N); \
        SETSETTING(P, B, S); \
    } while (0)
	//P is the register, B is the bit number in register, N is the number of bits of setting, S is the setting

#define CLK_ENABLE(x)				SETBIT(AHB2->AHB2_tt, x)
#define EnableVddIO2()				SETBIT(PWR_CR2->PWR_CR2_tt, 9)

#define TIM6_BIT					4
#define TIM6_ENABLE()				SETBIT(APB1ENR1_m->APB1_tt, TIM6_BIT)

#define LPUART_BIT					0
#define LPUART_ENABLE_CLK()			SETBIT(APB1ENR2_m->APB1_tt, LPUART_BIT)

#define CEN_BIT_LENGTH				1
#define CEN_BIT						0
#define ARPE_BIT_LENGTH				1
#define ARPE_BIT					7
#define OPM_BIT_LENGTH				1
#define OPM_BIT						3
#define URS_BIT_LENGTH				1
#define URS_BIT						2
#define UDIS_BIT_LENGTH				1
#define UDIS_BIT					1
#define UG_BIT_LENGTH				1
#define UG_BIT						0
#define UIF_BIT_LENGTH				1
#define UIF_BIT						0
#define UIE_BIT_LENGTH				1
#define UIE_BIT						0

#define M0_BIT						12
#define M1_BIT						28
#define STOP_BIT					12
#define UE_BIT						0
#define DMAT_BIT					7
#define DMAR_BIT					6
#define RE_BIT						2
#define TE_BIT						3
#define TXE_BIT						7
#define TC_BIT						6
#define RXNE_BIT					5

#define CLASSIC_BRR_VALUE			((256 * 4000000) / 115200)
#define CLEAR_SCREEN_LINES			100

typedef enum
{
	CLKA,
	CLKB,
	CLKC,
	CLKD,
	CLKE,
	CLKF,
	CLKG,
	CLKH,
	CLKI
}GPIONumber;

typedef enum
{
  PIN_RESET = 0U,
  PIN_SET
} PinState;

typedef enum
{
  FLAG_RESET = 0U,
  FLAG_SET
} FlagState;

typedef struct
{
  volatile uint32_t MODER;       /*!< GPIO port mode register,               Address offset: 0x00      */
  volatile uint32_t OTYPER;      /*!< GPIO port output type register,        Address offset: 0x04      */
  volatile uint32_t OSPEEDR;     /*!< GPIO port output speed register,       Address offset: 0x08      */
  volatile uint32_t PUPDR;       /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  volatile uint32_t IDR;         /*!< GPIO port input data register,         Address offset: 0x10      */
  volatile uint32_t ODR;         /*!< GPIO port output data register,        Address offset: 0x14      */
  volatile uint32_t BSRR;        /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
  volatile uint32_t LCKR;        /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  volatile uint32_t AFR[2];      /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  volatile uint32_t BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */
} GPIOx_t;


typedef struct
{
  uint32_t Pin;

  uint32_t Mode;

  uint32_t Type;

  uint32_t Pull;

  uint32_t Speed;

  uint32_t Alternate;
} GPIOInit_t;

typedef struct
{
	volatile uint16_t CR1;
	volatile uint16_t CR1_RESERVED;
	volatile uint16_t CR2;
	volatile uint16_t CR2_RESERVED;
	volatile uint32_t RESERVED1;
	volatile uint16_t DIER;
	volatile uint16_t DIER_RESERVED;
	volatile uint16_t SR;
	volatile uint16_t SR_RESERVED;
	volatile uint16_t EGR;
	volatile uint16_t EGR_RESERVED;
	volatile uint32_t RESERVED2;
	volatile uint32_t RESERVED3;
	volatile uint32_t RESERVED4;
	volatile uint32_t CNT;
	volatile uint16_t PSC;
	volatile uint16_t PSC_RESERVED;
	volatile uint16_t ARR;
	volatile uint16_t ARR_RESERVED;
} TIMx_t;

typedef struct
{
	uint16_t CEN; // Counter enable

	uint16_t ARPE; // Auto-reload preload enabled

	uint16_t OPM; // One-pulse mode

	uint16_t URS; // Update request source

	uint16_t UDIS; // Update disable

	uint16_t UG; // update generation

	uint16_t UIE; //

	uint16_t PRESCALOR;

	uint16_t PERIOD;
} TIMInit_t;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t BRR;
	volatile uint32_t RESERVED1;
	volatile uint32_t RESERVED2;
	volatile uint16_t RQR;
	volatile uint16_t RQR_RESERVED;
	volatile uint32_t ISR;
	volatile uint32_t ICR;
	volatile uint16_t RDR;
	volatile uint16_t RDR_RESERVED;
	volatile uint16_t TDR;
	volatile uint16_t TDR_RESERVED;
} LPUART_t;

typedef struct
{
	uint32_t Word_Length;

	uint32_t Stop_Bits;

	uint32_t DMAT;

	uint32_t DMAR;

	uint32_t BRR;

	uint32_t RE;

	uint32_t TE;

	uint32_t UE;
} LPUARTInit_t;

void GPIO_init(GPIOx_t *GPIOx, GPIOInit_t *GPIO_Init);
void TIM_init(TIMx_t *TIMx, TIMInit_t *TIM_Init);
void LPUART_init(LPUART_t *LPUART, LPUARTInit_t *LPUART_Init);
void turn_on_pin(GPIOx_t* GPIOx, pin_t GPIO_Pin);
void turn_off_pin(GPIOx_t* GPIOx, pin_t GPIO_Pin);
void HULK_delay(int miliseconds);
PinState read_pin(GPIOx_t* GPIOx, pin_t GPIO_Pin);
FlagState check_flag(TIMx_t* TIMx);
void clear_flag(TIMx_t* TIMx);
void basic_TIM6_init();
void start_timer();
void stop_timer();
void basic_LPUART_init();
void LPUART_SendChar(const char data);
char LPUART_ReadChar();
void LPUART_SendString(char* data);
void LPUART_NewLine();
char toggle_case_char(char c);
void LPUART_ClearScreen();



#endif /* INC_HULK_H_ */
