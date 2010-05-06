#ifndef TEST_H
#define TEST_H

#include "malta.h"
#include "console.h"
#include "timer.h"
#include "types.h"

static volatile tty_t* const tty = (tty_t*) 0xb80003f8;
static volatile malta_t* const malta = (malta_t*) 0xbf000400;
static volatile rtc_t* const rtc = (rtc_t*) 0xb8000070;

typedef struct {
	short id; // Unique id of device
	short owner; // PID of owning process or -1 if device is free.
	void * buffer_address; // Pointer to static assigned buffer space or NULL if device does not have a buffer.
} Device;


void init_devices();
void putStr(const char* text);
void putCh(char c);
void putWord(uint32_t word);
void IO_device(short id, short owner, void* buffer_address);

#endif
