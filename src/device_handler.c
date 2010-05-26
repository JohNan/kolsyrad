/*
 * device_handler.c
 *
 *  Created on: 4 maj 2010
 *      Author: Johan
 */

#include "device_handler.h"

Device d_tty = { 1, -1, &bfifoOut };
Device d_malta = { 2, -1, NULL };


// Assignes a name to a connected devices memory allocation.

int IO_device(Device d){
	if(d.owner == -1 ) {
		d.owner = getCurrent()->pid;
		return 1;
	} else {
		return 0;
	}
}

void printPid(pcb * p){
	char tmp[8];
	tmp[7] = '\0';
	itoa(p->pid,tmp,10);
	DputStr(tmp);
}
void printPrio(pcb * p){
	char tmp[8];
	tmp[7] = '\0';
	itoa(p->priority,tmp,10);
	DputStr(tmp);
}

/*
 * Interrupt output to tty
 * Using syscall
 */

void putMalta(uint32_t word){
	syscall_putMalta(word);
}

void putCh(char c) {
	syscall_putC(&getCurrent()->fifoOut,c);
	if (c == '\n') {
		syscall_putC(&getCurrent()->fifoOut, '\r');
	}
}

void putStr(char* text) {
	if(d_tty.owner == -1){
		if(IO_device(d_tty)){
			syscall_putStr(&getCurrent()->fifoOut, text);
			d_tty.owner = -1;
		}
	} else {
		while(d_tty.owner == -1){}
		if(IO_device(d_tty)){
			syscall_putStr(&getCurrent()->fifoOut, text);
			d_tty.owner = -1;
		}
	}
}

/*
 * Debug prints.
 * Polled
 */
void DputMalta(uint32_t word){
  int i;
  malta->ledbar.reg = 0xFF;
  for (i = 7; i >= 0; --i) {
    malta->asciipos[i].value = '0' + word % 10;
    word /= 10;
  }
}

/* Polled output to tty */
void DputCh(char c) {
	while ( !tty-> lsr.thre ) {}
		tty->thr = c;
	if(c == '\n') {
		while ( !tty-> lsr.thre ) {}
				tty->thr = '\r';
	}
}

/* Outputs a string on tty, polled */
void DputStr(char* text) {
	while (text[0] != '\0') {
		DputCh(text[0]);
		++text;
	}
	DputCh('\n');
}


/* bfifo_put: Inserts a character at the end of the queue. */
void bfifo_put(bounded_fifo* bfifo, uint8_t ch, uint8_t output) {
	/* Make sure the 'bfifo' pointer is not 0. */

	kdebug_assert(bfifo != 0);

	if (bfifo->length < FIFO_SIZE) {
		bfifo->buf[(bfifo->length)++] = ch;
	}
	if (tty->lsr.thre && output) {
		/* Transmitter idle: transmit buffered character */
		tty->thr = bfifo_get(bfifo);
		/* Determine if we should be notified when transmitter becomes idle */
		tty->ier.etbei = (bfifo->length > 0);
	}
}

/* bfifo_put: Inserts a character at the end of the queue. */
void bfifo_putStr(bounded_fifo* bfifo, uint32_t c) {
	char* ch = (char*)c;
	  while( ch[0] != '\0' ){
		  bfifo_put( bfifo,ch[0],1);
		if( ch[0] == '\n' ) {
			bfifo_put( bfifo,'\r',1);
		}
		ch++;
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

  // Here bfifo->length goes nuts
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

// stops a process from running
void block(void){

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

	DputStr("Device init done");
}
