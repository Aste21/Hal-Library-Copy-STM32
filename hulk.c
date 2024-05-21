/*
 * hulk.c
 *
 *  Created on: Mar 26, 2024
 *      Author: es-4
 */
#include "hulk.h"

void GPIO_init(GPIOx_t *GPIOx, GPIOInit_t *GPIO_Init)
{
	uint32_t position = 0x00u;
	uint32_t current_pin;
	while(((GPIO_Init->Pin) >> position) != 0x00u)
	{
		current_pin = (GPIO_Init->Pin) & (1 << position);
		if(current_pin != 0x00u)
		{
			CHANGESETTING(GPIOx->MODER, position * 2, MODE_BIT_LENGTH, GPIO_Init->Mode);
			CHANGESETTING(GPIOx->OTYPER, position, TYPE_BIT_LENGTH, GPIO_Init->Type);
			CHANGESETTING(GPIOx->OSPEEDR, position * 2, SPEED_BIT_LENGTH, GPIO_Init->Speed);
			CHANGESETTING(GPIOx->PUPDR, position * 2, PULL_BIT_LENGTH, GPIO_Init->Pull);
		}
		position++;
	}

}

void TIM_init(TIMx_t *TIMx, TIMInit_t *TIM_Init)
{
    CHANGESETTING(TIMx->CR1, CEN_BIT, CEN_BIT_LENGTH, TIM_Init->CEN);
    CHANGESETTING(TIMx->CR1, ARPE_BIT, ARPE_BIT_LENGTH, TIM_Init->ARPE);
    CHANGESETTING(TIMx->CR1, OPM_BIT, OPM_BIT_LENGTH, TIM_Init->OPM);
    CHANGESETTING(TIMx->CR1, URS_BIT, URS_BIT_LENGTH, TIM_Init->URS);
    CHANGESETTING(TIMx->CR1, UDIS_BIT, UDIS_BIT_LENGTH, TIM_Init->UDIS);
    CHANGESETTING(TIMx->DIER, UIE_BIT, UIE_BIT_LENGTH, TIM_Init->UIE);

    TIMx->PSC = TIM_Init->PRESCALOR;
    TIMx->ARR = TIM_Init->PERIOD;

    CHANGESETTING(TIMx->EGR, UG_BIT, 1, TIM_Init->UG);
}

void LPUART_init(LPUART_t *LPUART, LPUARTInit_t *LPUART_Init)
{
	CLK_ENABLE(CLKC);
	LPUART_ENABLE_CLK();

	CHANGESETTING(GPIOC_m->AFR[0], 0, 4, AF_8);
	CHANGESETTING(GPIOC_m->AFR[0], 4, 4, AF_8);
	CHANGESETTING(GPIOC_m->MODER, 0, 2, MODE_ALTERNATE_FUNCTION_m);
	CHANGESETTING(GPIOC_m->MODER, 2, 2, MODE_ALTERNATE_FUNCTION_m);

	if(LPUART_Init->Word_Length == DATA_BITS_8 || LPUART_Init->Word_Length == DATA_BITS_9)
	{
		CLRBIT(LPUART->CR1, M1_BIT);
	}
	else
	{
		SETBIT(LPUART->CR1, M1_BIT);
	}
	if(LPUART_Init->Word_Length == DATA_BITS_9)
	{
		SETBIT(LPUART->CR1, M0_BIT);
	}
	else
	{
		CLRBIT(LPUART->CR1, M0_BIT);
	}

	CHANGESETTING(LPUART->CR2, STOP_BIT, STOP_BIT_LENGTH, LPUART_Init->Stop_Bits);
	CHANGESETTING(LPUART->CR3, DMAT_BIT, DMAT_BIT_LENGTH, LPUART_Init->DMAT);
	CHANGESETTING(LPUART->CR3, DMAR_BIT, DMAR_BIT_LENGTH, LPUART_Init->DMAR);
	CHANGESETTING(LPUART->CR1, RE_BIT, RE_BIT_LENGTH, LPUART_Init->RE);
	CHANGESETTING(LPUART->CR1, TE_BIT, TE_BIT_LENGTH, LPUART_Init->TE);
	CHANGESETTING(LPUART->CR1, UE_BIT, UE_BIT_LENGTH, LPUART_Init->UE);

	LPUART->BRR = LPUART_Init->BRR;
}

