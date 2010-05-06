#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H
#define PROC_COUNT 30

#include "types.h"

typedef struct pcb{
	short pid;
	short progid;
	uint8_t priority;
	uint8_t state;
	short flags;
	int registrers_array[16];
	struct pcb *next;
	struct pcb *prev;
}pcb;

typedef struct {  // Program information block
	short progid; // Hold the program ID.
	char pname[16]; // The human readable name of the program.
	void * start_ptr; // A pointer to the entry point of the program
}pib;

typedef struct {
	pcb pcb_array[PROC_COUNT]; // An array of all current pcb's.
}proc_handler;

typedef struct {
	pcb * first_ready; //a pointer to the first ready process' PCB. It will only change if the process is not longer
	pcb * ready; //a pointer to the currently runnning process' PCB. It will walk through all process of highest current priority when scheduling.
	pcb * waiting; //a pointer to the first waiting process' PCB.
} pcb_queues;


#endif
