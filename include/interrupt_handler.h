#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "asm.h"
#include "debug.h"
#include "mips4kc.h"
#include "device_handler.h"
#include "scheduler.h"

/*
 * Init the exception handler
 */
void init_exc();
void kexception();

#endif
