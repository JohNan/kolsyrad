#ifndef CONSOLE_H
#define CONSOLE_H

#include "other/types.h"

typedef struct {
  uint8_t thr; /* 0x00: Transmitter Holding Register */

  /* 0x01: Interrupt Enable Register */
  struct {
		uint8_t erbfi   : 1;  /* Enable Received Data Aviable Interrupt	*/
		uint8_t etbei   : 1;
		uint8_t elsi   : 1;
		uint8_t edssi   : 1;
  } ier;

  uint8_t fcr; /* 0x02: FIFO Control  Register */

  /* 0x03: Line Control  Register */

  struct {
       uint8_t wls0   : 1;  /* bit 0: Word Length Select Bit 0	*/
       uint8_t wls1   : 1;  /* bit 1: Word Length Select Bit 1	*/
       uint8_t stb   : 1;  /* bit 2: Number of Stop Bits	*/
       uint8_t pen   : 1;  /* bit 3: Parity Enable	*/
       uint8_t eps   : 1;  /* bit 4: Even Parity Select	*/
       uint8_t sp : 1;  /* bit 5: Stick Parity */
       uint8_t sb : 1;  /* bit 6: Set Break            */
       uint8_t dlab : 1;  /* bit 7: Divisor Latch Access Bit            */
     } lcr;

  /* 0x04: Modem Control  Register */

  struct {
     uint8_t dtr   : 1;  /* bit 0: Data Terminal Ready	*/
     uint8_t rts   : 1;  /* bit 1: Request to send	*/
     uint8_t out1   : 1;  /* bit 2:	*/
     uint8_t out2   : 1;  /* bit 3: Set to one to enable interrupts	*/
     uint8_t loop   : 1;  /* bit 4:	*/
   } mcr;
  
  /*  0x05: Line Status Register */
  
  struct {
    uint8_t dr   : 1;  /* bit 0: Data Ready                   */
    uint8_t oe   : 1;  /* bit 1: Overrun Error                */
    uint8_t pe   : 1;  /* bit 2: Parity Error                 */
    uint8_t fe   : 1;  /* bit 3: Framing Error                */
    uint8_t bi   : 1;  /* bit 4: Break Interrupt              */
    uint8_t thre : 1;  /* bit 5: Transmitter Holding Register */
    uint8_t temt : 1;  /* bit 6: Transmitter Empty            */
  } lsr;
  
} tty_t;

#endif
