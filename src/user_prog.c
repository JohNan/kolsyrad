#include "user_prog.h"

void hello(){
	static int i = 0;
	putStr("Hello world.");
	while(i < 2000){
		//putMalta(i++);
		if(i % 600 == 0) {
			putStr("Hello world.\n");
		}
	}
	putStr("H: Counting done.");
}

void goodbye(){
	static int i = 0;
	putStr("Goodbye world.");
	while(i < 2000){
		//putMalta(i++);
		if(i % 600 == 0) {
			putStr("Goodbye world.\n");
		}
	}
	putStr("G: Counting done.");
}
