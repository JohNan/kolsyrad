#ifndef _BOOT_H
#define _BOOT_H

#include "structs.h"

void ksyscall_handler(registers_t* reg);
void syscall_putMalta(uint32_t word);
void syscall_putStr(bounded_fifo* bfifo, char* ch);
void syscall_putC(bounded_fifo* bfifo, char ch);
uint8_t syscall_getC();
char *syscall_getS();
void syscall_flush(bounded_fifo* bfifo);
void syscall_exec(pib *new);
pcb *syscall_fork();
void syscall_set_prio(pcb *who, int prio);
pcb *syscall_get_pid();
void syscall_exit();

#endif
