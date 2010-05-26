#include "kjell.h"

void kjell(){
	int i = 1;
	uint8_t temp;
	while(1){
		temp = getCh();
		if(i){
			printS("kolsyrad>");
			i = 0;
		}
		if (temp == '\n'){
			i = 1;
		} else if(temp == 'a') {
			putStr("Du skrev ett A");
		}
	}
}
