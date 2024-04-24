# Hal-Library-Copy-STM32
A copy of fundamental functions from the HAL library like ReadPin, WritePin, GPIO_Init etc., in a library called ,,HULK". 

This library implements simple GPIO functions and simple TIM6 Counter. 

In main there is an example of a simple program that displays a 4 digit number, and changes it exactly every 1 second,  based on joystick (if it is pressed the number goes up, and if it is not pressed then the number goes up).

The only functions taken from HAL library in the following code are: 

  HAL_Init() and SystemClock_Config()
  
which setup most of the clocks and a few peripherals in the stm32 board.
