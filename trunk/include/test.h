typedef unsigned char uint8_t;
typedef unsigned char uint8_m;
typedef unsigned int   uint32_m;


typedef struct {
  uint8_t thr; /* 0x00: Transmitter Holding Register */
  uint8_t iir; /* 0x01: Interrupt Identity Register */
  uint8_t fcr; /* 0x02: FIFO Control  Register */
  uint8_t lcr; /* 0x03: Line Control  Register */
  uint8_t mcr; /* 0x04: Modem Control  Register */
  
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

/* Display driver for 8 digit LED on Malta board       */
/* (See pages 14-16 of the Malta board's User's Guide) */
typedef struct
{
  uint8_t pad1[8];

  /* LEDBAR: 8 bits, 1 = LED on */
  union {
    uint8_t reg;
    struct {
      uint8_t led0 : 1;
      uint8_t led1 : 1;
      uint8_t led2 : 1;
      uint8_t led3 : 1;
      uint8_t led4 : 1;
      uint8_t led5 : 1;
      uint8_t led6 : 1;
      uint8_t led7 : 1;
    } field;
  } ledbar;
  uint8_t pad2[7];

  /* ASCIIWORD: Value written here will be displayed in hex */
  uint32_t asciiword;
  uint8_t  pad3[4];

  /* ASCIIPOSn : ASCII value for LED position 'n'. */
  struct {
      uint8_t value;
      uint8_t pad[7];
  } asciipos[8];
} malta_t;


