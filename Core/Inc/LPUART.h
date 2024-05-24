/*
 * LPUART.h
 *
 *  Created on: May 24, 2024
 *      Author: es-4
 */

#ifndef INC_LPUART_H_
#define INC_LPUART_H_

#include "hulk.h"

#define DATA_BITS_8					0x00000000u
#define DATA_BITS_9					0x00000001u
#define DATA_BITS_7					0x00000002u

#define STOP_BIT_LENGTH				2
#define STOP_BITS_1					0x00000000u
#define STOP_BITS_2					0x00000002u
#define STOP_BITS_RESET				0x00000000u

#define DMAT_BIT_LENGTH				1
#define DISABLE_DMAT				0x00000000u
#define ENABLE_DMAT					0x00000001u

#define DMAR_BIT_LENGTH				1
#define DISABLE_DMAR				0x00000000u
#define ENABLE_DMAR					0x00000001u

#define RE_BIT_LENGTH				1
#define DISABLE_RECEIVER			0x00000000u
#define ENABLE_RECEIVER				0x00000001u

#define TE_BIT_LENGTH				1
#define DISABLE_TRANSMITTER			0x00000000u
#define ENABLE_TRANSMITTER			0x00000001u

#define UE_BIT_LENGTH				1
#define DISABLE_LPUART				0x00000000u
#define ENABLE_LPUART				0x00000001u

#define CLASSIC_BRR					115200

#define AF_8						0x00000008u

#define LPUART_m					((LPUART_t*)0x40008000)

#define LPUART_BIT					0
#define LPUART_ENABLE_CLK()			SETBIT(APB1ENR2_m->APB1_tt, LPUART_BIT)

#define M0_BIT						12
#define M1_BIT						28
#define STOP_BIT					12
#define UE_BIT						0
#define DMAT_BIT					7
#define DMAR_BIT					6
#define RE_BIT						2
#define TE_BIT						3
#define TXE_BIT						7
#define TC_BIT						6
#define RXNE_BIT					5

#define CLASSIC_BRR_VALUE			((256 * 4000000) / 115200)
#define CLEAR_SCREEN_LINES			100

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t BRR;
	volatile uint32_t RESERVED1;
	volatile uint32_t RESERVED2;
	volatile uint16_t RQR;
	volatile uint16_t RQR_RESERVED;
	volatile uint32_t ISR;
	volatile uint32_t ICR;
	volatile uint16_t RDR;
	volatile uint16_t RDR_RESERVED;
	volatile uint16_t TDR;
	volatile uint16_t TDR_RESERVED;
} LPUART_t;

typedef struct
{
	uint32_t Word_Length;

	uint32_t Stop_Bits;

	uint32_t DMAT;

	uint32_t DMAR;

	uint32_t BRR;

	uint32_t RE;

	uint32_t TE;

	uint32_t UE;
} LPUARTInit_t;

void basic_LPUART_init();
void LPUART_SendChar(const char data);
char LPUART_ReadChar();
void LPUART_SendString(char* data);
void LPUART_NewLine();
char toggle_case_char(char c);
void LPUART_ClearScreen();
void LPUART_SendFifo(FIFO* fifo);
void LPUART_init(LPUART_t *LPUART, LPUARTInit_t *LPUART_Init);


#endif /* INC_LPUART_H_ */
