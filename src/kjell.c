#include "kjell.h"
#include "stdlib.h"

void kjell(){
	int i = 1;
	uint8_t temp;
	char *inString;
	while(1){
		temp = getCh();
		if(i){
			printS("kolsyrad>");
			i = 0;
		}

		if (strcmp(inString,"fibbonacci")){
			fibbonacci();
		}
		else{
			temp = getCh();
			if (temp == '\r' || temp == '\n'){
				instring = getStr();
				i = 1;
			}

		}
	}
}
