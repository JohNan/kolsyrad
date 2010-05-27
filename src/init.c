#include "init.h"

void init() {
	int i;
	//init devices.
	init_devices();

	//init processes
	init_poc();

	//init scheduler
	init_scheduler(&pcbq, &free_pcb_q);

	//init exceptions
	init_exc();

	/*	i = make_process(0,1,0);
	if(i != -1){
		DputStr("First process created.");
		}*/
	i = make_process(1,25,0);
	if(i != -1){
		DputStr("Second process created.");
		}
	/*i = make_process(2,25,0);
		if(i != -1){
		DputStr("Third process created.");

	}
		
		/*i = make_process(3,30,20);
		if(i != -1){
		DputStr("Forth process created.");

	}
	i = make_process(4,25,20);
		if(i != -1){
		DputStr("Fifth process created.");

		}*/

/*

	char tmp[8];
	tmp[8] = '\0';

	char tmp2[8];
	tmp2[8] = '\0';


	for(i=0;i<5;i++){
		DputStr("---Process---");
		DputStr("PID: ");
		printPid(&pcbs[i]);
		DputStr("Next: ");
		printPid(pcbs[i].next);
		DputStr("Prev: ");
		printPid(pcbs[i].prev);
		DputStr("Prio: ");
		printPrio(&pcbs[i]);
		DputStr("---end---");
	}

	DputStr("---First ready---");
	printPid(pcbq.first_ready);
	DputStr("---Ready---");
	printPid(pcbq.ready);
*/
	// now we just wait for an exception to occur and start scheduling

	DputStr("Init done.");

	enableTimer();

  while (1) {};
}
