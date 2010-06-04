#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H

#define RUNNING 1
#define WAITING 2

#include "other/types.h"

#include "structs/registers.h"

#include "kjell.h"
#include "scheduler.h"
#include "structs.h"
#include "user_prog.h"
#include "_boot.h"

#define MAX_PROCESS 20 // maximum number of processes
#define MAX_PROGRAM 20 // maximum number of programs
#define STACK_SIZE 1024 // stack size for programs

/* Process states */
#define PS_FREE 0; // this PCB is free
#define PS_START 1; // this process is being initialized by kernel
#define PS_READY 2; // this process is ready to run
#define PS_SLEEP 3; // this process is waiting for something
#define PS_DEAD 4; // this process has finished execution

// global variables, defined in process_handler.c
extern pcb pcbs[];
extern pib pibs[];

void init_poc();

//creates an PCB for a new process returns -1 if fail else pidx
pcb *get_pcb(void);

//marks the given PCB as free and adds it to the free list
void p_free_pcb(pcb *);

//terminates process either normaly or abnormaly
void exit();

// unblocks a process
void unblock(pcb *);

// sets priority on processes
void set_priority(pcb *,int);

// Returns a list of processes in any queue. Argument will decide what queues to return.
pcb *list_queue(int);

// Make a process
int make_process( int pibsNr, int prio, uint32_t args );

//
int knewP( int pibsNr, int prio, uint32_t args);

void kkill(int pid);

//returns the priority of process with pib p
uint8_t kgetPriority(uint8_t p);
//returns the state of process with pib p
uint8_t kgetState(uint8_t p);
//returns the name of process with pib p
char *kgetName(uint8_t p);

uint8_t pcb_exists( uint8_t p );

#define PL_READY 1
#define PL_SLEEP 2

#endif
