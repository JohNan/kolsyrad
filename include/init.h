#ifndef INIT_H
#define INIT_H

#include "device_handler.h"
#include "interrupt_handler.h"
#include "_boot.h"

void init();
/*
 * Syscalls
 */
void ksyscall_handler(registers_t* reg);
#endif
