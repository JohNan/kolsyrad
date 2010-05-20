#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "other/asm.h"
#include "other/debug.h"

#include "structs/mips4kc.h"

#include "device_handler.h"

/*
 * Init the exception handler
 */
void init_exc();
void kexception();

#endif
