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

	//putStrP("Exception init done");
}

/* kexception:
 *   Application-specific exception handler, called after registers
 *   have been saved.
 */
void kexception() {
  static int i = 0;
  registers_t* reg;
  cause_reg_t cause;
  /* Make sure that we are here because of a timer interrupt. */
  cause.reg = kget_cause();

  /*
   * DEBUG
   */
  /*
  tmp = cause.field.exc;
  putWord(tmp);
  */

//  kdebug_assert(cause.field.exc == 0);    /* External interrupt */

  if (cause.field.ip & 4) { /* Hardware interrupt (tty) */
  	  tty_interrupt();
  } else if(cause.field.exc == 0){ /* Timer interrupt */
	  /* Reload timer for another 100 ms (simulated time) */
	  kload_timer(10 * timer_msec);

	  /* Icrease the number on the Malta display. */
	  kputWord(++i);
	  // device_timer();

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
