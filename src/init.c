#include "init.h"

void init() {
        int i;
        //init devices.
        init_devices();

        //init exceptions
        init_exc();

        //init processes
        init_poc();

        //init scheduler
        init_scheduler(&pcbq, &free_pcb_q);

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
