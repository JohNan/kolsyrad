#include "init.h"

extern Device d_tty;

void init() {
	pcb *ini;
	init_poc();

/*	char tmp[8];
	tmp[8] = '\0';
	//itoa(pibs[0].start_ptr,tmp,10);
	itoa(0x008c2001,tmp,10);
	putStrI(tmp);
*/
	ini = pcbs;
	ini->progid = pibs[0].progid;
	ini->state = PS_READY;
	ini->registers.epc_reg = pibs[0].start_ptr;
	ini->registers.ra_reg = (int)&exit;
	S_add_new_pcb(ini);

	//init devices.
	init_devices();

	//init exceptions
	init_exc();


	// now we just wait for an exception to occur and start scheduling


	putStrI("Init done.");

  while (1) {};
}
