/*
 * TIM6.c
 *
 *  Created on: May 24, 2024
 *      Author: es-4
 */
#include "TIM6.h"

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

FlagState check_tim6_flag(TIMx_t* TIMx)
{
	if(((TIMx->SR) & (1<<UIF_BIT)) != 0x0)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void clear_tim6_flag(TIMx_t* TIMx)
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
		while(check_tim6_flag(TIM6_m) != FLAG_SET);

		clear_tim6_flag(TIM6_m);
	}
}
