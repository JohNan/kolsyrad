#include "process_handler.h"

pcb pcbs[MAX_PROCESS];
pib pibs[MAX_PROGRAM] = {
  {0, "idle", (int)&idle},
  {1, "malta_scroll", (int)&mscroll},
  {2, "kjell", (int)&kjell},
  {3, "increment", (int)&increment},
  {4, "fibonacci", (int)&fibonacci},
  {5, "printp", (int)&smile}
};

uint8_t pstack[MAX_PROCESS][STACK_SIZE];

/* init_poc()
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: initializes all proces related structures
 */
void init_poc() {
  int i;

	readyQ.first =
	readyQ.last =
		freeQ.first =
		freeQ.last =
			waitingQ.first =
			waitingQ.last = NULL;

  freeQ.first = &pcbs[0];
  freeQ.last = &pcbs[MAX_PROCESS - 1];

  pcbs[0].pid = 0;
  pcbs[0].progid = NULL;
  pcbs[0].priority = 0;
  pcbs[0].state = PS_FREE;
  pcbs[0].flags = 0;
  /* registers do not need init */
  // except for SP
  pcbs[0].registers.sp_reg = (uint32_t) &pstack[MAX_PROCESS];
  pcbs[0].next = &pcbs[1];
  pcbs[0].prev = &pcbs[MAX_PROCESS - 1];
  pcbs[0].time = 0;
  /* next_instr does not need init */

  pcbs[MAX_PROCESS - 1].pid = MAX_PROCESS - 1;
  pcbs[MAX_PROCESS - 1].progid = NULL;
  pcbs[MAX_PROCESS - 1].priority = 0;
  pcbs[MAX_PROCESS - 1].state = PS_FREE;
  pcbs[MAX_PROCESS - 1].flags = 0;
  /* registers do not need init */
  pcbs[MAX_PROCESS - 1].registers.sp_reg = (uint32_t) &pstack[1];
  pcbs[MAX_PROCESS - 1].next = &pcbs[0];
  pcbs[MAX_PROCESS - 1].prev = &pcbs[MAX_PROCESS - 2];
  pcbs[MAX_PROCESS - 1].time = 0;
  /* next_instr does not need init */

  for(i = 1; i < (MAX_PROCESS - 1); i++) {
    pcbs[i].pid = i;
    pcbs[i].progid = NULL;
    pcbs[i].priority = 0;
    pcbs[i].state = PS_FREE;
    pcbs[i].flags = 0;
    /* registers do not need init */
    pcbs[i].registers.sp_reg = (uint32_t) &pstack[i];
    pcbs[i].next = &pcbs[i + 1];
    pcbs[i].prev = &pcbs[i - 1];
    pcbs[i].time = 0;
    /* next_instr does not need init */
  }

  //DputStr("Process init done");
}

//creates an PCB for a new process returns -1 if fail else pidx
// note that the returned PCB is completely unlinked
pcb *get_pcb(void) {
        pcb *p = freeQ.first;
        removePcb(&freeQ,p);
        return p;
}


//marks the given PCB as free and adds it to the free list
//the given PCB must be unlinked
/* p_free_pcb(p)
 * TYPE: pcb& -> void
 * PRE: p must not be NULL
 * POST: -
 * SIDE-EFFECT: moves p to the free queue
 */
void p_free_pcb(pcb *p) {
	insertPcb(&freeQ,p);
	p->progid = NULL;
	p->state = PS_FREE;
}

//terminates process either normaly or abnormaly
// currently, exit status is ignored
/* exit
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: terminates the current process
 */
void exit() {
	syscall_exit();
	while(1){}
}

// sets priority on processes
/* set_priority(who,prio)
 * TYPE: pcb& * int -> void
 * PRE: who must not be NULL
 * POST: -
 * SIDE-EFFECT: sets the priority of who to prio
 */
void set_priority(pcb *who, int p) {
  who->priority = p;
}

char pcb_exists(uint8_t p){
	if(pcbs[p].state != PS_FREE)
		return 1;
	else
		return 0;
}

//returns the priority of process with pib p
uint8_t kgetPriority(uint8_t p){
	uint8_t ret = -1;
	if (pcb_exists(p) == 1){
		ret = pcbs[p].priority;
	}
	kget_registers()->v_reg[0] = (int) ret;
	return NULL;
}
//returns the state of process with pib p
uint8_t kgetState(uint8_t p){
	uint8_t ret = -1;
	if (pcb_exists(p)){
		ret = pcbs[p].state;
	}
	kget_registers()->v_reg[0] = (int) ret;
	return NULL;
}
//returns the name of process with pib p
char *kgetName(uint8_t p){
	uint8_t ret = -1;
	if (pcb_exists(p)){
		ret = pcbs[p].state;
	}
	kget_registers()->v_reg[0] = (int) ret;
	return NULL;
}

// Returns a list of processes in any queue. Argument will decide what queues to return.
/* list_queue(what)
 * TYPE: int -> pcb&
 * PRE: -
 * POST: the requested list, or NULL if what is not a valid queue identifier
 */
pcb *list_queue(int what) {
  switch(what) {
  case PL_READY:
    return readyQ.first;
  case PL_SLEEP:
    return waitingQ.first;
  }
  return NULL;
}

/* make_process(pib, prio, args)
 * TYPE: int * int * uint32 -> int
 * PRE: pib must be an index to a valid PIB
 * POST: the pid of the created process
 * SIDE-EFFECT: initializes the new PCB and adds it to scheduling
 */
int make_process( int pibsNr, int prio, uint32_t args ){
	pcb *newPcb = get_pcb();

	newPcb->progid = &pibs[pibsNr];
	newPcb->state = PS_READY;
	newPcb->registers.epc_reg = newPcb->progid->start_ptr;
	newPcb->registers.ra_reg = (int)&exit;
	newPcb->registers.a_reg[0] = args;
	newPcb->priority = prio;
	newPcb->fifoOut.length = 0;
	newPcb->fifoIn.length = 0;
	newPcb->nextIO = 0;
	newPcb->next = newPcb->prev = NULL;
	insertPcb(&readyQ,newPcb);
//	S_schedule();
	return newPcb->pid;
}

/*
 * SYSCALLS
 */
/* make_process(pib, prio, args)
 * TYPE: int * int * uint32 -> int
 * PRE: pib must be an index to a valid PIB
 * POST: the pid of the created process
 * SIDE-EFFECT: initializes the new PCB and adds it to scheduling
 */
int knewP( int pibsNr, int prio, uint32_t args){
	pcb *newPcb = get_pcb();

	newPcb->progid = &pibs[pibsNr];
	newPcb->state = PS_READY;
	newPcb->registers.epc_reg = newPcb->progid->start_ptr;
	newPcb->registers.ra_reg = (int)&exit;
	newPcb->registers.a_reg[0] = args;
	newPcb->priority = prio;
	newPcb->fifoOut.length = 0;
	newPcb->fifoIn.length = 0;
	newPcb->nextIO = 0;
	newPcb->next = newPcb->prev = NULL;
	insertPcb(&readyQ,newPcb);
	S_schedule();

	kget_registers()->v_reg[0] = (int)newPcb->pid;

	return newPcb->pid;
}

void kkill(int pid){
	if(pcbs[pid].state == 2){
		removePcb(&readyQ, &pcbs[pid]);
		p_free_pcb(&pcbs[pid]);
	} else if(pcbs[pid].state == 3){
		removePcb(&waitingQ, &pcbs[pid]);
		p_free_pcb(&pcbs[pid]);
	}
}


