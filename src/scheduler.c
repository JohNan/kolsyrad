#include "scheduler.h"

pcb *currentPcb;
pcb_queues * S_pcbQ;
free_pcb * S_freeQ;

void S_schedule(){
	currentPcb = S_pcbQ->ready;
	if( S_pcbQ->first_ready == NULL ){
		DputStr( "PiNK SCREEN\n" );
		DputStr( "No processes to run, " );
		while( 1 ){
		}
	} else if( S_pcbQ->ready->priority > S_pcbQ->ready->next->priority ){
		kset_registers( &S_pcbQ->ready->registers );
		S_pcbQ->ready = S_pcbQ->first_ready;
	} else {
		kset_registers( &S_pcbQ->ready->registers );
		S_pcbQ->ready = S_pcbQ->ready->next;
	}

	kload_timer(10 * timer_msec);
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
	return currentPcb;
}

void move_to_int(pcb *who) {
  pcb *p = S_pcbQ->waiting.pcbInt;
  unlink_pcb(who);
  if(p != NULL)
    p->prev = who;
  who->next = p;
  S_pcbQ->waiting.pcbInt = who;
}

void move_to_sleep(pcb *who) {
	pcb *p = S_pcbQ->waiting.pcbTimer;
	unlink_pcb(who);
	if(p != NULL)
		p->prev = who;
	who->next = p;
	S_pcbQ->waiting.pcbTimer = who;
}

void move_to_ready(pcb *who) {
  //DputStr("ready!");
  unlink_pcb(who);
  //DputStr("set!");
  S_add_new_pcb(who);
  //DputStr("go!");

}

void unlink_pcb(pcb *who) {
  if(S_pcbQ->ready == who)
    S_pcbQ->ready = who->next;
  if(S_pcbQ->first_ready == who)
    S_pcbQ->first_ready = who->next;
  if(S_pcbQ->waiting.pcbInt == who)
    S_pcbQ->waiting.pcbInt = who->next;
  if(S_pcbQ->waiting.pcbTimer == who)
    S_pcbQ->waiting.pcbTimer = who->next;

  if(who->next != NULL)
    who->next->prev = who->prev;
  if(who->prev != NULL)
    who->prev->next = who->next;
}

void init_scheduler(pcb_queues * p1, free_pcb * p2){
	S_pcbQ = p1;
	S_freeQ = p2;
}

// tells process q to wait for ms milliseconds
void S_stop_ms( int32_t ms, pcb * q){
  int t;

  if(q == NULL) {
	  q = S_pcbQ->ready->prev;
  }
  t = (q == S_pcbQ->ready->prev); // is it current proc that sleeps?
  q->time = ms;
  //DputStr("Time to sleep!");
  //printPid(q);
  move_to_sleep(q);
  if(t){
	  S_schedule();
  }
}

void S_start( pcb * q ){
  move_to_ready(q);
}

void S_stop( pcb * q ){

}
