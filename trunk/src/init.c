#include "init.h"
#include "process_handler.h"

void init() {
	pcb *ini;

	//init devices.
	init_devices();

	//init exceptions
	init_exc();

	init_poc();

	ini = pcbs;
	ini.pib = pibs;
	ini.state = PS_READY;
	pcbq.first_ready = pcbq.ready = ini;
	kset_registers(&ini.registers);
	free_pcb_q.first = ini->next;

	// now we just wait for an exception to occur and start scheduling



//	putCh('A');
	putWord(7);
//	putStr("loha you ol' bag of scum!");

  while (1) {};
}
