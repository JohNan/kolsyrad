/*
 * device_handler.c
 *
 *  Created on: 4 maj 2010
 *      Author: Johan
 */

#include "device_handler.h"


/* bfifo_put: Inserts a character at the end of the queue. */
void bfifo_put(struct bounded_fifo* bfifo, uint8_t ch) {
  /* Make sure the 'bfifo' pointer is not 0. */
  kdebug_assert(bfifo != 0);

  if (bfifo->length < FIFO_SIZE) {
    bfifo->buf[(bfifo->length)++] = ch;
  }
}

/* bfifo_put: Inserts a character at the end of the queue. */
void bfifo_back(struct bounded_fifo* bfifo) {
  /* Make sure the 'bfifo' pointer is not 0. */
  kdebug_assert(bfifo != 0);

  if (bfifo->length < FIFO_SIZE) {
	 bfifo->length--;
  }
}

/* bfifo_get: Returns a character removed from the front of the queue. */
uint8_t bfifo_get(struct bounded_fifo* bfifo)
{
  int i;
  uint8_t ch;

  /* Make sure the 'bfifo' pointer is not 0, and that queue is not empty. */
  kdebug_assert(bfifo != 0);
  kdebug_assert(bfifo->length > 0);

  bfifo->length--;
  ch = bfifo->buf[0];
  for (i = 0; i < bfifo->length; i++) {
    bfifo->buf[i] = bfifo->buf[i+1];
  }
  return ch;
}

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

	status_reg_t and, or;
	// Set fifo-length
	bfifo.length = 0;

	//Set MCR Out2 to 1 to enable interrupts on the console.
	tty->mcr.out2 = 1;
	tty->ier.erbfi = 1;

	// Set the UART word length to 8 bits.
	// Set word length to 8 bits (two least significant bits to 1),
	tty->lcr.wls0 = 1;
	tty->lcr.wls1 = 1;

	and.reg = 0xFFFFFFFF;
	and.field.exl = 0; // Normal level (not exception)
	and.field.erl = 0; // Error level
	and.field.um  = 0; // Kernel mode
	and.field.im  = 4; // Disable all except HW interrupt 0
	and.field.bev = 0; // Use normal exception vector (not bootsptrap)

	or.reg  = 0;
	or.field.ie   = 1;   // Enable interrupts
	or.field.im  = 4;   // Enable HW interrupt 0
	or.field.cu0  = 1;   // Coprocessor 0 usable

	kset_sr(and.reg, or.reg);
}
