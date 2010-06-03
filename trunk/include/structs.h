#ifndef STRUCTS_H
#define STRUCTS_H

#include "other/types.h"
#include "structs/registers.h"

#define FIFO_SIZE 32
#define PROC_COUNT 30

/*
 * device
 */
typedef struct {
	short id; // Unique id of device
	short owner; // PID of owning process or -1 if device is free.
	void * buffer_address; // Pointer to static assigned buffer space or NULL if device does not have a buffer.
} Device;

/* A simple FIFO queue of bounded size. */
typedef struct {
  uint8_t  buf[FIFO_SIZE];
  uint32_t length;
} bounded_fifo;

bounded_fifo bfifoOut;
bounded_fifo bfifoIn;

/*
 * Program Information Block
 */
typedef struct pib{  // Program information block
	short progid; // Hold the program ID.
	char pname[16]; // The human readable name of the program.
	int start_ptr; // A pointer to the entry point of the program
}pib;

/*
 * process
 */
typedef struct pcb{
	char pid;
	char flags;
	uint8_t priority;
	uint8_t state;
	pib *progid;
	bounded_fifo fifoOut;
	bounded_fifo fifoIn;
	registers_t registers;
	struct pcb *next;
	struct pcb *prev;
	struct pcb *nextIO;
	int time;
}pcb;

typedef struct io_queue{
	pcb *current;
	pcb *last;
}io_queue;

io_queue ioqueue;

typedef struct queue {
	pcb * first;
	pcb * last;
} queue;

queue readyQ;
queue waitingQ;
queue freeQ;

#endif
