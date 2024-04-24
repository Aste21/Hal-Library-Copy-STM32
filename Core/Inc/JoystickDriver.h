#ifndef __JOYSTICKDRIVER_H__
#define __JOYSTICKDRIVER_H__

#include "utils.h"

#define NUMBER_OF_JOY_STICK_PINS 5
#define JOY_RT_PIN (1U << 0) // PE0
#define JOY_RT_PORT GPIOE_m
#define JOY_LT_PIN (1U << 1) // PE1
#define JOY_LT_PORT GPIOE_m
#define JOY_DN_PIN  (1U << 2) // PE2
#define JOY_DN_PORT GPIOE_m
#define JOY_UP_PIN (1U << 3) // PE3
#define JOY_UP_PORT GPIOE_m
#define JOY_CNT_PIN (1U << 15) // PE15
#define JOY_CNT_PORT GPIOE_m

typedef enum {
    JOYSTICK_IDLE,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT,
    JOYSTICK_UP,
    JOYSTICK_DOWN,
	JOYSTICK_CENTER
} JOYSTICK_State;

static const GPIO_Pin JOY_STICK[NUMBER_OF_JOY_STICK_PINS] = {
		{JOY_RT_PORT, JOY_RT_PIN},
		{JOY_LT_PORT, JOY_LT_PIN},
		{JOY_DN_PORT, JOY_DN_PIN},
		{JOY_UP_PORT, JOY_UP_PIN},
		{JOY_CNT_PORT, JOY_CNT_PIN}
};

void JOY_STICK_init(void);
JOYSTICK_State joy_input_checker(void);

#endif
