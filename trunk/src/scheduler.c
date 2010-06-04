#include "scheduler.h"

pcb *runningPcb;
pcb *nextPcb;

/*
 * Local functions
 */
/* SP_add_before(toAdd,before)
 * TYPE: pcb& * pcb& -> void
 * PRE: toAdd and before must be non-NULL
 * POST: -
 * SIDE-EFFECT: inserts toAdd in front of before
 */
void SP_add_before( pcb * toAdd, pcb * before ){
	toAdd->next = before;
	toAdd->prev = before->prev;
	before->prev->next = toAdd;
	before->prev = toAdd;
}

/*
 * Public functions
 */
/* S_schedule
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: switches to next process
 */
void S_schedule(){

	runningPcb = nextPcb;
	if( readyQ.first == NULL ){
		DputStr("########################\n");
		DputStr("#      PINK SCREEN     #\n");
		DputStr("########################\n");
		while(1){
			__asm( "nop" );
		}
	}else if (nextPcb->next->priority < nextPcb->priority){
		nextPcb = readyQ.first;
	} else {
		nextPcb = nextPcb->next;
	}

	kset_registers(&runningPcb->registers);
	kload_timer(1 * timer_msec);
}

/* insertPcb(q,p)
 * TYPE: queue& * pcb& -> void
 * PRE: q and p must be non-NULL
 * POST: -
 * SIDE-EFFECT: adds p to q
 */
void insertPcb( queue *q, pcb *newPcb ) {
	if(q->first == NULL){
		q->first = newPcb;
		newPcb->next = newPcb;
		newPcb->prev = newPcb;
		if(q == &readyQ){
			nextPcb = newPcb;
		}
	} else if (newPcb->priority > q->first->priority) {
		SP_add_before(newPcb, q->first);
		q->first = newPcb;
		if(q == &readyQ){
			nextPcb = newPcb;
		}
	} else {
		pcb * currentInLoop = q->first->next;
		int i = 1;
		while( i ){
			if( currentInLoop == q->first ){
				SP_add_before( newPcb, currentInLoop );
				i = 0;
			} else if( newPcb->priority > currentInLoop->priority ){
				SP_add_before( newPcb, currentInLoop );
				i = 0;
			}
			currentInLoop = currentInLoop->next;
		}
	}
}

/* removePcb(q,p)
 * TYPE: queue& * pcb& -> void
 * PRE: q and p must be non-NULL
 * POST: -
 * SIDE-EFFECT: removes p from q
 */
void removePcb( queue *q, pcb *remPcb ) {
	if(q->first == remPcb){
		if(q->first->next == remPcb){ //Only one Pcb in queue;
			q->first = NULL;
			q->last = NULL;
		} else {
			if(q == &readyQ){
				if(nextPcb == remPcb) {
					nextPcb = remPcb->next;
				}
			}
			remPcb->prev->next = remPcb->next;
			remPcb->next->prev = remPcb->prev;
			q->first = q->first->next;
			q->first->prev = remPcb->prev;
		}
	} else {
		if(q == &readyQ){
						if(nextPcb == remPcb) {
							nextPcb = remPcb->next;
						}
					}
		remPcb->prev->next = remPcb->next;
		remPcb->next->prev = remPcb->prev;
	}
}

/* getCurrent
 * TYPE: void -> pcb&
 * PRE: -
 * POST: pointer to current running PCB
 */
pcb* getCurrent(){
	return runningPcb;
}

/* getNext
 * TYPE: void -> pcb&
 * PRE:
 * POST: pointer to next running PCB
 */
pcb* getNext(){
	return nextPcb;
}

// tells process q to wait for ms milliseconds
/* ksleep(ms,who)
 * TYPE: int32 * pcb& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: puts who to sleep for ms milliseconds. if who is NULL, the
 *              current process sleeps. if the current process sleeps, call
 *              S_schedule
 */
void ksleep( int32_t ms, pcb * q){
	if(q == NULL) {
		q = getCurrent();
	}
	q->state = 3;
	q->time = ms;

	removePcb(&readyQ,q);
	insertPcb(&waitingQ,q);
}

/* kexit
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: terminates current process and calls S_schedule
 */
void kexit(){
	pcb *delPcb = getCurrent();
	removePcb(&readyQ,delPcb);
	p_free_pcb(delPcb);

	pcb *current = ioqueue.current;
	pcb *prev = NULL;
	while(current != NULL){
		if(delPcb == current){
			if(prev == NULL)
				delPcb->nextIO = ioqueue.current;
			else
				prev->nextIO = delPcb->nextIO;
			break;

		} else{
			prev = current;
			current = current->nextIO;
		}
	}

	S_schedule();
}

/* kunblock(who)
 * TYPE: pcb& -> void
 * PRE: who must not be NULL
 * POST: -
 * SIDE-EFFECT: moves who from waiting queue to ready queue
 */
void kunblock( pcb * q ){
	removePcb(&waitingQ,q);
	insertPcb(&readyQ,q);
	q->state = 2;
}

/* init_scheduler
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: initializes some global pointers
 */
void init_scheduler(){
	runningPcb = NULL;
	nextPcb = NULL;
}
