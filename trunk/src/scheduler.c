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
	runningPcb = nextPcb;
	if(nextPcb->next->priority < nextPcb->priority){
		nextPcb = ready->first;
	} else {
		nextPcb = nextPcb->next;
	}

	kset_register(&runningPcb->registers);
	kload_timer(1 * timer_msec);
}

void insertPcb( queue *q, pcb *newPcb ) {
	if(q->first == NULL){
		q->first = newPcb;
		newPcb->next = newPcb;
		newPcb->prev = newPcb;
	} else if (newPcb->priority > q->first) {
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
				SP_add_before( toAdd, currentInLoop );
				i = 0;
			}
			currentInLoop = currentInLoop->next;
		}
	}
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
	removePcb(ready,q);
	insertPcb(waiting,q);
	if(t){
		S_schedule();
	}
}

void kunblock( pcb * q ){
	removePcb(waiting,q);
	insertPcb(ready,q);
}

void init_scheduler(){
	currentPcb = NULL;
	nextPcb = NULL;
}
