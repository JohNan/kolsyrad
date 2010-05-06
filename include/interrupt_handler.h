#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "asm.h"
#include "debug.h"
#include "mips4kc.h"

/*
 * Init the exception handler
 */
void init_exc();

/*
 * kexception is called when an exception occurs, after registers
 * have been saved. Use 'kget_registers' to access the saved
 * registers, and 'kset_registers' to update the entire register
 * set when 'kexception' returns (useful for task switching).
 */
void kexception();

#endif
