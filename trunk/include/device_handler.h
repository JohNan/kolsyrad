#ifndef TEST_H
#define TEST_H

#include "malta.h"
#include "console.h"
#include "timer.h"
#include "types.h"
#include "debug.h"
#include "mips4kc.h"

static volatile tty_t* const tty = (tty_t*) 0xb80003f8;
static volatile malta_t* const malta = (malta_t*) 0xbf000400;
static volatile rtc_t* const rtc = (rtc_t*) 0xb8000070;

#define FIFO_SIZE 8

typedef struct {
	short id; // Unique id of device
	short owner; // PID of owning process or -1 if device is free.
	void * buffer_address; // Pointer to static assigned buffer space or NULL if device does not have a buffer.
} Device;

/* A simple FIFO queue of bounded size. */
struct bounded_fifo {
  uint8_t  buf[FIFO_SIZE];
  uint32_t length;
} bfifo;

void init_devices();
void putStr(const char* text);
void putCh(char c);
void putWord(uint32_t word);
void IO_device(short id, short owner, void* buffer_address);

void bfifo_put(struct bounded_fifo* bfifo, uint8_t ch);
uint8_t bfifo_get(struct bounded_fifo* bfifo);
void bfifo_back(struct bounded_fifo* bfifo);

#endif
