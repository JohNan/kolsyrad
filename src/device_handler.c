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

int IO_device(Device *d){
	if((d->owner == -1) || (d->owner == getCurrent()->pid) ) {
		d->owner = getCurrent()->pid;
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

char *kgetStr(){
	pcb *current = getCurrent();
	if(ioqueue.current == NULL){
		ioqueue.current = current;
		ioqueue.last = current;
	} else {
		ioqueue.last->nextIO = current;
		ioqueue.last = current;
	}

	ksleep(-1,current->pid);

	kget_registers()->v_reg[0] = (int)current->fifoIn.buf;

	S_schedule();

	return NULL;
}

/*
 * Interrupt output to tty
 * Using syscall
 */

void putMalta(uint32_t word){
	syscall_putMalta(word);
}

void putMaltaStr(char *str) {
  syscall_putMaltaStr(str);
}

void putCh(char c) {
	syscall_putC(&getCurrent()->fifoOut,c);
	if (c == '\n') {
		syscall_putC(&getCurrent()->fifoOut, '\r');
	}
}


void putStr(char* text) {
	syscall_putStr(&getCurrent()->fifoOut, text);
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

void DputMaltaStr(char *str) {
  int i;
  //malta->ledbar.reg = 0xFF;
  for (i = 0;i < 8; i++) {
    malta->asciipos[i].value = str[i];
  }
}

void DputCh(char c) {
	while ( !tty-> lsr.thre ) {}
	tty->thr = c;
	if(c == '\n') {
		while ( !tty-> lsr.thre ) {}
		tty->thr = '\r';
	}
}

void DputStr(char* text) {
	while (*text != '\0') {
		DputCh(*text);
		++text;
	}
}

void DputN(int num) {
	char temp[13];
	itoa( num, temp, 10 );
	DputStr(temp);
}

uint8_t prevCmd[FIFO_SIZE] = "";

void Input(char ch) {
	pcb *current = ioqueue.current;

	if (ioqueue.current == NULL)
		return;
    static char escape1 = 0;
     static char escape2 = 0;
     static char escape3 = 0;
     //static char lastCommand[200] = "";

     // We got an escape char
     if (ch == ESCAPE) {
     //      putslnDebug("c=escape");
             escape1 = ch;
     }
     else if (escape1 == ESCAPE) {
             //putslnDebug("escape1=escape");
             // We have escape char stored
             if (escape2 == SKIP) {
                     // We have an escape key stored (e.g. an arrow)
                     escape3 = ch;
             }
             else if (ch == SKIP) {
                     // We have the second sign of an escape sequence
                     escape2 = ch;
             }
     }
     else if (escape3 == 0) {
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
		} else if(ch == '\r' || ch == '\t'){

		} else {
			bfifo_put(&bfifoOut, ch, 1);
			current->fifoIn.buf[current->fifoIn.length] = ch;
			current->fifoIn.buf[current->fifoIn.length+1] = '\0';
			current->fifoIn.length++;
		}
     }

     if (escape3 != 0) {
			if(ch == UPARROW && prevCmd[0] != '\0') {
     			bfifo_putStr(&bfifoOut,prevCmd);
     			strcpy(current->fifoIn.buf,prevCmd);
     			current->fifoIn.length = strlen(current->fifoIn.buf);
     		}

    	 escape1 = 0;
    	 escape2 = 0;
    	 escape3 = 0;
     }

	if(ch == '\n'){

		strcpy(prevCmd,current->fifoIn.buf);

		if(ioqueue.last == current){
			ioqueue.current = NULL;
			ioqueue.last = NULL;
		} else {
			ioqueue.current = current->nextIO;
		}

		current->fifoIn.buf[current->fifoIn.length] = '\0';
		current->fifoIn.length = 0;

		kunblock(current->pid);
		S_schedule();
	}
}

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

void bfifo_putStr(bounded_fifo* bfifo, char *ch) {
	while( ch[0] != '\0' ){
		bfifo_put( bfifo,ch[0],1);
		if( ch[0] == '\n' ) {
			bfifo_put( bfifo,'\r',1);
		}
		ch++;
	}
}

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
