#ifndef TEST_H
#define TEST_H

#include "other/asm.h"
#include "other/debug.h"
#include "other/types.h"

#include "structs/mips4kc.h"
#include "structs/malta.h"
#include "structs/console.h"

#include "structs.h"
#include "_boot.h"

static volatile tty_t* const tty = (tty_t*) 0xb80003f8;
static volatile malta_t* const malta = (malta_t*) 0xbf000400;

void init_devices();
void putStrP(char* text);

void putChP(char c);
void putChI(char c);
void putWord(uint32_t word);
int IO_device(Device, short);
void tty_interrupt();

void bfifo_put(bounded_fifo* bfifo, uint8_t ch);
uint8_t bfifo_get(bounded_fifo* bfifo);
void bfifo_flush(bounded_fifo* bfifo);

/*
 * Debug print functions
 */

void putStrI(char* text);
void kputStrI(char* text);

void bfifo_putStr(bounded_fifo* bfifo, char* ch);

void DputChI(char c);
void Dbfifo_put(bounded_fifo* bfifo, uint8_t ch);
uint8_t Dbfifo_get(bounded_fifo* bfifo);

#endif
