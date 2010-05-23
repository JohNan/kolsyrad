#include "init.h"

extern Device d_tty;

void init() {
	int i;
	//init devices.
	init_devices();


	char tmp[8];
	tmp[8] = '\0';

	init_poc();

	i = make_process(1,25);
	if(i != -1){
		DputStr("First process created.");
		itoa(i,tmp,10);
		DputStr(tmp);
	}
	i = make_process(0,25);
	if(i != -1){
		DputStr("Second process created.");
		itoa(i,tmp,10);
		DputStr(tmp);

	}
	// now we just wait for an exception to occur and start scheduling

	DputStr("Init done.");
	//putStrP("Init done.");

	//init exceptions
	init_exc();

  while (1) {};
}
