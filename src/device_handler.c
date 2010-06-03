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

/* IO_device(d)
 * TYPE: Device -> int
 * PRE: -
 * POST: 0 if d is already claimed by another process, 1 otherwise
 * SIDE-EFFECT: sets the owner in d if it is free when called
 */
int IO_device(Device *d){
	if((d->owner == -1) || (d->owner == getCurrent()->pid) ) {
		d->owner = getCurrent()->pid;
		return 1;
	} else {
		return 0;
	}
}

/* printPid(p)
 * TYPE: pcb& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints the pid of p to the console
 */
void printPid(pcb * p){
	char tmp[8];
	tmp[7] = '\0';
	itoa(p->pid,tmp,10);
	DputStr(tmp);
}

/* printPrio(p)
 * TYPE: pcb& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints the priority of p to the console
 */
void printPrio(pcb * p){
	char tmp[8];
	tmp[7] = '\0';
	itoa(p->priority,tmp,10);
	DputStr(tmp);
}

/* getCh
 * TYPE: void -> uint8
 * PRE: -
 * POST: the next character to be read from the console
uint8_t getCh(){
	return syscall_getC();
}


uint8_t kgetCh(){
	if(bfifoIn.length > 0){
		kget_registers()->v_reg[0] = bfifoIn.buf[bfifoIn.length-1];
	}
	return NULL;
}
*/

/* kgetStr
 * TYPE: void -> char&
 * PRE: -
 * POST: a string read from the console
 * SIDE-EFFECT: puts the current process to sleep and calls schedule()
 */
char *kgetStr(){
	pcb *current = getCurrent();
	if(ioqueue.current == NULL){
		ioqueue.current = current;
		ioqueue.last = current;
	} else {
		ioqueue.last->nextIO = current;
		ioqueue.last = current;
	}



	ksleep(-1,current);

	kget_registers()->v_reg[0] = (int)current->fifoIn.buf;

	S_schedule();
	//DputStr(getCurrent()->progid->pname);
	return NULL;
}

/* flush
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: resets the input buffer so it's ready to read a new line
 */
void flush() {
	syscall_flush(&bfifoIn);
}

/*
 * Interrupt output to tty
 * Using syscall
 */

/* putMalta(word)
 * TYPE: uint32 -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints word to the Malta LED-display
 */
void putMalta(uint32_t word){
	syscall_putMalta(word);
}

/* putMaltaStr(str)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints word to the Malta LED-display
 */
void putMaltaStr(char *str) {
  syscall_putMaltaStr(str);
}

/* putCh(ch)
 * TYPE: char -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints ch to the console
 */
void putCh(char c) {
	syscall_putC(&getCurrent()->fifoOut,c);
	if (c == '\n') {
		syscall_putC(&getCurrent()->fifoOut, '\r');
	}
}

/* putStr(str)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console
 */
void putStr(char* text) {
	syscall_putStr(&getCurrent()->fifoOut, text);
}

/*
void putStr(char* text) {
  if(d_tty.owner == -1){
 // is the tty free?
		if(IO_device(&d_tty)){
			syscall_putStr(&getCurrent()->fifoOut, text);
			d_tty.owner = -1;
		}
	} else {
		while(d_tty.owner != -1){}
		if(IO_device(&d_tty)){
			syscall_putStr(&getCurrent()->fifoOut, text);
			d_tty.owner = -1;
		}
	}
}
*/
/*
 * Debug prints.
 * Polled
 */
/* DputMalta(word)
 * TYPE: uint32 -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints word to the Malta LED-display
 */
void DputMalta(uint32_t word){
  int i;
  malta->ledbar.reg = 0xFF;
  for (i = 7; i >= 0; --i) {
    malta->asciipos[i].value = '0' + word % 10;
    word /= 10;
  }
}

/* putMaltaStr(word)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints word to the Malta LED-display
 */
void DputMaltaStr(char *str) {
  int i;
  malta->ledbar.reg = 0xFF;
  for (i = 0;i < 8; i++) {
    malta->asciipos[i].value = *str++;
  }
}

