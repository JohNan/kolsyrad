#ifndef INIT_H
#define INIT_H

#include "other/asm.h"
#include "other/types.h"
#include "other/stdlib.h"
#include "other/debug.h"

#include "structs.h"

#include "scheduler.h"
#include "process_handler.h"
#include "device_handler.h"
#include "interrupt_handler.h"
#include "_boot.h"

/* init
 * TYPES: none -> none
 * PRE: none
 * POST: none
 * SIDE-EFFECT: It initates all modules that are needed
 */
void init();

/* ksyscall_handler( registers* reg )
 * TYPES: registers_t* -> none
 * PRE: the pointer must be a valid one
 * POST: none
 * SIDE_EFFECT: loads all register from the address reg
 */
void ksyscall_handler(registers_t* reg);
#endif
