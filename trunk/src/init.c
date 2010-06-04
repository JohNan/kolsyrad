#include "init.h"

/* bootscr
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints the world's coolest splash screen
 */
void bootscr(){
	DputStr("                                   ooo \n");
	DputStr("                                  o   o\n");
	DputStr("         ooooo                    o   o\n");
	DputStr("        o     o                   o   o                        oooo\n");
	DputStr("       o       o                   ooo                        o    o\n");
	DputStr("      o         o                                            o      o\n");
	DputStr("      o         o                                           o        o\n");
	DputStr("      o         o                                           o        o\n");
	DputStr("      o         o                            oooo           o        o\n");
	DputStr("      o         o                           o    o          o        o\n");
	DputStr("       o       o                           o      o          o      o\n");
	DputStr("        o     o          oooo              o      o           o    o\n");
	DputStr("         ooooo          o    o             o      o            oooo\n");
	DputStr("                       o      o            o      o\n");
	DputStr("                      o        o            o    o\n");
	DputStr("                      o        o             oooo\n");
	DputStr("                      o        o\n");
	DputStr("                      o        o\n");
	DputStr("                       o      o\n");
	DputStr("                        o    o\n");
	DputStr("     ooo                 oooo\n");
	DputStr("    o   o                              ooo\n");
	DputStr("    o   o        oooo                 o   o                   ooo\n");
	DputStr("    o   o       o    o                o   o                  o   o\n");
	DputStr("     ooo       o      o               o   o                  o   o\n");
	DputStr("               o      o                ooo                   o   o\n");
	DputStr("               o      o                                       ooo\n");
	DputStr("               o      o                       ooo\n");
	DputStr("                o    o                       o   o\n");
	DputStr("                 oooo                       o     o\n");
	DputStr("                            ooo             o     o\n");
	DputStr("                           o   o             o   o\n");
	DputStr("                           o   o              ooo              ooo\n");
	DputStr("                           o   o                              o   o\n");
	DputStr("          ooo               ooo                               o   o\n");
	DputStr("         o   o                                                o   o\n");
	DputStr("        o     o                                                ooo\n");
	DputStr("        o     o\n");
	DputStr("        o     o\n");
	DputStr("         o   o\n");
	DputStr("          ooo                           oo\n");
	DputStr("                                       o  o            oo\n");
	DputStr("                       ooo             o  o           o  o\n");
	DputStr("                      o   o             oo           o    o\n");
	DputStr("                     o     o                         o    o\n");
	DputStr("                     o     o   CARBONATED            o    o\n");
	DputStr("                     o     o   - A bubbling OS        o  o           oo\n");
	DputStr("                      o   o                            oo           o  o\n");
	DputStr("                       ooo                                          o  o\n");
	DputStr("                                                                     oo\n");
	DputStr("\n");
	DputStr("  By: Johan Nenzén, Per Boström, Stefan Risberg, Krister Emrén - 2010\n");
	DputStr("\n");
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

	//Start idle process
	i = make_process(0,1,NULL);
	//Start kjell
	i = make_process(2,2,NULL);
	//Start malta
	i = make_process(1,25,NULL);

	bootscr();
	enableTimer();

  while (1) {};
}






