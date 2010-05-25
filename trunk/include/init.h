#ifndef INIT_H
#define INIT_H

#include "other/asm.h"
#include "other/types.h"
#include "other/stdlib.h"
#include "other/debug.h"

#include "structs/registers.h"

#include "structs.h"

#include "scheduler.h"
#include "process_handler.h"
#include "device_handler.h"
#include "interrupt_handler.h"
#include "_boot.h"

void init();
#endif
