#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_handler.h"

void schedule();
void add_to_pcb( pcb * newProcess );

#endif
