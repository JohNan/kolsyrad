#include "scheduler.h"

//===========================================
// temp
//===========================================
/*
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
*/
//===========================================


pcb_queues * S_PcbQueue = 0;
free_pcb * S_FreePcb = 0;

void * readip(void);
void jumpip( void * );

void add_before( pcb * source, pcb * target ){
	source->next = target;
	source->prev = target->prev;

	target->prev = source;

	source->prev->next = source;
}

// reschedules all processes
void schedule() {
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

	// Kollar om någon process i waiting kö vill köras igen
	if( S_PcbQueue->waiting->flags == 1 ){
		pcb * readyToRun = S_PcbQueue->waiting;
		pcb * currentInLoop = S_PcbQueue->first_ready;

		// Tar ut readyToRun ur waiting kör

		readyToRun->next->prev = readyToRun->prev;
		readyToRun->prev->next = readyToRun->next;
		S_PcbQueue->waiting = readyToRun->next;

		// Och lägger in den i kör kön

		if( readyToRun->priority > currentInLoop->priority ){
			add_before( readyToRun, currentInLoop );
			S_PcbQueue->first_ready = readyToRun;
			runPcb = readyToRun;
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
	} else {
		S_PcbQueue->waiting = S_PcbQueue->waiting->next;
	}

	//=======================================================

	// Här ska alla register laddas in med data och shit

	//=======================================================

	jumpip( runPcb->next_instr );
}

void add_new_pcb( pcb * toAdd ){

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

void remove_pcb(){
	pcb * first = S_PcbQueue->first_ready;
	pcb * running = S_PcbQueue->ready;
	pcb * toDelete = 0;
	pcb * toRun = 0;
	if( running == first ){
		if( first->priority > first->next->priority ){
			first->prev->next = first->next;
			first->next->prev = first->prev;
			toDelete = first;
			first = first->next;
			S_PcbQueue->first_ready = first;
			toRun = first;
		} else {
			toDelete = running;
			running->prev->next = running->next;
			running->next->prev = running->prev;
			S_PcbQueue->first_ready = first->next;
			toRun = running->next;
		}
	} else {
		toDelete = running;
		running->prev->next = running->next;
		running->next->prev = running->prev;
		toRun = running->next;
	}

	toDelete->next = S_FreePcb->first;
	toDelete->prev = S_FreePcb->last;

	S_FreePcb->first->prev = toDelete;
	S_FreePcb->last->next = toDelete;

	// ladda alla register här

	jumpip( toRun->next_instr );
}

void remove_pcb( pcb * removePcb );
void S_set_pcb_queues( pcb_queues * queue ){
	S_PcbQueue = queue;
}
void S_set_free_pcb( free_pcb * queue ){
	S_FreePcb = queue;
}

