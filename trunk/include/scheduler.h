#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "other/asm.h"
#include "other/types.h"
#include "other/stdlib.h"

#include "structs/registers.h"

#include "device_handler.h"
#include "structs.h"

/* S_schedule()
 * TYPES: void -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: Schedules for next process to run
 */
void S_schedule();

/* S_add_new_pcb( toAdd )
 * TYPES: pcb * -> void
 * PRE: has to have a valid pcb pointer
 * POST: none
 * SIDE-EFFECT: Adds toAdd to the running process queue
 */
void insertPcb(queue *q, pcb *newPcb);

/* S_remove_active()
 * TYPES: void -> void
 * PRE: there should be at least one active process
 * POST: none
 * SIDE-EFFECT: removes the active process
 */
void removePcb(queue *q, pcb *remPcb);


pcb* getCurrent();
pcb* getNext();


void ksleep( int32_t ms, pcb * q);
void kunblock( pcb * q );

/* init_scheduler( p1, p2 )
 * TYPE: pcb_queue *, free_pcb * -> void
 *
 */
void init_scheduler();

#endif
