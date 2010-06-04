#ifndef _BOOT_H
#define _BOOT_H

#include "structs.h"

void ksyscall_handler(registers_t* reg);
void syscall_putMalta(uint32_t word);
void syscall_putMaltaStr(char *str);
void syscall_putStr(bounded_fifo* bfifo, char* ch);
void syscall_putC(bounded_fifo* bfifo, char ch);
char *syscall_getS();
int syscall_newp(int pibsNr, int prio, uint32_t args);
pcb *syscall_fork();
void syscall_set_prio( int pid, uint8_t p );
pcb *syscall_get_pid();
void syscall_exit();
void syscall_kill(int pid);
void syscall_sleep(int ms, uint8_t p);
void syscall_block(int32_t ms, uint8_t p);
void syscall_unblock( uint8_t p );
void syscall_ps();

uint8_t syscall_getPriority(uint8_t p);
uint8_t syscall_getState(uint8_t p);
char *syscall_getName(uint8_t p);

#endif
