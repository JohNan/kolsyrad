#include "init.h"
#include "process_handler.h"

extern Device d_tty;

void init() {

	//init devices.
	init_devices();

	//init exceptions
	init_exc();

	pcb *ini;
	init_poc();

	ini = pcbs;
	ini->progid = pibs[0].progid;
	ini->state = PS_READY;
	pcbq.first_ready = pcbq.ready = ini;
	kset_registers(&ini->registers);
	free_pcb_q.first = ini->next;

	// now we just wait for an exception to occur and start scheduling


	if(IO_device(d_tty,234)){
		putStrI("Device successfully locked to PID 234");
	}

  while (1) {};
}
