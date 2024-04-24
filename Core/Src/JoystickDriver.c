#include "JoystickDriver.h"

void JOY_STICK_init(void)
{
	CLK_ENABLE(CLKE);
	GPIOInit_t GPIOInit = {0};
	turn_off_pin(GPIOE_m, JOY_RT_PIN| JOY_LT_PIN | JOY_DN_PIN | JOY_UP_PIN);
	GPIOInit.Pin = JOY_RT_PIN| JOY_LT_PIN | JOY_DN_PIN | JOY_UP_PIN | JOY_CNT_PIN;
	GPIOInit.Mode = MODE_INPUT_m;
	GPIOInit.Type = TYPE_PUSH_PULL;
	GPIOInit.Pull = NO_PULL;
	GPIOInit.Speed = SPEED_LOW;
	GPIO_init(GPIOE_m, &GPIOInit);
}

JOYSTICK_State joy_input_checker(void)
{
	if(read_pin(GPIOE_m, JOY_LT_PIN) == PIN_RESET)
	{
		return JOYSTICK_LEFT;
	}
	if(read_pin(GPIOE_m, JOY_DN_PIN) == PIN_RESET)
	{
		return JOYSTICK_DOWN;
	}
	if(read_pin(GPIOE_m, JOY_RT_PIN) == PIN_RESET)
	{
		return JOYSTICK_RIGHT;
	}
	if(read_pin(GPIOE_m, JOY_UP_PIN) == PIN_RESET)
	{
		return JOYSTICK_UP;
	}
	if(read_pin(GPIOE_m, JOY_CNT_PIN) == PIN_RESET)
	{
		return JOYSTICK_CENTER;
	}
	return JOYSTICK_IDLE;
}
