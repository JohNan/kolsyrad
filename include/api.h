#ifndef API_H
#define API_H

#include "device_handler.h"
#include "process_handler.h"
#include "other/stdlib.h"
#include "other/types.h"
#include "structs.h"

/* setPrio( pid, prio )
 * TYPES: int, int -> void
 * PRE: pid has to be valid.
 * POST: none
 * SIDE-EFFECT: changes pids prio
 */
void setPrio( int pid, int prio );

/* kill( pid )
 * TYPES: int -> void
 * PRE: pid has to be a valid one
 * POST: none
 * SIDE-EFFECT: kills the pid
 */
void kill(int pid);

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

/* ps
 * TYPE: void -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints all processes to the console
 */
void ps();

/* sleep(ms)
 * TYPE: int -> void
 * PRE: exceptions must be initialized
 * POST: -
 * SIDE-EFFECT: puts current process to sleep for ms milliseconds
 */
void sleep( int ms );
/* sleep_pid( p, ms )
 * PRE: none
 * POST: none
 * SIDE-EFFECT: puts process with pid p to sleep ms milliseconds
 */
void sleep_pid( uint8_t p, int ms );

/* block
 * TYPE: void -> void
 * PRE: exceptions must be initialized
 * POST: -
 * SIDE-EFFECT: puts current process to sleep until woken by another process
 */
void block();

/* block_pid( p )
 * TYPE: uint8_t -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: blocks a process whit pid p
 */
void block_pid( uint8_t p );

/* unblock( pid )
 * TYPE: uint8_t -> null
 * PRE: none
 * POST: none
 * SIDE-EFFECTS: unblocks a blocked process.
 */
void unblock( uint8_t p );

/* getStr
 * TYPE: void -> char&
 * PRE: -
 * POST: a string read from the console
 * SIDE-EFFECT: puts the current process to sleep until a newline is read
 */
char *getStr();

/* getPriority
 * TYPE:
 * POST: -
 * SIDE-EFFECTS: returns the priority of process p.
 */
uint8_t getPriority(uint8_t p);

/* getState
 * TYPE
 * POST:
 * SIDE-EFFECTS: Returns the current state of the process with pid p
 */
uint8_t getState(uint8_t p);

/*getName
 * TYPE:
 * POST:
 * SIDE-EFFECTS: Returns the name of the program using the process
 */

char *getName(uint8_t p);

/*set_priority
 * TYPE: int, uint8_t -> void
 * PRE: none
 * POST: none
 * SIDE-EFFECT: changes the priority of a pib
 */
void set_priority( int pib, uint8_t p );

#endif
