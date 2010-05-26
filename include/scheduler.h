#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "other/asm.h"
#include "other/types.h"
#include "other/stdlib.h"

#include "structs/registers.h"

#include "device_handler.h"
#include "structs.h"

/*
 * Jumps to next process in the running queue
 */
void S_schedule();
/*
 * Takes a pointer to a pcb and add it to the running queue
 * at the right place
 */
void S_add_new_pcb(pcb *toAdd );
/*
 * Removes the current running process pcb and moves it to
 * to free pcb queue
 */
void S_remove_active();
/*
 * Moves a waiting pcb to the active queue
 */
void S_activate_pcb( pcb * toActivate );

void init_scheduler(pcb_queues * p1, free_pcb * p2);

pcb* getCurrent();

#endif
