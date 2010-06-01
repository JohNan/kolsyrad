#include "kjell.h"
#include "stdlib.h"

#define parsing_command 0
#define parsing_args 1
#define commands_and_args 2
#define command 3

typedef struct pRet{
	char args[32];
	char com[32];
	int indexA;
	int indexC;
	int prog;
	int s;
}pRet;

pRet ret;

void parser( char * str ){
	ret.indexA = 0;
	ret.indexC = 0;

	int s = parsing_command;

	int i;
	for( i = 0; str[i] != '\n'; i++ ){
		switch( s ){
		case parsing_command:
			if( str[i] == ' ' ){
				ret.com[ret.indexC] = '\0';
				s = parsing_args;
			} else {
				ret.com[ret.indexC] = str[i];
				ret.indexC += 1;
			}
			break;
		case parsing_args:
			if( str[i] == '\r' ){
				if( ret.indexA == 0 )
					s = command;
				else{
					ret.args[ret.indexA] = '\0';
					s = commands_and_args;
				}
			} else {
				ret.args[ret.indexA] = str[i];
				ret.indexA += 1;
			}
			break;
		}
	}

	ret.s = s;
	char t[] = "increment";
	if( strcmp( ret.com, t ) == 1 )
		ret.prog = 3;
}

void kjell(){
	char *inString;
	printS("kolsyrad>");
	while(1){
		inString = getStr();
		if (strcmp(inString,"fibonacci")){
			fibonacci(6);
		}
	}
}

#undef parsing_command
#undef parsing_args
#undef commands_and_args
#undef command
