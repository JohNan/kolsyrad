/*
 * device_handler.c
 *
 *  Created on: 4 maj 2010
 *      Author: Johan
 */

#include "device_handler.h"

bounded_fifo bfifoOut;
bounded_fifo bfifoDebug;

Device d_tty = { .id = 1, .owner = -1, .buffer_address = &bfifoOut };
Device d_malta = { .id = 2, .owner = -1, .buffer_address = NULL };


// Assignes a name to a connected devices memory allocation.

int IO_device(Device d, short pid){
	if(d.owner == -1 ) {
		d.owner = pid;
		return 1;
	} else {
		return 0;
	}
}

void kputWord(uint32_t word){
  int i;
  malta->ledbar.reg = 0xFF;
  for (i = 7; i >= 0; --i) {
    malta->asciipos[i].value = '0' + word % 10;
    word /= 10;
  }
}

void putWord(uint32_t word){
	syscall_putWord(word);
}

/* Polled output to tty */
void putChP(char c) {
  // Poll until ready to transmit.
  while ( !tty-> lsr.thre ) {}
  // Write character to Transmitter Holding Register
  tty->thr = c;
}

/* Interrupt output to tty
 * TODO: Add syscall functionality
 */
void putChI(char c) {
	bfifo_put(&bfifoOut,c);
	if (c == '\n') {
		bfifo_put(&bfifoOut, '\r');
	}
}

/* Outputs a string on tty, polled */
void putStrP(char* text) {
  while (text[0] != '\0') {
   putChP(text[0]);
    ++text;
  }
}

/* Outputs a string on tty, interrupt */
void kputStrI(char* text) {
  while (text[0] != '\0') {
	  bfifo_put(&bfifoOut, text[0]);
    ++text;
  }
  putChI('\n');
}

void putStrI(char* text) {
	syscall_putStrI(text);
}

/* bfifo_put: Inserts a character at the end of the queue. */
void bfifo_put(bounded_fifo* bfifo, uint8_t ch) {
  /* Make sure the 'bfifo' pointer is not 0. */
  kdebug_assert(bfifo != 0);

  if (bfifo->length < FIFO_SIZE) {
    bfifo->buf[(bfifo->length)++] = ch;
  }
  if (tty->lsr.thre) {
  		/* Transmitter idle: transmit buffered character */
  		tty->thr = bfifo_get(bfifo);

  		/* Determine if we should be notified when transmitter becomes idle */
  		tty->ier.etbei = (bfifo->length > 0);
  	 }
}

/* bfifo_put: Inserts a character at the end of the queue. */
void bfifo_putStr(bounded_fifo* bfifo, uint32_t ch) {
	char *c = (char*)ch;
	while (c[0] != '\0') {
		bfifo_put(bfifo, c[0]);
	}
}

/* bfifo_get: Returns a character removed from the front of the queue. */
uint8_t bfifo_get(bounded_fifo* bfifo) {
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


//Resets the buffer
void bfifo_flush(bounded_fifo* bfifo)
{
  int i;

  /* Make sure the 'bfifo' pointer is not 0, and that queue is not empty. */
  kdebug_assert(bfifo != 0);
  kdebug_assert(bfifo->length > 0);

  if (bfifo->length > 0) {

  for (i = 0; i < bfifo->length; i++) {
	  if (bfifo->length > 0 && tty->lsr.thre) {
		  tty->thr = bfifo->buf[i];

		  tty->ier.etbei = (bfifo->length > 0);
	  }
  }
  bfifo->length = 0;

  }
}


/*
 * Looks for a command in buffer
 */
void tty_command(bounded_fifo* bfifo){

}

// stops a process from running
void block(void){

}
/*
// starts a stopped process
void unblock(void){

}
*/

/*
 * tty interrupt code.
 */
void tty_interrupt(){
	uint8_t ch;
 /* UART interrupt */
	  if (tty->lsr.dr) {
		/* Data ready: add character to buffer */
		ch = tty->thr; /* rbr and thr is the same. */
		bfifo_put(&bfifoOut, ch);

		/* Should be moved to shell program */
		if (ch == '\r') {
				bfifo_put(&bfifoOut, '\n');
		}

		if (ch == '\b') {
				bfifo_put(&bfifoOut, ' ');
				bfifo_put(&bfifoOut, '\b');
		}


	  }

	  if (bfifoOut.length > 0 && tty->lsr.thre) {
		/* Transmitter idle: transmit buffered character */
		tty->thr = bfifo_get(&bfifoOut);

		/* Determine if we should be notified when transmitter becomes idle */
		tty->ier.etbei = (bfifoOut.length > 0);
	  }
	  /* Acknowledge UART interrupt. */
	  kset_cause(~0x1000, 0);
}

void init_devices(){

	status_reg_t and, or;
	// Set fifo-length
	bfifoOut.length = 0;

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

	//putStrP("Device init done");
}
