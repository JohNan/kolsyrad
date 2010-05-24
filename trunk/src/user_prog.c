#include "user_prog.h"

void hello(){
	int i = 0;
	DputStr("Hello world.");
	while(i < 2000){
		//putMalta(i++);
		if(i % 1000 == 0) {
			putStr("Goodbye world.\n");
		}
		i++;
	}
	DputStr("H: Counting done.");
}

void goodbye(){
	//int i = 0;
	DputStr("Goodbye world.");
/*	while(i < 2000){
		//putMalta(i++);
		if(i % 1000 == 0) {
			putStr("Goodbye world.\n");
		}
	}*/
	DputStr("G: Counting done.");
}

void smile(){
	//int i = 0;
	DputStr("Smile.");
	/*while(i < 2000){
		//putMalta(i++);
		if(i % 1000 == 0) {
			putStr("Smile.\n");
		}
	}*/
	DputStr("S: Smile.");
}
