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

queue ready;
queue wating;
queue free;

/*
typedef struct pcb_waiting{
	pcb *pcbTimer;
	pcb *pcbInt;
}pcb_waiting;

typedef struct pcb_queues{
	pcb * first_ready; //a pointer to the first ready process' PCB. It will only change if the process is not longer
	pcb * ready; //a pointer to the currently runnning process' PCB. It will walk through all process of highest current priority when scheduling.
	pcb_waiting waiting; //pointer to waiting processes
} pcb_queues;

typedef struct free_pcb{
	pcb * first;
	pcb * last;
} free_pcb;
*/
extern pcb_queues pcbq;
extern free_pcb free_pcb_q;

#endif
