#include "init.h"
static registers_t regs;

void init() {
	//init devices.
	init_devices();

	kset_registers(&regs);

	//init exceptions
	init_exc();

	//init processes
	init_poc();

	//init scheduler
	init_scheduler(&pcbq, &free_pcb_q, &regs);

	/*
	 * Skit
	 */
	make_process(0,25);
	// now we just wait for an exception to occur and start scheduling

	DputStr("Init done.");
	//putStrP("Init done.");

	enableTimer();

  while (1) {};
}
