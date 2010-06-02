#include "process_handler.h"

pcb pcbs[MAX_PROCESS];
pib pibs[MAX_PROGRAM] = {
  {0, "idle", (int)&idle},
  {1, "malta_scroll", (int)&mscroll},
  {2, "kjell", (int)&kjell},
  {3, "increment", (int)&increment},
  {4, "fibonacci", (int)&fibonacci}
};
pcb_queues pcbq;
free_pcb free_pcb_q;

uint8_t pstack[MAX_PROCESS+1][STACK_SIZE];

/* init_poc()
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: initializes all proces related structures
 */
void init_poc() {
  int i;

  pcbq.first_ready =
    pcbq.ready =
    pcbq.waiting.pcbTimer =
    pcbq.waiting.pcbInt = NULL;

  free_pcb_q.first = &pcbs[0];
  free_pcb_q.last = &pcbs[MAX_PROCESS - 1];

  pcbs[0].pid = 0;
  pcbs[0].progid = NULL;
  pcbs[0].priority = 0;
  pcbs[0].state = PS_FREE;
  pcbs[0].flags = 0;
  /* registers do not need init */
  // except for SP
  pcbs[0].registers.sp_reg = (uint32_t) &pstack[1];
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
  pcbs[MAX_PROCESS - 1].registers.sp_reg = (uint32_t) &pstack[MAX_PROCESS];
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
    pcbs[i].registers.sp_reg = (uint32_t) &pstack[i+1];
    pcbs[i].next = &pcbs[i + 1];
    pcbs[i].prev = &pcbs[i - 1];
    pcbs[i].time = 0;
    /* next_instr does not need init */
  }

  //DputStr("Process init done");
}

//updates the process table (PID is the index of array and the data is a pointer to PCB)
void set_pcb_image(pib *newPIB) {
 // (pcbq.ready) -> progid = newPIB -> progid;
  /*__inline__ __asm__ {
	  sw ra,newPIB->start_ptr
	  }*/
  /* need some inline asm code here to mess about with the stack frame
     so that when we return, execution continues at the starting point of
     new new program */
  /* stack frame should look something like:
     sp ----> empty
     sp-4 --> return addr
  */
}

// creates a new process with the same PIB
/*
int fork() {
  int pid = get_pcb();
  if(pid > -1) {
    //pcbs[pid]
  }
  return pid;
}
*/
//creates an PCB for a new process returns -1 if fail else pidx
// note that the returned PCB is completely unlinked
pcb *get_pcb(void) {
  pcb *p;

 /* if(free_pcb_q.first == NULL)
    return -1; */
  p = free_pcb_q.first;
  p->state = PS_START;
  free_pcb_q.first = p -> next;
  p->prev = p->next = NULL;
  return p;
}

//marks the given PCB as free and adds it to the free list
//the given PCB must be unlinked
void p_free_pcb(pcb *p) {
  if(free_pcb_q.last == NULL)
    free_pcb_q.first = free_pcb_q.last = p;
  else {
    p->prev = free_pcb_q.last;
    free_pcb_q.last = p->prev->next = p;
  }
  p->progid = NULL;
  p->state = PS_FREE;
}

//terminates process either normaly or abnormaly
// currently, exit status is ignored
void exit() {
	syscall_exit();
  while(1){}
}

// unblocks a process
/*
void unblock(pcb *who) {
  if(pcbq.waiting == who)
    pcbq.waiting = who->next;

  // unlink
  if(who->prev != NULL)
    who->prev->next = who->next;
  if(who->next != NULL)
    who->next->prev = who->prev;
  who->prev = who->next = NULL;

  // TODO: call the scheduler to insert it at the right place in ready Q
}
*/

// sets priority on processes
void set_priority(pcb *who, int p) {
  who->priority = p;
}

// Returns a list of processes in any queue. Argument will decide what queues to return.
pcb *list_queue(int what) {
  switch(what) {
  case PL_READY:
    return pcbq.ready;
  case PL_SLEEP:
    return pcbq.waiting.pcbInt;
  }
  return NULL;
}

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
	S_add_new_pcb( newPcb );
//	S_schedule();
	return newPcb->pid;
}

/*
 * SYSCALLS
 */
void knewP( int pibsNr, int prio, uint32_t args){
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
	S_add_new_pcb( newPcb );
	S_schedule();
}

