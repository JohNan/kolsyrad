#ifndef TEST_H
#define TEST_H

#include "other/debug.h"
#include "other/types.h"

#include "structs/mips4kc.h"
#include "structs/malta.h"
#include "structs/console.h"

static volatile tty_t* const tty = (tty_t*) 0xb80003f8;
static volatile malta_t* const malta = (malta_t*) 0xbf000400;

#define FIFO_SIZE 32

typedef struct {
	short id; // Unique id of device
	short owner; // PID of owning process or -1 if device is free.
	void * buffer_address; // Pointer to static assigned buffer space or NULL if device does not have a buffer.
} Device;

/* A simple FIFO queue of bounded size. */
typedef struct {
  uint8_t  buf[FIFO_SIZE];
  uint32_t length;
} bounded_fifo;

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

void DputChI(char c);
void Dbfifo_put(bounded_fifo* bfifo, uint8_t ch);
uint8_t Dbfifo_get(bounded_fifo* bfifo);

#endif