/* Polled output to tty */
/* DputCh(ch)
 * TYPE: char -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints ch to the console using polled IO
 */
void DputCh(char c) {
	while ( !tty-> lsr.thre ) {}
	tty->thr = c;
	if(c == '\n') {
		while ( !tty-> lsr.thre ) {}
		tty->thr = '\r';
	}
}

/* Outputs a string on tty, polled */
/* DputStr(str)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console using polled IO
 */
void DputStr(char* text) {
	while (*text != '\0') {
		DputCh(*text);
		++text;
	}
	DputCh('\n');
}

uint8_t prevCmd[FIFO_SIZE] = "";
/* Input(ch)
 * TYPE: char -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: adds ch to the IO buffer of the buffer of a waiting process
 *              and wakes the process if a newline is read
 */
void Input(char ch) {
	pcb *current = ioqueue.current;

	if (ioqueue.current == NULL)
		return;

	if(ch == '\n'){
		bfifo_put(&bfifoOut, '\n', 1);
		bfifo_put(&bfifoOut, '\r', 1);
		current->fifoIn.buf[current->fifoIn.length] = '\0';
	} else if(ch == '\b'){
		if(current->fifoIn.length > 0){
			bfifo_put(&bfifoOut, '\b',1);
			bfifo_put(&bfifoOut, ' ',1);
			bfifo_put(&bfifoOut, '\b',1);
			current->fifoIn.length--;
		}
	} else if(ch == '\r'){

	} else if(ch == UPARROW) {
		bfifo_putStr(&bfifoOut,prevCmd);
		strcpy(current->fifoIn.buf,prevCmd);
		current->fifoIn.length = strlen(current->fifoIn.buf);
	}
	else {
		bfifo_put(&bfifoOut, ch, 1);
		current->fifoIn.buf[current->fifoIn.length] = ch;
		current->fifoIn.buf[current->fifoIn.length+1] = '\0';
		current->fifoIn.length++;
	}

	if(ch == '\n'){

		strcpy(prevCmd,current->fifoIn.buf);

		if(ioqueue.last == current){
			ioqueue.current = NULL;
			ioqueue.last = NULL;
		} else {
			ioqueue.current = current->nextIO;
		}

		current->fifoIn.length = 0;
		kunblock(current);
		S_schedule();
	}
}


/* bfifo_put: Inserts a character at the end of the queue. */
/* bfifo_put(bf, ch, out)
 * TYPE: bounded_fifo& * uint8 * uint8 -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: stores ch in the buffer of bf and outputs one
 *              to the console if output matches the ready register
 */
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
/* bfifo_putStr(bf, str)
 * TYPE: bounded_fifo& * char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console using bf
 */
void bfifo_putStr(bounded_fifo* bfifo, char *ch) {
	  while( ch[0] != '\0' ){
		  bfifo_put( bfifo,ch[0],1);
		if( ch[0] == '\n' ) {
			bfifo_put( bfifo,'\r',1);
		}
		ch++;
	}
}

/* bfifo_get: Returns a character removed from the front of the queue. */
/* bfifo_get(bf)
 * TYPE: bounded_fifo -> uint8
 * PRE: -
 * POST: the first character available in bf
 * SIDE-EFFECT: shifts the buffer of bf
 */ 
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
/* bfifo_flush(bf)
 * TYPE: bounded_fifo& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: empties the buffer of bf
 */
void bfifo_flush(bounded_fifo* bfifo) {
	bfifo->length = 0;
	bfifo->buf[bfifo->length] = '\0';
}

/* init_devices
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: initializes all device related structs
 */
void init_devices(){

	status_reg_t and, or;
	// Set fifo-length
	bfifoOut.length = 0;
	bfifoIn.length = 0;

	// Set ioqueue to 0
	ioqueue.last = NULL;
	ioqueue.current = NULL;

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

	//DputStr("Device init done");
}
