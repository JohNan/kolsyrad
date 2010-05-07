#include "scheduler.h"

//===========================================
// temp
//===========================================

typedef struct pcb{
	short pid;
	short progid;
	uint8_t priority;
	uint8_t state;
	short flags;
	int registrers_array[16];
	struct pcb *next;
	struct pcb *prev;
	void * next_instr;
}pcb;

typedef struct pcb_queues{
	pcb * first_ready; //a pointer to the first ready process' PCB. It will only change if the process is not longer
	pcb * ready; //a pointer to the currently runnning process' PCB. It will walk through all process of highest current priority when scheduling.
	pcb * waiting; //a pointer to the first waiting process' PCB.
} pcb_queues;

typedef struct free_pcb{
	pcb * first;
	pcb * last;
} free_pcb;

//===========================================


pcb_queues * S_PcbQueue = 0;
free_pcb * S_FreePcb = 0;

void * readip(void);
void jumpip( void * );

void S_add_before( pcb * source, pcb * target ){
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
	currentPcb = S_PcbQueue->ready;
	currentPcb->next_instr = pNextInstr;

	//=======================================================

	// Här ska alla register sparas ner

	//=======================================================

	if( currentPcb->next->priority < currentPcb->priority ){
		S_PcbQueue->ready = S_PcbQueue->first_ready;
	} else {
		S_PcbQueue->ready = currentPcb->next;
	}

	runPcb = S_PcbQueue->ready;

	//=======================================================

	// Här ska alla register laddas in med data och shit

	//=======================================================

	jumpip( runPcb->next_instr );
}
void S_add_new_pcb( pcb * toAdd ){

	pcb * currentInLoop = S_PcbQueue->first_ready;

	if( toAdd->priority > currentInLoop->priority ){
		add_before( toAdd, currentInLoop );
	} else {
		currentInLoop = currentInLoop->next;

		int i = 1;
		while( i ){
			if( currentInLoop == queue->first_ready ){
				add_before( readyToRun, currentInLoop );
				i = 0;
			} else if( readyToRun->priority > currentInLoop->priority ){
				add_before( readyToRun, currentInLoop );
				i = 0;
			} else {
				i++;
				currentInLoop = currentInLoop->next;
			}
		}
	}
}
void S_set_pcb_queues( pcb_queues * queue ){
	S_PcbQueue = queue;
}
void S_set_free_pcb( free_pcb * queue ){
	S_FreePcb = queue;
}
void S_delete_pcb( pcb * toDelete ){
	toDelete->next->prev = toDelete->prev;
	toDelete->prev->next = toDelete->next;

	S_FreePcb->first->prev = toDelete;
	S_FreePcb->last->next = toDelete;

	toDelete->next = S_FreePcb->first;
	toDelete->prev = S_FreePcb->last;
}
void S_remove_active(){
	pcb * first = S_PcbQueue->first_ready;
	pcb * toDelete = S_PcbQueue->ready;
	pcb * toRun = 0;

	if( toDelete = first ){
		toRun = toDelete->next;
	} else {
		if( toDelete->priority > toDelete->next->priority ){
			toRun = S_PcbQueue->first_ready;
		} else {
			toRun = toDelete->next;
		}
	}
	S_delete_pcb( toDelete );

	// ladda register

	jumpip( toRun->next_instr );
}
void S_remove_inactive( pcb * toDelete ){
	pcb * first = S_PcbQueue->first_ready;

	if( toDelete == first ){
		S_PcbQueue->first_ready = first->next;
	}
	S_delete_pcb( toDelete );
}
void S_activate_pcb( pcb * toActivate ){
	pcb * first = S_PcbQueue->first_ready;
	pcb * inLoop = S_PcbQueue->first_ready->next;

	toActivate->next->prev = toActivate->prev;
	toActivate->prev->next = toActivate->next;

	if( first->priority < toActivate->priority ){
		S_PcbQueue->first_ready = toActivate;

		S_add_before( toActivate, first );
	} else {
		int i = 1;
		while( i ){
			if( inLoop == first ){
				S_add_before( toActivate, inLoop );
				i = 0;
			} else if( inLoop->priority > inLoop->next->priority ){
				S_add_before( toActivate, inLoop->next );
				i = 0;
			}
		}
	}
}
void S_deactivate_pcb( pcb *toDeactivate){
	// måste göras
}
