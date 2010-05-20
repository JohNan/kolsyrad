#ifndef _BOOT_H
#define _BOOT_H

#include "structs.h"

void ksyscall_handler(registers_t* reg);
void syscall_putStr(bounded_fifo* bfifo, uint32_t ch);

#endif
