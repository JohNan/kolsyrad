#ifndef DEBUG_H
#define DEBUG_H

#include "device_handler.h"

/* Only for debug purposes:
 * Your OS should work when NDEBUG is defined.
 */

#ifdef NDEBUG
#define kdebug_putc(n)
#define kdebug_print(n)
#define kdebug_println(n)
#define kdebug_printint(n)
#define kdebug_assert(n)

#else

/* kdebug_putc(ch)
 * TYPE: char -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints ch to the console, using polled IO
 */
void kdebug_putc(char c);´

/* kdebug_print(str)
 * TYPE: char[] -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console, using polled IO
 */
void kdebug_print(const char* text);

/* kdebug_println(str)
 * TYPE: char[] -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console, followed by a newline, using polled IO
 */
void kdebug_println(const char* text);

/* kdebug_printint(val)
 * TYPE: int -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints val to the console, using polled IO
 */
void kdebug_printint(int value);

/* kdebug_assert_at(ass, file, line)
 * TYPE: int * char[] * int -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: if ass is true, does nothing, otherwise it prints an error
 *              message and halts the CPU
 */
void kdebug_assert_at(int assertion, const char* file, int line);
#define kdebug_assert(a) kdebug_assert_at(a,__FILE__,__LINE__)
#endif

#endif
