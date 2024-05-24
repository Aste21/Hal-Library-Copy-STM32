/*
 * LPUART.c
 *
 *  Created on: May 24, 2024
 *      Author: es-4
 */
#include "LPUART.h"

void LPUART_init(LPUART_t *LPUART, LPUARTInit_t *LPUART_Init)
{
	CLK_ENABLE(CLKC);
	LPUART_ENABLE_CLK();

	CHANGESETTING(GPIOC_m->AFR[0], 0, 4, AF_8);
	CHANGESETTING(GPIOC_m->AFR[0], 4, 4, AF_8);
	CHANGESETTING(GPIOC_m->MODER, 0, 2, MODE_ALTERNATE_FUNCTION_m);
	CHANGESETTING(GPIOC_m->MODER, 2, 2, MODE_ALTERNATE_FUNCTION_m);

	if(LPUART_Init->Word_Length == DATA_BITS_8 || LPUART_Init->Word_Length == DATA_BITS_9)
	{
		CLRBIT(LPUART->CR1, M1_BIT);
	}
	else
	{
		SETBIT(LPUART->CR1, M1_BIT);
	}
	if(LPUART_Init->Word_Length == DATA_BITS_9)
	{
		SETBIT(LPUART->CR1, M0_BIT);
	}
	else
	{
		CLRBIT(LPUART->CR1, M0_BIT);
	}

	CHANGESETTING(LPUART->CR2, STOP_BIT, STOP_BIT_LENGTH, LPUART_Init->Stop_Bits);
	CHANGESETTING(LPUART->CR3, DMAT_BIT, DMAT_BIT_LENGTH, LPUART_Init->DMAT);
	CHANGESETTING(LPUART->CR3, DMAR_BIT, DMAR_BIT_LENGTH, LPUART_Init->DMAR);
	CHANGESETTING(LPUART->CR1, RE_BIT, RE_BIT_LENGTH, LPUART_Init->RE);
	CHANGESETTING(LPUART->CR1, TE_BIT, TE_BIT_LENGTH, LPUART_Init->TE);
	CHANGESETTING(LPUART->CR1, UE_BIT, UE_BIT_LENGTH, LPUART_Init->UE);

	LPUART->BRR = LPUART_Init->BRR;
}

void basic_LPUART_init()
{
	LPUARTInit_t LPUARTInit = {0};

	LPUARTInit.Word_Length = DATA_BITS_8;
	LPUARTInit.Stop_Bits = STOP_BITS_1;
	LPUARTInit.DMAT = DISABLE_DMAT;
	LPUARTInit.DMAR = DISABLE_DMAR;
	LPUARTInit.BRR = CLASSIC_BRR_VALUE;
	LPUARTInit.RE = ENABLE_RECEIVER;
	LPUARTInit.TE = ENABLE_TRANSMITTER;
	LPUARTInit.UE = ENABLE_LPUART;

	LPUART_init(LPUART_m, &LPUARTInit);
}

void LPUART_SendChar(const char data)
{
	while(!(LPUART_m->ISR & (1<<TXE_BIT))){}
	LPUART_m->TDR = data;
}

char LPUART_ReadChar()
{
	while(!(LPUART_m->ISR & (1<<RXNE_BIT))){}
	char c = LPUART_m->RDR;
	return c;
}

void LPUART_NewLine()
{
	  LPUART_SendChar('\n');
	  LPUART_SendChar('\r');
}

void LPUART_SendString(char* data)
{
	char* temp = data;
	while(*temp != '\0')
	{
		LPUART_SendChar(*temp);
		temp++;
	}
}

void LPUART_SendFifo(FIFO* fifo)
{
	char c;
	while(!FIFO_IsEmpty(fifo))
	{
		FIFO_Get(fifo, &c);
		LPUART_SendChar(c);
	}
}

char toggle_case_char(char c) {
    if (islower(c)) {
        return toupper(c);
    } else if (isupper(c)) {
        return tolower(c);
    }
    return c; // Non-alphabetical characters remain unchanged
}

void LPUART_ClearScreen()
{
	for(int i = 0;i < CLEAR_SCREEN_LINES;i++)
	{
		LPUART_NewLine();
	}
}


