#ifndef _BOOT_H
#define _BOOT_H

void ksyscall_handler(registers_t* reg);
void syscall_kputStrI(char* text);

#endif
