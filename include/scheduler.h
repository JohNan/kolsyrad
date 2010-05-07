#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_handler.h"

/* Kommer att fixa så att man aldrig kommer att behöva ge
 * en pekare till pcb_queues eller free_pcb structerna.
 */
pcb_queues * S_PcbQueue = 0;
free_pcb * S_FreePcb = 0;

void S_schedule( pcb_queues * queue );

// Lägger till en ny pcb i pcb queues
void S_add_new_pcb( pcb * toAdd, pcb_queues * queue );
void S_set_pcb_queues( pcb_queues * queue );
void S_set_free_pcb( free_pcb * queue );
void S_remove_active();
void S_remove_inactive( pcb * toDelete );
// Ska alltid ligga i waiting kön
void S_activate_pcb( pcb * toActivate );
// Ska alltid ligga i kör kön
void S_deactivate_pcb( pcb *toDeactivate);
#endif
