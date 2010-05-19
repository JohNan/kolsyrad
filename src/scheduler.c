#include "scheduler.h"

extern pcb_queues pcbq;
extern free_pcb free_pcb_q;

void * readip(void);
void jumpip( void * );

void SP_add_before( pcb * source, pcb * target ){
	source->next = target;
	source->prev = target->prev;

	target->prev = source;

	source->prev->next = source;
}

// reschedules all processes
void S_schedule() {
	// Variable declaration
	void * pNextInstr = 0;
	pcb * runPcb = 0;
	pcb * currentPcb = 0;


	pNextInstr = readip();
	currentPcb = pcbq->ready;
	currentPcb->next_instr = pNextInstr;

	//=======================================================

	// Här ska alla register sparas ner

	//=======================================================

	if( currentPcb->next->priority < currentPcb->priority ){
		pcbq.ready = pcbq.first_ready;
	} else {
		pcbq.ready = currentPcb->next;
	}

	runPcb = pcbq.ready;

	//=======================================================

	// Här ska alla register laddas in med data och shit

	//=======================================================

	kset_registers(&runPcb.registers);

	//jumpip( runPcb->next_instr );
}
void S_add_new_pcb( pcb * toAdd ){

	pcb * currentInLoop = pcbq.first_ready;

	if( toAdd->priority > currentInLoop->priority ){
		SP_add_before( toAdd, currentInLoop );
	} else {
		currentInLoop = currentInLoop->next;

		int i = 1;
		while( i ){
			if( currentInLoop == queue->first_ready ){
				SP_add_before( readyToRun, currentInLoop );
				i = 0;
			} else if( readyToRun->priority > currentInLoop->priority ){
				SP_add_before( readyToRun, currentInLoop );
				i = 0;
			} else {
				i++;
				currentInLoop = currentInLoop->next;
			}
		}
	}
}
void S_set_pcb_queues( pcb_queues * queue ){
	pcbq = queue;
}
void S_set_free_pcb( free_pcb * queue ){
	free_pcb_q = queue;
}
void SP_delete_pcb( pcb * toDelete ){
	toDelete->next->prev = toDelete->prev;
	toDelete->prev->next = toDelete->next;

	free_pcb_q.first->prev = toDelete;
	free_pcb_q.last->next = toDelete;

	toDelete->next = free_pcb_q.first;
	toDelete->prev = free_pcb_q.last;
}
void S_remove_active(){
	pcb * first = pcbq.first_ready;
	pcb * toDelete = pcbq.ready;
	pcb * toRun = 0;
	toDelete->flags = 2;

	if( toDelete = first ){
		toRun = toDelete->next;
	} else {
		if( toDelete->priority > toDelete->next->priority ){
			toRun = pcbq.first_ready;
		} else {
			toRun = toDelete->next;
		}
	}
	SP_delete_pcb( toDelete );

	// ladda register

	jumpip( toRun->next_instr );
}
void S_remove_inactive( pcb * toDelete ){
	pcb * first = pcbq.first_ready;

	if( toDelete == first ){
		pcbq.first_ready = first->next;
	}
	SP_delete_pcb( toDelete );
}
void S_activate_pcb( pcb * toActivate ){
	pcb * first = pcbq.first_ready;
	pcb * inLoop = pcbq.first_ready->next;

	toActivate->flags = 1;

	toActivate->next->prev = toActivate->prev;
	toActivate->prev->next = toActivate->next;

	if( first->priority < toActivate->priority ){
		pcbq.first_ready = toActivate;

		SP_add_before( toActivate, first );
	} else {
		int i = 1;
		while( i ){
			if( inLoop == first ){
				SP_add_before( toActivate, inLoop );
				i = 0;
			} else if( inLoop->priority > inLoop->next->priority ){
				SP_add_before( toActivate, inLoop->next );
				i = 0;
			}
		}
	}
}
void SP_move_to_waiting( pcb * toMove ){
	if( pcbq.waiting == 0 ){
		toDeactivate->next = toDeactivate;
		toDeactivate->prev = toDeactivate;

		pcbq.waiting = toDeactivate;
	} else {
		toDeactivate->next = pcbq.waiting;
		toDeactivate->prev = pcbq.waiting->prev;

		pcbq.waiting->prev->next = toDeactivate;
		pcbq.waiting->prev = toDeactivate;
	}
}
void S_deactivate_pcb( pcb *toDeactivate){
	toDeactivate->flags = 2;
	pcb * first = pcbq.first_ready;
	if( toDeactivate == first ){
		pcbq.first_ready = first->next;
		toDeactivate->prev->next = toDeactivate->next;
		toDeactivate->next->prev = toDeactivate->prev;
	}
	SP_move_to_waiting( toDeactivate );
}
