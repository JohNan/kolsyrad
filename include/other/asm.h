
#ifndef ASM_H
#define ASM_H

#include "other/types.h"

#include "structs/registers.h"

/* Timer 67MHz (?) */
static const int timer_usec = 67;
static const int timer_msec = 67000;

/* Functions provided by '_boot.S' */
uint32_t kset_sr(uint32_t and_mask, uint32_t or_mask);
uint32_t kget_sr();
uint32_t kset_cause(uint32_t and_mask, uint32_t or_mask);
uint32_t kget_cause();
void kload_timer(uint32_t timer_value);
void kset_registers(registers_t* regs);
registers_t* kget_registers();
void kdebug_magic_break();

#endif
