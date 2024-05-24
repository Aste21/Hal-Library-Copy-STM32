#include "7SegDisplayDriver.h"

void DIGIT_init(void) {
	CLK_ENABLE(CLKB);
    CLK_ENABLE(CLKG);
    EnableVddIO2();

    GPIOInit_t GPIOInit = {0};
    GPIOInit.Pin = DIGIT_A_PIN | DIGIT_B_PIN | DIGIT_C_PIN | DIGIT_D_PIN |
                   DIGIT_E_PIN | DIGIT_F_PIN | DIGIT_G_PIN | DIGIT_DP_PIN;
    GPIOInit.Mode = MODE_OUTPUT_m;
    GPIOInit.Type = TYPE_PUSH_PULL;
    GPIOInit.Pull = NO_PULL;
    GPIOInit.Speed = SPEED_LOW;
    GPIO_init(DIGIT_A_PORT, &GPIOInit);

    GPIOInit.Pin = DIG_1_PIN | DIG_2_PIN | DIG_3_PIN | DIG_4_PIN;
    GPIO_init(DIG_1_PORT, &GPIOInit);
}

void turn_off_full_segment()
{
	turn_off_pin(DIGIT_A_PORT, DIGITS[10]);
}

void display_number(int number, int delay_miliseconds)
{
		for(int i = NUMBER_OF_DIG_LEDS - 1;i >= 0;i--)
		{
			turn_off_full_segment();
			// Set segments for the current digit
			if(i == NUMBER_OF_DIG_LEDS - 1 || number != 0)
			{
				turn_on_pin(DIGIT_A_PORT, DIGITS[number % 10]);
			}
			turn_on_pin_struct(DIG_LED[i]);

			HULK_delay(delay_miliseconds);
			turn_off_pin_struct(DIG_LED[i]);
			// Turn on only the current digit
			number /= 10;
		}
}

void display_digit(int number, int segment)
{
	turn_off_full_segment();
	turn_on_pin_struct(DIG_LED[segment]);
	turn_on_pin(DIGIT_A_PORT, DIGITS[number]);
	HULK_delay(1);
	turn_off_pin_struct(DIG_LED[segment]);
}
