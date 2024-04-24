#ifndef __UTILS_H__
#define __UTILS_H__

#include "hulk.h"

typedef struct {
	GPIOx_t* port;
	pin_t pin;
} GPIO_Pin;

void LED_PIN_init(GPIO_Pin pin);
void turn_on_pin_struct(GPIO_Pin pin);
void turn_off_pin_struct(GPIO_Pin pin);

#endif
