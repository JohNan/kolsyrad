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
void newP(int pibsNr, int prio, uint32_t args);

/* printN( num )
 * TYPES: int -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: prints num to the terminal and doesn't
 * 				add new line after
 */
void printN( int num );

/* printC( ch )
 * TYPES: char -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: prints ch to the terminal and doesn't
 * 				add new line after
 */
void printC( char ch );

/* printS( str )
 * TYPE: char * -> void
 * PRE: the str has to end whit an \0
 * POST: none
 * SIDE-EFFECT: prints str to the terminal and doesn't
 * 				add new line  after
 */
void printS( char * str );

/* printNln( num )
 * TYPE: int -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: prints num to terminal and adds a new line
 * 				at end.
 */
void printNln( int num );

/* printCln( ch )
 * TYPE: char -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: prints ch to terminal and adds a new line
 * 				at end.
 */
void printCln( char ch );

/* printSln( str )
 * TYPE: char * -> void
 * PRE: str have to end whit \0.
 * POST: none
 * SIDE-EFFECT: prints str to terminal and adds a new line
 * 				at end.
 */
void printSln( char * str );

/* printP
 * TYPES: void -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: prints all processes that are running or waiting
 */
void printP();

/* sleep( ms )
 * TYPES: int -> void
 * PRE: ms > 0
 * POST: none
 * SIDE-EFFECT: puts the current process to sleep for ms milliseconds
 */
void sleep( int ms );

/* wait()
 * TYPES: void -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: puts the current process to wait until another reactivates it
 */
void wait();

#endif
