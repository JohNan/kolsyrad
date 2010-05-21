#include "user_prog.h"

void hello(){
	static int i = 0;
	DputStr("Hello world.");
	while(i < 10000){
		putMalta(i++);
	}
	DputStr("H: Counting done.");
}

void goodbye(){
	static int i = 0;
	DputStr("Goodbye world.");
	while(i < 10000){
		putMalta(i++);
	}
	DputStr("G: Counting done.");
}
