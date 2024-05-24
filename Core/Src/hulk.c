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









