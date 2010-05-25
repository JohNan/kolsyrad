#ifndef _BOOT_H
#define _BOOT_H

#include "structs.h"

void ksyscall_handler(registers_t* reg);
void syscall_putMalta(uint32_t word);
void syscall_putStr(bounded_fifo* bfifo, char* ch);
void syscall_putC(bounded_fifo* bfifo, char ch);
void syscall_newp(int pibsNr, int prio);
void syscall_exit();

#endif
