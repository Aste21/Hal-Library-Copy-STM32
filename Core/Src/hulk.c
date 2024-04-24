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
			GPIOx->MODER = GPIOx->MODER & ~(3 << position * 2);
			GPIOx->MODER = GPIOx->MODER | (GPIO_Init->Mode << position * 2);
			GPIOx->OTYPER = GPIOx->OTYPER & ~(1 << position);
			GPIOx->OTYPER = GPIOx->OTYPER | (GPIO_Init->Type << position);
			GPIOx->OSPEEDR = GPIOx->OSPEEDR & ~(3 << position * 2);
			GPIOx->OSPEEDR = GPIOx->OSPEEDR | (GPIO_Init->Speed << position * 2);
			GPIOx->PUPDR = GPIOx->PUPDR & ~(3 << position * 2);
			GPIOx->PUPDR = GPIOx->PUPDR | (GPIO_Init->Pull << position * 2);
		}
		position++;
	}

}

void TIM_init(TIMx_t *TIMx, TIMInit_t *TIM_Init)
{
	CLRBIT(TIMx->CR1, CEN_BIT);
	if(TIM_Init->CEN != 0x0)
	{
		SETBIT(TIMx->CR1, CEN_BIT);
	}

	CLRBIT(TIMx->CR1, ARPE_BIT);
	if(TIM_Init->ARPE != 0x0)
	{
		SETBIT(TIMx->CR1, ARPE_BIT);
	}

	CLRBIT(TIMx->CR1, OPM_BIT);
	if(TIM_Init->OPM != 0x0)
	{
		SETBIT(TIMx->CR1, OPM_BIT);
	}

	CLRBIT(TIMx->CR1, URS_BIT);
	if(TIM_Init->URS != 0x0)
	{
		SETBIT(TIMx->CR1, URS_BIT);
	}

	CLRBIT(TIMx->CR1, UDIS_BIT);
	if(TIM_Init->UDIS != 0x0)
	{
		SETBIT(TIMx->CR1, UDIS_BIT);
	}

	CLRBIT(TIMx->DIER, UIE_BIT);
	if(TIM_Init->UIE != 0x0)
	{
		SETBIT(TIMx->DIER, UIE_BIT);
	}

	TIMx->PSC = (uint32_t)TIM_Init->PRESCALOR;

	TIMx->ARR = (uint32_t)TIM_Init->PERIOD;

	CLRBIT(TIMx->EGR, UG_BIT);
	if(TIM_Init->UG != 0x0)
	{
		SETBIT(TIMx->EGR, UG_BIT);
	}
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
	TIMInit.PRESCALOR = 2000 - 1;
	TIMInit.PERIOD = 1;

	TIM_init(TIM6_m, &TIMInit);
}

void HULK_delay_old(int time)
{
	int i = 0;
	while(i<time*1000)
	{
		i++;
	}
}

void HULK_delay(int miliseconds)
{
	for(int i = 0;i < miliseconds;i++)
	{
		while(check_flag(TIM6_m) != FLAG_SET);

		clear_flag(TIM6_m);
	}
}
