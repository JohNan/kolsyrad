/*
 * example_timer:
 *   An example of how to setup the MIPS/Malta board
 *   to periodically increase a number on the display.
 */
#include "asm.h"
#include "malta.h"
#include "debug.h"

static registers_t regs;

/* display_word:
 *   Display a value on the Malta display.
 */
static void display_word(uint32_t word)
{
  int i;
  malta->ledbar.reg = 0xFF;
  for (i = 7; i >= 0; --i) {
    malta->asciipos[i].value = '0' + word % 10;
    word /= 10;
  }
}

/* kinit:
 *   Application-specific initialisation code, called
 *   from the boot code '_start' in 'asm.S'.
 */
void kinit()
{
  char a[] = {'H','i',' ','d','u','d','e',',',' ',
	      'w','h','a','t','\'','s',' ','u','p','?','\n', '\0'};

  /* Put '0' on the Malta display. */
  display_word(0);

  /* Setup storage-area for saving registers on exception. */
  kset_registers(&regs);

  /* Initialise timer to interrupt in 100 ms (simulated time). */
  kload_timer(100 * timer_msec);

  /* Update the status register to enable timer interrupts. */
  kset_sr(0xFFBF00E8, 0x10008001);
  
  /* Forever do nothing. */
  while(1);
}

/* kexception:
 *   Application-specific exception handler, called after registers
 *   have been saved.
 */
void kexception()
{
  static int i = 0;
  cause_reg_t cause;

  /* Make sure that we are here because of a timer interrupt. */
  cause.reg = kget_cause();
  kdebug_assert(cause.field.exc == 0);    /* External interrupt */
  kdebug_assert(cause.field.ip & 0x80);   /* Timer interrupt */

  /* Reload timer for another 100 ms (simulated time) */
  kload_timer(100 * timer_msec);

  /* Icrease the number on the Malta display. */
  display_word(++i);
}
