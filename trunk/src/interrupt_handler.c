#include "interrupt_handler.h"

static registers_t regs;

void init_exc() {

	  /* Setup storage-area for saving registers on exception. */
	  kset_registers(&regs);

	  /* Initialise timer to interrupt in 100 ms (simulated time). */
	  kload_timer(100 * timer_msec);

	  /* Update the status register to enable timer interrupts. */
	  kset_sr(0xFFBF00E8, 0x10008001);
}

/* kexception:
 *   Application-specific exception handler, called after registers
 *   have been saved.
 */
void kexception() {
  static int i = 0;
  uint8_t ch;
  cause_reg_t cause;

  /* Make sure that we are here because of a timer interrupt. */
  cause.reg = kget_cause();
  kdebug_assert(cause.field.exc == 0);    /* External interrupt */

  /* Timer interrupt */
  if(cause.field.exc == 0){
	  /* Reload timer for another 100 ms (simulated time) */
	  kload_timer(100 * timer_msec);

	  /* Icrease the number on the Malta display. */
	  putWord(++i);
  }

  /* Hardware interrupt (tty) */
  if (cause.field.ip & 4) {
      /* UART interrupt */
      if (tty->lsr.dr) {
        /* Data ready: add character to buffer */
        ch = tty->thr; /* rbr and thr is the same. */
        bfifo_put(&bfifo, ch);
        if (ch == '\r') {
			bfifo_put(&bfifo, '\n');
        }
      }
      if (bfifo.length > 0 && tty->lsr.thre) {
        /* Transmitter idle: transmit buffered character */
        tty->thr = bfifo_get(&bfifo);

        /* Determine if we should be notified when transmitter becomes idle */
        tty->ier.etbei = (bfifo.length > 0);
      }
      /* Acknowledge UART interrupt. */
      kset_cause(~0x1000, 0);
    }
}
