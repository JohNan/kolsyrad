/*
 * device_handler.c
 *
 *  Created on: 4 maj 2010
 *      Author: Johan
 */

#include "device_handler.h"

static volatile tty_t* const tty = (tty_t*) 0xb80003f8;
static volatile malta_t* const malta = (malta_t*) 0xbf000000;

// Assignes a name to a connected devices memory allocation.
/*
void IO_device(short id, short owner, void* buffer_address){
	device->id = id;
	device->owner = owner;
	device->buffer_address = buffer_address;
}
*/
// Prints to stdOut and resets the buffer
void buffer_flush(void){

}

// stops a process from running
void block(void){

}

// starts a stopped process
void unblock(void){

}
