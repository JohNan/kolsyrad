#include "user_prog.h"
#include "other/types.h"

void kjell(){
	int i = 1;
	uint8_t temp;
	while(1){
		if (i){
			printS("kolsyrad>");
			i = 0;
		}
		else{
			if (getCh == '\n'){
				i = 1;
			}
		}

	}



}
