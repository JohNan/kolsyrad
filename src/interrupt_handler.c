#define NDEBUG

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
  cause_reg_t cause;

  /* Make sure that we are here because of a timer interrupt. */
  cause.reg = kget_cause();
  kdebug_assert(cause.field.exc == 0);    /* External interrupt */
  kdebug_assert(cause.field.ip & 0x80);   /* Timer interrupt */

  if(cause.field.ip & 4){ /* Hardware interrupt (UART) */
	 putWord(23);
  }

  /* Reload timer for another 100 ms (simulated time) */
  kload_timer(100 * timer_msec);

  /* Icrease the number on the Malta display. */
  if(cause.field.ip & 0x80){
	  putWord(++i);
  }
}
