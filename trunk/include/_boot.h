#ifndef _BOOT_H
#define _BOOT_H

#include "structs.h"

void ksyscall_handler(registers_t* reg);
void syscall_putWord(uint32_t word);
void syscall_putStrI(char* text);

#endif
