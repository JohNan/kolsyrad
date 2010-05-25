#include "scheduler.h"

pcb_queues * S_pcbQ;
free_pcb * S_freeQ;

void S_schedule(){
	DputStr("------SCHEMA------");
	if( S_pcbQ->first_ready == NULL ){
		DputStr("------SCHEMA-NULL------");
		//Do nothing
	} else {
		kset_registers( &( S_pcbQ->ready->registers ) );

		S_pcbQ->ready = S_pcbQ->ready->next;

	}
}

void S_add_new_pcb( pcb * toAdd ){
	if( S_pcbQ->first_ready == NULL ){
		S_pcbQ->first_ready = toAdd;
		S_pcbQ->ready = toAdd;

		toAdd->next = toAdd;
		toAdd->prev = toAdd;
	} else {
		toAdd->next = S_pcbQ->ready;
		toAdd->prev = S_pcbQ->ready->prev;
		S_pcbQ->ready->prev->next = toAdd;
		S_pcbQ->ready->prev = toAdd;
	}
}

void S_remove_active(){
	DputStr("------REMOVE------");
	pcb * current = NULL;
	current = S_pcbQ->ready->prev;

	DputCh( S_pcbQ->ready->pid );

	char temp[10];
	itoa( S_pcbQ->magic, temp, 10 );
	temp[9] = '\0';
	DputStr( temp );

	if( S_pcbQ->ready == S_pcbQ->ready->prev ){
		DputStr( "------REMOVE-Fisk------" );
		S_pcbQ->ready->next = S_freeQ->first;
		S_freeQ->first = S_pcbQ->ready;

		S_pcbQ->ready = NULL;
		S_pcbQ->first_ready = NULL;
	} else if( current == S_pcbQ->first_ready ){
		DputStr("------REMOVE-ELSE-L44------");
		current->prev->next = current->next;
		current->next->prev = current->prev;

		S_pcbQ->first_ready = current->next;

		if( S_freeQ->first == NULL ){
			current->next = NULL;
			S_freeQ->first = current;
		} else {
			current->next = S_freeQ->first;
			S_freeQ->first = current;
		}
	} else {
		DputStr("------ALLT-ANNAT------" );
	}

	DputStr( "------EXIT-REMOVE------" );
}

void init_scheduler(pcb_queues * p1, free_pcb * p2){
	S_pcbQ = p1;
	S_freeQ = p2;
}

