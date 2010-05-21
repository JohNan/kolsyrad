#include "init.h"

extern Device d_tty;

void init() {
	pcb *ini, *ini2;

	//init devices.
	init_devices();


/*	char tmp[8];
	tmp[8] = '\0';
	//itoa(pibs[0].start_ptr,tmp,10);
	itoa(0x008c2001,tmp,10);
	putStrI(tmp);
*/
	init_poc();

	ini = make_process(1,25);
	DputCh((char)ini->pid);

	ini2 = make_process(0,25);
	DputCh((char)ini->pid);

	// now we just wait for an exception to occur and start scheduling

	DputStr("Init done.");
	//putStrP("Init done.");

	//init exceptions
	init_exc();

  while (1) {};
}
