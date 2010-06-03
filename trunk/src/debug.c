#include "other/debug.h"

#ifndef NDEBUG
/* kdebug_putc(ch)
 * TYPE: char -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints ch to the console, using polled IO
 */
void kdebug_putc(char c)
{
  // BUSY wait for transmitter ready
  while (!tty->lsr.thre) {}

  // Transmit character
  tty->thr = c;
}

/* kdebug_print(str)
 * TYPE: char[] -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console, using polled IO
 */
void kdebug_print(const char* text)
{
  while (text[0] != '\0')
  {
    kdebug_putc(text[0]);
    if (text[0] == '\n') kdebug_putc('\r');
    ++text;
  }
}

/* kdebug_println(str)
 * TYPE: char[] -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console, followed by a newline, using polled IO
 */
void kdebug_println(const char* text)
{
  kdebug_print(text);
  kdebug_putc('\n');
  kdebug_putc('\r');
}

/* kdebug_printint(val)
 * TYPE: int -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints val to the console, using polled IO
 */
void kdebug_printint(int value)
{
  // Recursive C is not very efficient, but the recursive
  // depth is only logarithmic to the value printed so
  // it should be ok.
  if (value < 10)
  {
    kdebug_putc('0' + value);
  }
  else
  {
    kdebug_printint(value / 10);
    kdebug_putc('0' + (value % 10));
  }
}

/* kdebug_magic_break
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: halts the CPU
 */
void kdebug_magic_break();

/* kdebug_assert_at(ass, file, line)
 * TYPE: int * char[] * int -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: if ass is true, does nothing, otherwise it prints an error
 *              message and halts the CPU
 */
void kdebug_assert_at(int assertion, const char* file, int line)
{
  if (!assertion)
  {
    kdebug_print("DEBUG: assertion failed at line ");
    kdebug_printint(line);
    kdebug_print(" in file '");
    kdebug_print(file);
    kdebug_println("'.");

    /* Stop simulation, if 'magic-break-enable'. */
    kdebug_magic_break();

    while (1)
    {
      // Do nothing, its the only safe bet when the kernel has crashed.
    }
  }
}
#endif
