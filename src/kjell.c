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
	for( i = 0; str[i] != '\0'; i++ ){
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
			if( str[i] == '\0' ){
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
	/*if( strcmp( ret.com, "increment" ) == 1 )
		newp( 3, 25, atoi(ret.args) );
	else if( strcmp( ret.com, ""))*/
	if( strcmp( ret.com, "malta_scroll" ) ){
		newP( 1, 15, NULL );
	} else if( strcmp( ret.com, "kjell") ){
		newP( 2, 2, NULL );
	} else if( strcmp( ret.com, "increment" ) ){
		newP( 3, 15, atoi( ret.args ) );
	} else if( strcmp( ret.com, "fibonacci" ) ){
		newP( 4, 15, atoi( ret.args ) );
	} else {
		printS( "Jo fäjld bastärd!");
	}
}


void kjell(){
	char *inString;
	while(1){
		printS("kolsyrad>");
		inString = getStr();
		parser(inString);
	/*	if (strcmp(inString,"fibonacci")){
			fibonacci(6);
		} */
	}
}

#undef parsing_command
#undef parsing_args
#undef commands_and_args
#undef command
