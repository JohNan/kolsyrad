#ifndef STRUCTS_H
#define STRUCTS_H

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

/*
 * process
 */
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

#endif
