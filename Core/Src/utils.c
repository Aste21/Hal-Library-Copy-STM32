#include "utils.h"

void LED_PIN_init(GPIO_Pin pin)
{
	GPIOInit_t GPIOInit = {0};
	turn_on_pin(pin.port, pin.pin);
	GPIOInit.Pin = pin.pin;
	GPIOInit.Mode = MODE_OUTPUT_m;
	GPIOInit.Type = TYPE_PUSH_PULL;
	GPIOInit.Pull = GPIO_NOPULL;
	GPIOInit.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_init(pin.port, &GPIOInit);
}

void turn_on_pin_struct(GPIO_Pin pin)
{
	turn_on_pin(pin.port, pin.pin);
}

void turn_off_pin_struct(GPIO_Pin pin)
{
	turn_off_pin(pin.port, pin.pin);
}
