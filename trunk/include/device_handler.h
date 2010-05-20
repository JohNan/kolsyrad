#ifndef TEST_H
#define TEST_H

#include "asm.h"
#include "malta.h"
#include "console.h"
#include "timer.h"
#include "types.h"
#include "debug.h"
#include "mips4kc.h"


static volatile tty_t* const tty = (tty_t*) 0xb80003f8;
static volatile malta_t* const malta = (malta_t*) 0xbf000400;
static volatile rtc_t* const rtc = (rtc_t*) 0xb8000070;

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
void putStrP(const char* text);
void putStrI(const char* text);
void putChP(char c);
void putChI(char c);
void putWord(uint32_t word);
int IO_device(Device, short);
void tty_interrupt();

void bfifo_put(bounded_fifo* bfifo, uint8_t ch);
uint8_t bfifo_get(bounded_fifo* bfifo);
void bfifo_flush(bounded_fifo* bfifo);

/*
 * Syscalls
 */
void kputStrI(const char* text);

/*
 * Debug print functions
 */
void DputChI(char c);
void Dbfifo_put(bounded_fifo* bfifo, uint8_t ch);
uint8_t Dbfifo_get(bounded_fifo* bfifo);

#endif
