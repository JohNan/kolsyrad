#include "scheduler.h"

void * readip(void);
void jumpip( void * );

void add_before( pcb * source, pcb * target ){
	source->next = target;
	source->prev = target->prev;

	target->prev = source;

	source->prev->next = source;
}

// reschedules all processes
void schedule( pcb_queues * queue ) {
	// Variable declaration
	void * pNextInstr = 0;
	pcb * runPcb = 0;
	pcb * currentPcb = 0;


	pNextInstr = readip();
	currentPcb = queue->ready;
	currentPcb->next_instr = pNextInstr;

	//=======================================================

	// Här ska alla register sparas ner

	//=======================================================

	if( currentPcb->next->priority < currentPcb->priority ){
		queue->ready = queue->first_ready;
	} else {
		queue->ready = currentPcb->next;
		runPcb = queue->ready;
	}

	// Kollar om någon process i waiting kö vill köras igen
	if( queue->waiting->flags == 1 ){
		pcb * readyToRun = queue->waiting;
		pcb * currentInLoop = queue->first_ready;

		// Tar ut readyToRun ur waiting kör

		readyToRun->next->prev = readyToRun->prev;
		readyToRun->prev->next = readyToRun->next;
		queue->waiting = readyToRun->next;

		// Och lägger in den i kör kön

		if( readyToRun->priority > currentInLoop->priority ){
			add_before( readyToRun, currentInLoop );
			queue->first_ready = readyToRun;
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
				}
			}
		}
	} else {
		queue->waiting = queue->waiting->next;
	}

	//=======================================================

	// Här ska alla register laddas in med data och shit

	//=======================================================

	jumpip( runPcb->next_instr );
}
