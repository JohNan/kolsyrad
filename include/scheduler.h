#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_handler.h"

/* Kommer att fixa så att man aldrig kommer att behöva ge
 * en pekare till pcb_queues eller free_pcb structerna.
 */
pcb_queues * S_PcbQueue = 0;
free_pcb * S_FreePcb = 0;

void schedule( pcb_queues * queue );

// Lägger till en ny pcb i pcb queues
void add_new_pcb( pcb * toAdd, pcb_queues * queue );

/* Om processen som körs har terminerat av sig själv.
 * Antar att det bara är processer som kör som någonsin
 * kan terminera, men eftersom det kan finnas möjligheten
 * så kodar jag två olika med samma namn men med olika antal
 * argument.
 */

/* Denna funktion tar bårt den körande pcb, och matar den fram ett steg
 */
void remove_pcb();

/* Tar bort en specific pcb, men gör inget med den nu.
 */
void remove_pcb( pcb * removePcb );

/* initierar dom två truckterna som står längst upp
 */
void S_set_pcb_queues( pcb_queues * queue );
void S_set_free_pcb( free_pcb * queue );

#endif
