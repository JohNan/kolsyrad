#ifndef TEST_H
#define TEST_H

#include <malta.h>
#include <console.h>

typedef struct {
	short id; // Unique id of device
	short owner; // PID of owning process or -1 if device is free.
	void * buffer_address; // Pointer to static assigned buffer space or NULL if device does not have a buffer.
}device;

#endif
