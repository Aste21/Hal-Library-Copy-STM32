/*
 * FIFO.h
 *
 *  Created on: May 21, 2024
 *      Author: es-4
 */

#ifndef FIFO_H_
#define FIFO_H_

#define BUFFERSIZE 0xFF

typedef struct {
	char buffer[BUFFERSIZE+1];

	unsigned int head;

	unsigned int tail;
} FIFO;

void FIFO_Init(FIFO *fifo);
void FIFO_Empty(FIFO *fifo);
int FIFO_Put(FIFO *fifo, char data);
int FIFO_Get(FIFO *fifo, char *data);

#endif /* FIFO_H_ */
