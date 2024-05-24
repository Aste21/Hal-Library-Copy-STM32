/*
 * TIM6.h
 *
 *  Created on: May 24, 2024
 *      Author: es-4
 */

#ifndef INC_TIM6_H_
#define INC_TIM6_H_

#include "hulk.h"

#define TIM6_m						((TIMx_t*)0x40001000)

#define TIM6_BIT					4
#define TIM6_ENABLE()				SETBIT(APB1ENR1_m->APB1_tt, TIM6_BIT)

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

void TIM_init(TIMx_t *TIMx, TIMInit_t *TIM_Init);
FlagState check_tim6_flag(TIMx_t* TIMx);
void clear_tim6_flag(TIMx_t* TIMx);
void basic_TIM6_init();
void start_timer();
void stop_timer();


#endif /* INC_TIM6_H_ */
