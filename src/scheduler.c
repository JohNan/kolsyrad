#include "scheduler.h"

pcb_queues * S_pcbQ;
free_pcb * S_freeQ;

void S_schedule(){
	if( S_pcbQ->first_ready == NULL ){
		DputStr( "PiNK SCREEN\n" );
		DputStr( "No processes to run, " );
		while( 1 ){
			DputStr( "rEEbOOt" );
		}
	} else if( S_pcbQ->ready->priority > S_pcbQ->ready->next->priority ){
		kset_registers( &S_pcbQ->ready->registers );
		S_pcbQ->ready = S_pcbQ->first_ready;
	} else {
		kset_registers( &S_pcbQ->ready->registers );
		S_pcbQ->ready = S_pcbQ->ready->next;
	}

	kload_timer(1 * timer_msec);
}

void SP_add_before( pcb * toAdd, pcb * before ){
	toAdd->next = currentInLoop;
	toAdd->prev = currentInLoop->prev;
	currentInLoop->prev->next = toAdd;
	currentInLoop->prev = toAdd;
}

void S_add_new_pcb( pcb * toAdd ){
	if( S_pcbQ->first_ready == NULL ){
		S_pcbQ->first_ready = toAdd;
		S_pcbQ->ready = toAdd;

		toAdd->next = toAdd;
		toAdd->prev = toAdd;
	} else {
		pcb * currentInLoop = S_pcbQ->first_ready;
		if( toAdd->priority > currentInLoop->priority ){
			SP_add_before( toAdd, currentInLoop );

			S_pcbQ->first_ready = toAdd;
			S_pcbQ->ready = toAdd;
		} else {
			currentInLoop = currentInLoop->next;

			int i = 1;
			while( i ){
				if( currentInLoop == S_pcbQ->first_ready ){
					SP_add_before( toAdd, currentInLoop );
					i = 0;
				} else if( toAdd->priority > currentInLoop->priority ){
					SP_add_before( toAdd, currentInLoop );
					i = 0;
				}
				currentInLoop = currentInLoop->next;
			}

		}
	}
}

void SP_add_to_free( pcb * q ){
	q->prev = NULL;

	if( S_freeQ->first == NULL ){
		q->next = NULL;
		S_freeQ->first = q;
		S_freeQ->last = q;
	} else {
		q->next = S_freeQ->first;
		S_freeQ->first = q;
	}
}

void S_remove_active(){
	pcb * current = NULL;
	current = S_pcbQ->ready->prev;

	if( S_pcbQ->ready == current ){
		DputStr( "S_remove_active: 1\n" );

		S_pcbQ->ready = NULL;
		S_pcbQ->first_ready = NULL;
	} else if( current == S_pcbQ->first_ready ){
		DputStr( "S_remove_active: 2\n" );
		current->prev->next = current->next;
		current->next->prev = current->prev;

		S_pcbQ->first_ready = current->next;
	} else {
		DputStr( "S_remove_active: 3\n" );
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	SP_add_to_free( current );
}

pcb* getCurrent(){
	return S_pcbQ->ready->prev;
}

void init_scheduler(pcb_queues * p1, free_pcb * p2){
	S_pcbQ = p1;
	S_freeQ = p2;
}

