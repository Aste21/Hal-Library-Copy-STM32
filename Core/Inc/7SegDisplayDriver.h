#ifndef __7SEGDISPLAYDRIVER_H__
#define __7SEGDISPLAYDRIVER_H__

#include "utils.h"

#define NUMBER_OF_DIGIT_PINS 8
#define NUMBER_OF_DIG_LEDS 4

#define DIGIT_A_PIN (1U << 0)
#define DIGIT_A_PORT GPIOG_m
#define DIGIT_B_PIN (1U << 1)
#define DIGIT_B_PORT GPIOG_m
#define DIGIT_C_PIN (1U << 2)
#define DIGIT_C_PORT GPIOG_m
#define DIGIT_D_PIN (1U << 3)
#define DIGIT_D_PORT GPIOG_m
#define DIGIT_E_PIN (1U << 4)
#define DIGIT_E_PORT GPIOG_m
#define DIGIT_F_PIN (1U << 5)
#define DIGIT_F_PORT GPIOG_m
#define DIGIT_G_PIN (1U << 6)
#define DIGIT_G_PORT GPIOG_m
#define DIGIT_DP_PIN (1U << 9)
#define DIGIT_DP_PORT GPIOG_m

#define DIG_1_PIN (1U << 2)
#define DIG_1_PORT GPIOB_m
#define DIG_2_PIN (1U << 3)
#define DIG_2_PORT GPIOB_m
#define DIG_3_PIN (1U << 4)
#define DIG_3_PORT GPIOB_m
#define DIG_4_PIN (1U << 5)
#define DIG_4_PORT GPIOB_m

typedef enum {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	DP
} DIGIT_Number;

static const GPIO_Pin DIGIT_LED[NUMBER_OF_DIGIT_PINS] = {
		{DIGIT_A_PORT, DIGIT_A_PIN},
		{DIGIT_B_PORT, DIGIT_B_PIN},
		{DIGIT_C_PORT, DIGIT_C_PIN},
		{DIGIT_D_PORT, DIGIT_D_PIN},
		{DIGIT_E_PORT, DIGIT_E_PIN},
		{DIGIT_F_PORT, DIGIT_F_PIN},
		{DIGIT_G_PORT, DIGIT_G_PIN},
		{DIGIT_DP_PORT, DIGIT_DP_PIN}
};

static const GPIO_Pin DIG_LED[NUMBER_OF_DIG_LEDS] = {
		{DIG_1_PORT, DIG_1_PIN},
		{DIG_2_PORT, DIG_2_PIN},
		{DIG_3_PORT, DIG_3_PIN},
		{DIG_4_PORT, DIG_4_PIN}
};

static const uint8_t DIGITS[] = {
	DIGIT_A_PIN | DIGIT_B_PIN | DIGIT_C_PIN | DIGIT_D_PIN | DIGIT_E_PIN | DIGIT_F_PIN,	// 0
	DIGIT_B_PIN | DIGIT_C_PIN,	// 1
	DIGIT_A_PIN | DIGIT_B_PIN | DIGIT_D_PIN | DIGIT_E_PIN | DIGIT_G_PIN,	// 2
	DIGIT_A_PIN | DIGIT_B_PIN | DIGIT_C_PIN | DIGIT_D_PIN | DIGIT_G_PIN,	// 3
	DIGIT_B_PIN | DIGIT_C_PIN | DIGIT_F_PIN | DIGIT_G_PIN,	// 4
	DIGIT_A_PIN | DIGIT_C_PIN | DIGIT_D_PIN | DIGIT_F_PIN | DIGIT_G_PIN,	// 5
	DIGIT_A_PIN | DIGIT_C_PIN | DIGIT_D_PIN | DIGIT_E_PIN | DIGIT_F_PIN | DIGIT_G_PIN,	// 6
	DIGIT_A_PIN | DIGIT_B_PIN | DIGIT_C_PIN,	// 7
	DIGIT_A_PIN | DIGIT_B_PIN | DIGIT_C_PIN | DIGIT_D_PIN | DIGIT_E_PIN | DIGIT_F_PIN | DIGIT_G_PIN,	// 8
	DIGIT_A_PIN | DIGIT_B_PIN | DIGIT_C_PIN | DIGIT_D_PIN | DIGIT_F_PIN | DIGIT_G_PIN,	// 9
	DIGIT_A_PIN | DIGIT_B_PIN | DIGIT_C_PIN | DIGIT_D_PIN | DIGIT_E_PIN | DIGIT_F_PIN | DIGIT_G_PIN // all
};

void DIGIT_init(void);
void turn_off_full_segment();
void display_number(int number, int delay_miliseconds);
void display_digit(int number, int segment);
#endif
