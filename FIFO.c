/*
 * FIFO.cpp
 *
 *  Created on: May 21, 2024
 *      Author: es-4
 */

#include "FIFO.h"

void FIFO_Init (struct FIFO *fifo){
	fifo->head=0;
	fifo->tail=0;
}

void FIFO_Empty (struct FIFO *fifo){
	fifo->head = fifo->tail;
}

int FIFO_Put (struct FIFO *fifo, char Data){
	if (((fifo->tail - fifo->head) == 1) || ((fifo->tail - fifo->head) == BUFFERSIZE))
	{
		return -1;
	} /* FIFO overflow */
	Fifo->buffer[Fifo->head] = Data;
	Fifo->head = (Fifo->head + 1) & BUFFERSIZE;
	return 1; /* Put 1 byte successfully */
}

int FIFO_Get (struct FIFO *Fifo, char *Data){
	if ((fifo.head != fifo.tail))
	{
		*data = fifo->buffer[Fifo->tail];
		fifo->tail = (fifo->tail + 1) & BUFFERSIZE;
		return 1; /* Get 1 byte successfully */
	}
	else
	{
		return -1; /* No data in FIFO */
	}
}
