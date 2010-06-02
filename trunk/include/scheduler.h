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
void S_add_new_pcb(pcb *toAdd );

/* S_remove_active()
 * TYPES: void -> void
 * PRE: there should be at least one active process
 * POST: none
 * SIDE-EFFECT: removes the active process
 */
void S_remove_active();

/* S_activate_pcb( toActivate )
 * TYPES: pcb * -> void
 * PRE: has to be an inactive process
 * POST: none
 * SIDE-EFFECT: move an inactivated process to running queue
 */
void S_activate_pcb( pcb * toActivate );

/* init_scheduler( p1, p2 )
 * TYPE: pcb_queue *, free_pcb * -> void
 *
 */
void init_scheduler(pcb_queues * p1, free_pcb * p2 );

pcb* getCurrent();

void move_to_ready(pcb *p);
void move_to_int(pcb *p);
void move_to_sleep(pcb *p);
void unlink_pcb(pcb *);
void S_stop_ms( int32_t ms, pcb * q);
void S_start( pcb * q );

#endif





