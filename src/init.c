#include "init.h"

extern Device d_tty;

void init() {
	pcb *ini, *ini2;


	//init devices.
	init_devices();

	//init exceptions
	init_exc();


/*	char tmp[8];
	tmp[8] = '\0';
	//itoa(pibs[0].start_ptr,tmp,10);
	itoa(0x008c2001,tmp,10);
	putStrI(tmp);
*/
	init_poc();

	ini = pcbs[0];
	ini->progid = pibs[0].progid;
	ini->state = PS_READY;
	ini->registers.epc_reg = pibs[0].start_ptr;
	ini->registers.ra_reg = (int)&exit;
	S_add_new_pcb(ini);

	ini2 = pcbs[1];
	ini2->progid = pibs[1].progid;
	ini2->state = PS_READY;
	ini2->registers.epc_reg = pibs[1].start_ptr;
	ini2->registers.ra_reg = (int)&exit;
	S_add_new_pcb(ini2);


	// now we just wait for an exception to occur and start scheduling

	kputStrI("Init done.");
	//putStrP("Init done.");

  while (1) {};
}
