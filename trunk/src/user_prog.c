#include "user_prog.h"

void hello(){
	//int i = 0;
	//putCh('P');
	DputStr( "Det FUNKAR!!!" );
}

void kjell(){
	while(1){
		putStr("�kolsyrad > ");
	}

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
// increments i and prints it to a new line.
// pre max > 0

void increment(int max){
	int i;
	for (i = 0; i < max; i++){
		printCln(i);
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
		nAux = n;
		m = n + m;
		n = nAux;
	  }
	  return n;
	}

int fibonacci(int input)
{
	int n;
	for(n=0; n<input; n++) printCln(fibonacci_aux(input));
	return 0;
}


