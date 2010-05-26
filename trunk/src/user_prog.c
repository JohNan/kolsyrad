#include "user_prog.h"

void idle(){
	putStr("Idle process started\n");
	while(1){}
}



void goodbye(){
	int i = 0;
	putStr("Goodbye world.\n");
	while(i < 90000){
		//putMalta(i++);
		if(i % 1000 == 0) {
			putStr("Goodbye world.\n");
		}
		i++;
	}
	putStr("G: Counting done.\n");
}

void smile(){
	//int i = 0;
	putStr("Smile.\n");
	/*while(i < 2000){
		//putMalta(i++);
		if(i % 1000 == 0) {
			putStr("Smile.\n");
		}
	}*/
	putStr("S: Smile.\n");
}
// increments i and prints it to a new line.
// pre max > 0

void increment(int max){
	int i;
	for (i = 0; i < max; i++){
		printNln(i);
	}
}
//prints the fibonacci serie from 0 to the given number.
//pre input > 0;
int fibonacci_aux(int input){
	  int n = 0;
	  int m = 1;
	  int nAux;
	  int i;
	  if (input==0)
		return 0;
	  for (i=0; i < input-1; i++) {
		nAux = m;
		m = n + m;
		n = nAux;
	  }
	  return m;
}

void fibonacci(int input)
{
	int n;

	for(n=0; n<input; n++) {
		printNln(fibonacci_aux(n));
	}



