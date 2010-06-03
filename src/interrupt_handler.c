#include "interrupt_handler.h"
static registers_t regs;

/* enableTimer
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: starts the timer interrupt
 */
void enableTimer(){
        /* Initialise timer to interrupt in 100 ms (simulated time). */
        kload_timer(100 * timer_msec);

        //DputStr("Interrupt enabled.");
}

/* init_exc
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: initialized the exception handler
 */
void init_exc() {
	status_reg_t and, or;
	/* Setup storage-area for saving registers on exception. */
	kset_registers(&regs);

	/* Update the status register to enable timer interrupts. */
	//kset_sr(0xFFBF00E8, 0x10008001);

	and.reg = 0xFFFFFFFF;
	and.field.exl = 0; // Normal level (not exception)
	and.field.erl = 0; // Error level
	and.field.um  = 0; // Kernel mode
	//and.field.im  = 8; // Disable all except HW interrupt 0
	and.field.bev = 0; // Use normal exception vector (not bootsptrap)

	or.reg  = 0;
	or.field.ie   = 1;   // Enable interrupts
	or.field.im   = 128;   // Enable Timer interrupt
	or.field.cu0  = 1;   // Coprocessor 0 usable

	kset_sr(and.reg, or.reg);

	//putStrP("Exception init done");
}

/* kexception:
 *   Application-specific exception handler, called after registers
 *   have been saved.
 */
/* kexception
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: handles an exception
 */
void kexception() {

  registers_t* reg;
  cause_reg_t cause;
  pcb *p;
  /* Make sure that we are here because of a timer interrupt. */
  cause.reg = kget_cause();

  /*
   * DEBUG
   */
  /*
  tmp = cause.field.exc;
  putWord(tmp);
  */

  //kdebug_assert(cause.field.exc == 0);    /* External interrupt */

  if (cause.field.ip & 4) { /* Hardware interrupt (tty) */
	  uint8_t ch;
	   /* UART interrupt */
	  	  if (tty->lsr.dr) {
	  		/* Data ready: add character to buffer */
	  		ch = tty->thr; /* rbr and thr is the same. */

	  		Input(ch);


	  		/* Should be moved to shell program */
	  		if (ch == '\r') {
	  				Input('\n');
	  		}

	  		if (ch == '\b') {
	  				bfifo_put(&bfifoOut, ' ',1);
	  				bfifo_put(&bfifoOut, '\b',1);
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
  } else if(cause.field.exc == 0){ /* Timer interrupt */
    //DputStr("Tick!");

	/* count down all sleepers */
    if(waitingQ.first != NULL){
		p = waitingQ.first;
		while(p != waitingQ.first->prev) {
			if(p->time > 0 ) {
				//DputStr("Tock!");
				p->time--;
				if( p->time == 0) {
					pcb *q = p;
					p = q->next;
					removePcb(&waitingQ, q);
					insertPcb(&readyQ, q);
					S_schedule();
				}
				else {
					p = p->next;
				}
			} else {
				p = p->next;
			}
		}
    }
	  /* Icrease the number on the Malta display. */
	  // DputMalta(++i);

    //DputStr("Schedule!");
	  /* lets schedule! */
	  S_schedule();

  } else if(cause.field.exc == 8) { /* Syscall exception */
	  /* Get pointer to stored registers. */
	  reg = kget_registers();

	  /* Handle the system call (see syscall.S). */
	  ksyscall_handler(reg);

	  /* Return from exception to instruction following syscall. */
	  reg->epc_reg += 4;

	  /* Acknowledge syscall exception. */
	  kset_cause(~0x60, 0);
  }

}
