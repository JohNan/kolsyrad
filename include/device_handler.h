#ifndef TEST_H
#define TEST_H

#include "other/asm.h"
#include "other/debug.h"
#include "other/types.h"
#include "other/stdlib.h"

#include "structs/mips4kc.h"
#include "structs/malta.h"
#include "structs/console.h"

#include "scheduler.h"
#include "structs.h"
#include "_boot.h"

#define RIGHTARROW 0x43
#define LEFTARROW 0x44
#define UPARROW 0x41
#define DOWNARROW 0x42

#define ESCAPE 0x1b
#define SKIP 0x5b

static volatile tty_t* const tty = (tty_t*) 0xb80003f8;
static volatile malta_t* const malta = (malta_t*) 0xbf000400;

/* printPid(p)
 * TYPE: pcb& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints the pid of p to the console
 */
void printPid(pcb * p);

/* printPrio(p)
 * TYPE: pcb& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints the priority of p to the console
 */
void printPrio(pcb * p);

/* init_devices
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: initializes all device related structs
 */
void init_devices();

/* IO_device(d)
 * TYPE: Device -> int
 * PRE: -
 * POST: 0 if d is already claimed by another process, 1 otherwise
 * SIDE-EFFECT: sets the owner in d if it is free when called
 */
int IO_device(Device *);

char *getStr();

/* kgetStr
 * TYPE: void -> char&
 * PRE: -
 * POST: a string read from the console
 * SIDE-EFFECT: puts the current process to sleep and calls schedule()
 */
char *kgetStr();

/* flush
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: resets the input buffer so it's ready to read a new line
 */
void flush();

/* putCh(ch)
 * TYPE: char -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints ch to the console
 */
void putCh(char c);

/* putStr(str)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console
 */
void putStr(char* text);

/* putMalta(word)
 * TYPE: uint32 -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints word to the Malta LED-display
 */
void putMalta(uint32_t word);

/* putMaltaStr(str)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints word to the Malta LED-display
 */
void putMaltaStr(char *str);

/* Input(ch)
 * TYPE: char -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: adds ch to the IO buffer of the buffer of a waiting process
 *              and wakes the process if a newline is read
 */
void Input(char ch);

/* bfifo_put: Inserts a character at the end of the queue. */
/* bfifo_put(bf, ch, out)
 * TYPE: bounded_fifo& * uint8 * uint8 -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: stores ch in the buffer of bf and outputs one
 *              to the console if output matches the ready register
 */
void bfifo_put(bounded_fifo* bfifo, uint8_t ch, uint8_t output);

/* bfifo_put: Inserts a character at the end of the queue. */
/* bfifo_putStr(bf, str)
 * TYPE: bounded_fifo& * char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console using bf
 */
void bfifo_putStr(bounded_fifo* bfifo, char *ch);

/* bfifo_get: Returns a character removed from the front of the queue. */
/* bfifo_get(bf)
 * TYPE: bounded_fifo -> uint8
 * PRE: -
 * POST: the first character available in bf
 * SIDE-EFFECT: shifts the buffer of bf
 */
uint8_t bfifo_get(bounded_fifo* bfifo);

/* bfifo_flush(bf)
 * TYPE: bounded_fifo& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: empties the buffer of bf
 */
void bfifo_flush(bounded_fifo* bfifo);

/*
 * Debug print functions
 * Polled
 */

/* Polled output to tty */
/* DputCh(ch)
 * TYPE: char -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints ch to the console using polled IO
 */
void DputCh(char c);

/* Outputs a string on tty, polled */
/* DputStr(str)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints str to the console using polled IO
 */
void DputStr(char* text);

/* Outputs a int on tty, polled */
/* DputN(num)
 * TYPE: int -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints num to the console using polled IO
 */
void DputN(int num);
/* DputMalta(word)
 * TYPE: uint32 -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints word to the Malta LED-display
 */
void DputMalta(uint32_t word);

/* putMaltaStr(word)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints word to the Malta LED-display
 */
void DputMaltaStr(char *str);

#endif
