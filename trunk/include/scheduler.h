#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_handler.h"

/*
 * Jumps to next process in the running queue
 */
void S_schedule();
/*
 * Takes a pointer to a pcb and add it to the running queue
 * at the right place
 */
void S_add_new_pcb( pcb * toAdd );
/*
 * Sets the pointer to the pcb queues
 */
void S_set_pcb_queues( pcb_queues * queue );
/*
 * Sets the pointer to the free pcb queue
 */
void S_set_free_pcb( free_pcb * queue );
/*
 * Removes the current running process pcb and moves it to
 * to free pcb queue
 */
void S_remove_active();
/*
 * Removes a pcb from the running queue. Is used when
 * a process terminates another process
 */
void S_remove_inactive( pcb * toDelete );
/*
 * Moves a waiting pcb to the active queue
 */
void S_activate_pcb( pcb * toActivate );
/*
 * Moves a active pcb to the waiting queue
 */
void S_deactivate_pcb( pcb *toDeactivate);

#endif
