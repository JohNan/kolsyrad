#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "other/asm.h"
#include "other/debug.h"
#include "other/mips4kc.h"

#include "init.h"
#include "device_handler.h"
#include "scheduler.h"
#include "process_handler.h"

/*
 * Init the exception handler
 */
void init_exc();
void kexception();

#endif
