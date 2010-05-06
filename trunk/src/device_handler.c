/*
 * device_handler.c
 *
 *  Created on: 4 maj 2010
 *      Author: Johan
 */

#include "device_handler.h"

// Assignes a name to a connected devices memory allocation.

void IO_device(short id, short owner, void* buffer_address){
	Device* d;
	d->id = id;
	d->owner = owner;
	d->buffer_address = buffer_address;
}

void putWord(uint32_t word){
  int i;
  malta->ledbar.reg = 0xFF;
  for (i = 7; i >= 0; --i) {
    malta->asciipos[i].value = '0' + word % 10;
    word /= 10;
  }
}

void putCh(char c) {
  // Poll until ready to transmit.
  while ( !tty-> lsr.thre ) {}

  // Write character to Transmitter Holding Register
  tty->thr = c;
}

void putStr(const char* text) {
  while (text[0] != '\0') {
   putCh(text[0]);
    ++text;
  }
}

// Prints to stdOut and resets the buffer
void buffer_flush(void){

}

// stops a process from running
void block(void){

}
/*
// starts a stopped process
void unblock(void){

}
*/

void init_devices(){
	//Set MCR Out2 to 1 to enable interrupts on the console.
	tty->mcr.out2 = 1;

	// Set the UART word length to 8 bits.
	// Set word length to 8 bits (two least significant bits to 1),
	tty->lcr.wls0 = 1;
	tty->lcr.wls1 = 1;
}
