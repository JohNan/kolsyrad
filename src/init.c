#include "init.h"

/* bootscr
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints the world's coolest splash screen
 */
void bootscr(){
	DputStr("                                   ooo ");
	DputStr("                                  o   o");
	DputStr("         ooooo                    o   o");
	DputStr("        o     o                   o   o                        oooo");
	DputStr("       o       o                   ooo                        o    o ");
	DputStr("      o         o                                            o      o ");
	DputStr("      o         o                                           o        o ");
	DputStr("      o         o                                           o        o  ");
	DputStr("      o         o                            oooo           o        o  ");
	DputStr("      o         o                           o    o          o        o   ");
	DputStr("       o       o                           o      o          o      o 	");
	DputStr("        o     o          oooo              o      o           o    o ");
	DputStr("         ooooo          o    o             o      o            oooo  ");
	DputStr("                       o      o            o      o  ");
	DputStr("                      o        o            o    o ");
	DputStr("                      o        o             oooo   ");
	DputStr("                      o        o   	");
	DputStr("                      o        o 	");
	DputStr("                       o      o 	");
	DputStr("                        o    o   ");
	DputStr("     ooo                 oooo  ");
	DputStr("    o   o                              ooo   	");
	DputStr("    o   o        oooo                 o   o                   ooo   ");
	DputStr("    o   o       o    o                o   o                  o   o  ");
	DputStr("     ooo       o      o               o   o                  o   o  ");
	DputStr("               o      o                ooo                   o   o           	");
	DputStr("               o      o                                       ooo            	");
	DputStr("               o      o                       ooo                            	");
	DputStr("                o    o                       o   o                           	");
	DputStr("                 oooo                       o     o                          	");
	DputStr("                            ooo             o     o                          	");
	DputStr("                           o   o             o   o                           	");
	DputStr("                           o   o              ooo              ooo           	");
	DputStr("                           o   o                              o   o          	");
	DputStr("          ooo               ooo                               o   o          	");
	DputStr("         o   o                                                o   o          	");
	DputStr("        o     o                                                ooo           	");
	DputStr("        o     o                                                              	");
	DputStr("        o     o                                                              	");
	DputStr("         o   o                                                               	");
	DputStr("          ooo                           oo                                   	");
	DputStr("                                       o  o            oo                    	");
	DputStr("                       ooo             o  o           o  o                   	");
	DputStr("                      o   o             oo           o    o                  	");
	DputStr("                     o     o                         o    o                  	");
	DputStr("                     o     o   CARBONATED            o    o                  	");
	DputStr("                     o     o   - A bubbling OS        o  o           oo      	");
	DputStr("                      o   o                            oo           o  o     	");
	DputStr("                       ooo                                          o  o     	");
	DputStr("                                                                     oo      	");
	DputStr("                                                                             	");
	DputStr("  By: Johan Nenz�n, Per Bostr�m, Stefan Risberg, Krister Emr�n - 2010 ");
	DputStr("");
}

/* init
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: initializes all kernel subsystems
 */
void init() {
	int i;

	//init devices.
	init_devices();
	DputStr("Welcome");
	//init processes
	init_poc();

	//init scheduler
	init_scheduler();

	//init exceptions
	init_exc();

	//Starts the idle process
	//i = make_process(0,1,0);
	//Starts kjell
//	i = make_process(2,2,0);


	//Start idle process
	i = make_process(0,1,0);
	//Start kjell
	i = make_process(2,2,0);
	//Start malta scroll
	//i = make_process(1,25,0);

/*
		i = make_process(3,30,20);
		if(i != -1){
		DputStr("Forth process created.");

	}
	i = make_process(4,25,20);
		if(i != -1){
		DputStr("Fifth process created.");

		}



	char tmp[8];
	tmp[8] = '\0';

	char tmp2[8];
	tmp2[8] = '\0';


	for(i=0;i<2;i++){
		DputStr("---Process---");
		DputStr("PID: ");
		printPid(&pcbs[i]);
		DputStr("Name: ");
		DputStr(pcbs[i].progid->pname);
		DputStr("Next: ");
		printPid(pcbs[i].next);
		DputStr("Prev: ");
		printPid(pcbs[i].prev);
		DputStr("Prio: ");
		printPrio(&pcbs[i]);
		DputStr("---end---");
	}

	DputStr("---First---");
	printPid(readyQ.first);
	DputStr("---Next---");
	printPid(readyQ.first->next);
*/

	// now we just wait for an exception to occur and start scheduling

//	DputStr("Init done.");
	bootscr();
	enableTimer();

  while (1) {};
}






