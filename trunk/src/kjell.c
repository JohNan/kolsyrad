#include "kjell.h"

void kjell(){
	int i = 1;
	uint8_t temp;
	while(1){
		if (i){
			printS("kolsyrad>");
			i = 0;
		}
		else{
			temp = getCh();
			if (temp == '\r' || temp == '\n'){
				i = 1;
			}
		}

	}



}
