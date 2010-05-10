#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H
#define PROC_COUNT 30

#define RUNNING 1
#define WAITING 2

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
	void * next_instr;
}pcb;

typedef struct pib{  // Program information block
	short progid; // Hold the program ID.
	char pname[16]; // The human readable name of the program.
	void * start_ptr; // A pointer to the entry point of the program
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

//updates the process table (PID is the index of array and the data is a pointer to PCB)
void set_exec_image(void);

//creates an PCB for a new process returns -1 if fail else pidx
void get_pcb(void);

//creates an PCB for a new process returns -1 if fail else pid
void p_free_pcb();

//terminates process either normaly or abnormaly
void exit(void);

// unblocks a process
void unblock(void);

// sets priority on processes
void set_priority(void);

// Returns a list of processes in any queue. Argument will decide what queues to return.
void list_queue(void);


#endif
