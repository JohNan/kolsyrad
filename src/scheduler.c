#include "scheduler.h"

pcb *runningPcb;
pcb *nextPcb;

/*
 * Local functions
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
void S_schedule(){
/*	DputStr("----Schedule-RUN---");
	printPid(runningPcb);

	DputStr("----Schedule-NEXT---");
	printPid(nextPcb);
*/
	runningPcb = nextPcb;
	if(nextPcb->next->priority < nextPcb->priority){
		nextPcb = readyQ.first;
	} else {
		nextPcb = nextPcb->next;
	}

	kset_registers(&runningPcb->registers);
	kload_timer(1 * timer_msec);
}

void insertPcb( queue *q, pcb *newPcb ) {
	if(q->first == NULL){
		q->first = newPcb;
		newPcb->next = newPcb;
		newPcb->prev = newPcb;
		nextPcb = newPcb;
	} else if (newPcb->priority > q->first->priority) {
		SP_add_before(newPcb, q->first);
		q->first = newPcb;
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
	DputStr("----InserPcb-Added---");
	printPid(newPcb);
}

void removePcb( queue *q, pcb *remPcb ) {
	if(q->first == remPcb){
		if(q->first->next == remPcb){ //Only one Pcb in queue;
			q->first = NULL;
			q->last = NULL;
		} else {
			remPcb->prev->next = remPcb->next;
			remPcb->next->prev = remPcb->prev;
			q->first = q->first->next;
			q->first->prev = remPcb->prev;
		}
	} else {
		remPcb->prev->next = remPcb->next;
		remPcb->next->prev = remPcb->prev;
	}
}

pcb* getCurrent(){
	return runningPcb;
}

pcb* getNext(){
	return nextPcb;
}

// tells process q to wait for ms milliseconds
void ksleep( int32_t ms, pcb * q){
	int t;
	if(q == NULL) {
		q = getCurrent();
	}
	t = (q == getCurrent()); // is it current proc that sleeps?
	q->time = ms;
	//DputStr("Time to sleep!");
	//printPid(q);
	removePcb(&readyQ,q);
	insertPcb(&waitingQ,q);
	if(t){
		S_schedule();
	}
}

void kexit(){
	pcb *delPcb = getCurrent();
	removePcb(&readyQ,delPcb);
	insertPcb(&freeQ,delPcb);
	S_schedule();
}

void kunblock( pcb * q ){
	removePcb(&waitingQ,q);
	insertPcb(&readyQ,q);
}

void init_scheduler(){
	runningPcb = NULL;
	nextPcb = NULL;
}