void turn_on_pin(GPIOx_t* GPIOx, pin_t GPIO_Pin)
{
	GPIOx->BSRR = (uint32_t)GPIO_Pin;
}

void turn_off_pin(GPIOx_t* GPIOx, pin_t GPIO_Pin)
{
	  GPIOx->BRR = (uint32_t)GPIO_Pin;
}

PinState read_pin(GPIOx_t* GPIOx, pin_t GPIO_Pin)
{
  if ((GPIOx->IDR & GPIO_Pin) != 0x00u)
  {
	  return PIN_SET;
  }
  else
  {
	  return PIN_RESET;
  }
}

FlagState check_flag(TIMx_t* TIMx)
{
	if(((TIMx->SR) & (1<<UIF_BIT)) != 0x0)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void clear_flag(TIMx_t* TIMx)
{
	CLRBIT(TIMx->SR, UIF_BIT);
}

void start_timer()
{
	SETBIT(TIM6_m->CR1, CEN_BIT);
}

void stop_timer()
{
	CLRBIT(TIM6_m->CR1, CEN_BIT);
}

void basic_TIM6_init()
{
	TIM6_ENABLE();

	TIMInit_t TIMInit = {0};

	TIMInit.CEN = 0; // Disable timer during setup
	TIMInit.ARPE = 1; // Enable ARR buffering
	TIMInit.OPM = 0; // Continuous mode
	TIMInit.URS = 1; // Only overflow/underflow generates update
	TIMInit.UDIS = 0; // Disable updates
	TIMInit.UG = 1; // Force an update to load the prescaler value
	TIMInit.UIE = 0; // Enable update interrupts (if using interrupts)
	TIMInit.PRESCALOR = 400 - 1;
	TIMInit.PERIOD = 10 - 1;

	TIM_init(TIM6_m, &TIMInit);
}

void HULK_delay(int miliseconds)
{
	for(int i = 0;i < miliseconds;i++)
	{
		while(check_flag(TIM6_m) != FLAG_SET);

		clear_flag(TIM6_m);
	}
}

void basic_LPUART_init()
{
	LPUARTInit_t LPUARTInit = {0};

	LPUARTInit.Word_Length = DATA_BITS_8;
	LPUARTInit.Stop_Bits = STOP_BITS_1;
	LPUARTInit.DMAT = DISABLE_DMAT;
	LPUARTInit.DMAR = DISABLE_DMAR;
	LPUARTInit.BRR = CLASSIC_BRR_VALUE;
	LPUARTInit.RE = ENABLE_RECEIVER;
	LPUARTInit.TE = ENABLE_TRANSMITTER;
	LPUARTInit.UE = ENABLE_LPUART;

	LPUART_init(LPUART_m, &LPUARTInit);
}

void LPUART_SendChar(const char data)
{
	while(!(LPUART_m->ISR & (1<<TXE_BIT))){}
	LPUART_m->TDR = data;
	while(!(LPUART_m->ISR & (1<<TC_BIT))){}
}

char LPUART_ReadChar()
{
	while(!(LPUART_m->ISR & (1<<RXNE_BIT))){}
	char c = LPUART_m->RDR;
	return c;
}

void LPUART_NewLine()
{
	  LPUART_SendChar('\n');
	  LPUART_SendChar('\r');
}

void LPUART_SendString(char* data)
{
	char* temp = data;
	while(*temp != '\0')
	{
		LPUART_SendChar(*temp);
		temp++;
	}
}

char toggle_case_char(char c) {
    if (islower(c)) {
        return toupper(c);
    } else if (isupper(c)) {
        return tolower(c);
    }
    return c; // Non-alphabetical characters remain unchanged
}

void LPUART_ClearScreen()
{
	for(int i = 0;i < CLEAR_SCREEN_LINES;i++)
	{
		LPUART_NewLine();
	}
}







