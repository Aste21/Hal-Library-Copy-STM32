/*
 * FIFO.cpp
 *
 *  Created on: May 21, 2024
 *      Author: es-4
 */

#include "FIFO.h"

void FIFO_Init (FIFO *fifo){
	fifo->head=0;
	fifo->tail=0;
}

void FIFO_Empty (FIFO *fifo){
	fifo->head = fifo->tail;
}

int FIFO_Put (FIFO *fifo, char data){
	if (((fifo->tail - fifo->head) == 1) || ((fifo->tail - fifo->head) == BUFFERSIZE))
	{
		return -1;
	} /* FIFO overflow */
	fifo->buffer[fifo->head] = data;
	fifo->head = (fifo->head + 1) & BUFFERSIZE;
	return 1; /* Put 1 byte successfully */
}

int FIFO_Get (FIFO *fifo, char *data){
	if ((fifo->head != fifo->tail))
	{
		*data = fifo->buffer[fifo->tail];
		fifo->tail = (fifo->tail + 1) & BUFFERSIZE;
		return 1; /* Get 1 byte successfully */
	}
	else
	{
		return -1; /* No data in FIFO */
	}
}

int FIFO_IsEmpty(FIFO *fifo)
{
	if ((fifo->head != fifo->tail))
		{
			return 0; /* Get 1 byte successfully */
		}
		else
		{
			return 1; /* No data in FIFO */
		}
}
