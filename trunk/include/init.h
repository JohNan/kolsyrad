#ifndef INIT_H
#define INIT_H

#include "other/asm.h"
#include "other/types.h"
#include "other/stdlib.h"

#include "device_handler.h"
#include "interrupt_handler.h"
#include "process_handler.h"
#include "scheduler.h"

void init();
/*
 * Syscalls
 */
void ksyscall_handler(registers_t* reg);
void syscall_kputStrI(char* text);

#endif