#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H
#define PROC_COUNT 30

#define RUNNING 1
#define WAITING 2

#include "types.h"
#include "registers.h"

typedef struct pcb{
	short pid;
	short progid;
	uint8_t priority;
	uint8_t state;
	short flags;
	registers_t registers;
	struct pcb *next;
	struct pcb *prev;
	void * next_instr;
}pcb;

#define MAX_PROCESS 20 // maximum number of processes
#define MAX_PROGRAM 5 // maximum number of programs
#define STACK_SIZE 1024 // stack size for programs

/* Process states */
#define PS_FREE 0; // this PCB is free
#define PS_START 1; // this process is being initialized by kernel
#define PS_READY 2; // this process is ready to run
#define PS_SLEEP 3; // this process is waiting for something
#define PS_DEAD 4; // this process has finished execution

typedef struct pib{  // Program information block
	short progid; // Hold the program ID.
	char pname[16]; // The human readable name of the program.
	int start_ptr; // A pointer to the entry point of the program
}pib;

typedef struct proc_handler{
	pcb pcb_array[PROC_COUNT]; // An array of all current pcb's.
}proc_handler;

typedef struct pcb_queues{
	pcb * first_ready; //a pointer to the first ready process' PCB. It will only change if the process is not longer
	pcb * ready; //a pointer to the currently runnning process' PCB. It will walk through all process of highest current priority when scheduling.
	pcb * waiting; //a pointer to the first waiting process' PCB.
} pcb_queues;

typedef struct free_pcb{
	pcb * first;
	pcb * last;
} free_pcb;

// global variables, defined in process_handler.c
extern pcb pcbs[];
extern pib pibs[];
extern pcb_queues pcbq;
extern free_pcb free_pcb_q;

void init_poc();
//updates the process table (PID is the index of array and the data is a pointer to PCB)
void set_pcb_image(pib *);

//creates an PCB for a new process returns -1 if fail else pidx
int get_pcb(void);

//marks the given PCB as free and adds it to the free list
void p_free_pcb(pcb *);

//terminates process either normaly or abnormaly
void exit(int);

// unblocks a process
void unblock(pcb *);

// sets priority on processes
void set_priority(pcb *,int);

// Returns a list of processes in any queue. Argument will decide what queues to return.
pcb *list_queue(int);

#define PL_READY 1
#define PL_SLEEP 2

#endif
