#include "init.h"

void init() {
	//init devices.
	init_devices();
	putCh('A');
	putWord(7);
	putStr("loha you ol' bag of scum!");

  while (1) {};
}
