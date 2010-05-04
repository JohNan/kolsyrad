#ifndef DEVICE_HANDLER_H
#define DEVICE_HANDLER_H

#include <types.h>


typedef struct {

	short id; //unique id of device
	short owner; //PID of owning process or -1 if device is free.
	void * buffer_address; //pointer to static assigned buffer space or NULL if device does not have a buffer.

} device;




#endif
