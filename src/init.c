#include "init.h"

extern Device d_tty;

void init() {
	int i;
	//init devices.
	init_devices();


	char tmp[8];
	tmp[8] = '\0';

	char tmp2[8];
	tmp2[8] = '\0';

	init_poc();
	init_scheduler(&pcbq, &free_pcb_q);

	i = make_process(0,25);
	if(i != -1){
		DputStr("First process created.");
	}
/*	i = make_process(1,25);
	if(i != -1){
		DputStr("Second process created.");
	}
	i = make_process(2,25);
		if(i != -1){
		DputStr("Third process created.");

	}

	for(i=0;i<3;i++){
		DputStr("---Process---");
		DputStr("PID: ");
		itoa(pcbs[i].pid,tmp,10);
		DputStr(tmp);
		DputStr("Next: ");
		itoa(pcbs[i].next->pid,tmp2,10);
		DputStr(tmp2);
		DputStr("Prev: ");
		itoa(pcbs[i].prev->pid,tmp,10);
		DputStr(tmp);
		DputStr("---end---");
	}
*/

	// now we just wait for an exception to occur and start scheduling

	DputStr("Init done.");
	//putStrP("Init done.");

	//init exceptions
	init_exc();

  while (1) {};
}
