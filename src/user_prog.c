#include "user_prog.h"

/* idle
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: loops forever
 */
void idle(){
	//putStr("Idle process started\n");
	while(1){
		__asm( "nop" );
	}
}

/* mscroll
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: scrolls the text "MALTA!" on the Malta LED display
 */
void mscroll() {
  int i;
  char *str = "MALTA!  ", c;

  while(1) {
    putMaltaStr(str);
    c = *str;
    for(i = 0;i < 7;i++)
      str[i] = str[i+1];
    str[7] = c;
    sleep(10);
  }
}

/* goodbye
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints "Goodbye world" 90 times and then exits
 */
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

/* smile
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: prints all current processes
 */
void smile(){
	printP();
}
// increments i and prints it to a new line.
// pre max > 0

/* increment(max)
 * TYPE: int -> void
 * PRE: max > 0
 * POST: -
 * SIDE-EFFECT: prints all integers from 0 to (max-1)
 */
void increment(int max){
	int i;
	for (i = 0; i < max; i++){
		printNln(i);
	}
}
//prints the fibonacci serie from 0 to the given number.
//pre input > 0;
/* fibonacci_aux(i)
 * TYPE: int -> int
 * PRE: i > 0
 * POST: the ith fibonacci number
 */
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

/* fibonacci(i)
 * TYPE: int -> void
 * PRE: i > 0
 * POST: -
 * SIDE-EFFECT: prints all fibonacci numbers between 0 and (i-1)
 */
void fibonacci(int input) {
	int n;

	for(n=0; n<input; n++) {
		printNln(fibonacci_aux(n));
	}
}


