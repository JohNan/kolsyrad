#include "interrupt_handler.h"

static registers_t regs;

void init_exc() {
	status_reg_t and, or;
	/* Setup storage-area for saving registers on exception. */
	kset_registers(&regs);

	/* Initialise timer to interrupt in 100 ms (simulated time). */
	kload_timer(100 * timer_msec);

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

  /* Timer interrupt */
  if(cause.field.ip & 0x80){
	  /* Reload timer for another 100 ms (simulated time) */
	  kload_timer(10 * timer_msec);

	  /* Icrease the number on the Malta display. */
	  putWord(++i);
	 // device_timer();

	  /* lets schedule! */
	  S_schedule();
  }

  /* Hardware interrupt (tty) */
  else if (cause.field.ip & 4) {
	  tty_interrupt();
  }

}
