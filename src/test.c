#include <test.h>
#include <malta.h>

static volatile tty_t* const tty = (tty_t*) 0xb80003f8;
static volatile malta_t* const malta = (malta_t*) 0xbf000000;

void tty_putc(char c) {
  // Poll until ready to transmit.
  while ( !tty-> lsr.thre ) {}		

  // Write character to Transmitter Holding Register
  tty->thr = c;	    
}

void tty_print_string(const char* text) {
  while (text[0] != '\0') {
    tty_putc(text[0]);
    ++text;
  }
}

static void display_word(uint32_t word)
{
  int i;
  malta->ledbar.reg = 0xFF;
  for (i = 7; i >= 0; --i) {
    malta->asciipos[i].value = '0' + word % 10;
    word /= 10;
  }
}

void tty_test() {
  tty_putc('A');
  malta->asciiword = 'a';
  malta->ledbar.field.led3 = 1;
  malta->ledbar.field.led7 = 0;
  malta->ledbar.field.led2 = 1;
	display_word(0);
  tty_print_string("loha you ol' bag of scum!\n");
  tty_print_string("Aloha you ol' bag of scum!");

  while (1) {};
}
