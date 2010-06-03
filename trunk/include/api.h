#ifndef API_H
#define API_H

#include "device_handler.h"
#include "process_handler.h"
#include "other/stdlib.h"
#include "other/types.h"
#include "structs.h"

/* newP(int,int,uin32_t)
 * TYPES: int -> void
 * PRE: pibsNr must be valid pib
 * 		0 < prio < 30
 * POST: none
 * SIDE-EFFECT: A new process is created.
 */
int newP(int pibsNr, int prio, uint32_t args);

/* printN(num)
 * TYPE: int -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints num to the console
 */
void printN( int num );

/* printC(ch)
 * TYPE: char -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints ch to the console
 */
void printC( char ch );

/* printS(str)
 * TYPE: char[] -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints str to the console
 */
void printS( char * str );

/* printNln(num)
 * TYPE: int -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints num to the console followed by a newline
 */
void printNln( int num );

/* printCln(ch)
 * TYPE: char -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints ch to the console followed by a newline
 */
void printCln( char ch );

/* printSln(str)
 * TYPE: char[] -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints str to the console followed by a newline
 */
void printSln( char * str );

/* printP
 * TYPE: void -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints all processes to the console
 */
void printP();

/* sleep(ms)
 * TYPE: int -> void
 * PRE: exceptions must be initialized
 * POST: -
 * SIDE-EFFECT: puts current process to sleep for ms milliseconds
 */
void sleep( int ms );

/* block
 * TYPE: void -> void
 * PRE: exceptions must be initialized
 * POST: -
 * SIDE-EFFECT: puts current process to sleep until woken by another process
 */
void block();

/* getStr
 * TYPE: void -> char&
 * PRE: -
 * POST: a string read from the console
 * SIDE-EFFECT: puts the current process to sleep until a newline is read
 */
char *getStr();

#endif
