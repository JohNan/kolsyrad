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
	toAdd->next = before;
	toAdd->prev = before->prev;
	before->prev->next = toAdd;
	before->prev = toAdd;
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

void S_stop( pcb * q ){
	if( q == S_pcbQ->first_ready ){
		if( q == S_pcbQ->ready ){
			S_pcbQ->first_ready = q->next;
			S_pcbQ->ready = q->next;
		} else {
			S_pcbQ->first_ready = q->next;
		}
	}

	q->next->prev = q->prev;
	q->prev->next = q->next;

	q->next = S_pcbQ->waiting;
	q->prev = S_pcbQ->waiting->prev;
	S_pcbQ->waiting->prev->next = q;
	S_pcbQ->waiting->prev = q;
}

void S_start( pcb * q ){
	if( q->priority > S_pcbQ->first_ready->priority ){
		q->next->prev = q->prev;
		q->prev->next = q->next;

		SP_add_before( q, S_pcbQ->first_ready );
		S_pcbQ->ready = q;
		S_pcbQ->first_ready = q;
	} else {
		pcb * inLoop = S_pcbQ->first_ready->next;
		int i = 1;
		while( i ){
			if( inLoop == S_pcbQ->first_ready ){
				SP_add_before( q, inLoop );
				i = 0;
			} else if( inLoop->priority > inLoop->next->priority ){
				SP_add_before( q, inLoop->next );
				i = 0;
			}
			inLoop = inLoop->next;
		}
	}
}
