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
int IO_device(Device, short);
void tty_interrupt();

void putCh(char c);
void putStr(char* text);
void putMalta(uint32_t word);

void bfifo_put(bounded_fifo* bfifo, char ch);
void bfifo_putStr(bounded_fifo* bfifo, char* ch);
uint8_t bfifo_get(bounded_fifo* bfifo);

void bfifo_flush(bounded_fifo* bfifo);

/*
 * Debug print functions
 * Polled
 */
void DputCh(char c);
void DputStr(char* text);
void DputMalta(uint32_t word);


#endif
