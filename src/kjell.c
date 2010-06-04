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

/* parser(str)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: parses str and takes appropriate action
 */
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
	ret.com[ret.indexC] = '\0';
	ret.args[ret.indexA] = '\0';

	ret.s = s;

	if( strcmp( ret.com, "malta_scroll" ) ){
		newP( 1, 25, NULL );
	} else if( strcmp( ret.com, "kjell") ){
		printC( '\n' );
		newP( 2, 2, NULL );
	} else if( strcmp( ret.com, "increment" ) ){
		if(ret.indexA != NULL) {
			newP( 3, 15, atoi( ret.args ) );
		} else {
			printS("Need a number. Try again.\n");
		}
	} else if(strcmp(ret.com, "prio") ){
		printN( getPriority( atoi( ret.args ) ) );
		printC( '\n' );
	} else if( strcmp( ret.com, "fibonacci" ) ){
		if(ret.indexA != NULL) {
			newP( 4, 15, atoi( ret.args ) );
		} else {
			printS("Need a number. Try again.\n");
		}
	} else if( strcmp( ret.com, "ps" ) ){
		ps();
	} else if( strcmp(ret.com, "idle" ) ){
		newP( 0, 1, NULL );
	} else if( strcmp(ret.com, "kill" ) ){
		if(ret.indexA != NULL) {
			kill( atoi( ret.args ) );
		} else {
			printS("Need a PID. Try again.\n");
		}
	} else if( strcmp( ret.com, "state" ) ){
		printN( getState( atoi( ret.args ) ) );
		printC( '\n' );
	} else if( strcmp( ret.com, "name" ) ){
		char * na = getName( atoi( ret.args ) );
		if( na == NULL ){
			printS( "Not found" );
		} else {
			printS( na );
		}
		printC( '\n' );
	} else if( strcmp( ret.com, "setPrio" ) ){
		set_priority( atoi( ret.args ), 10 );
		printS( "changed the priority of pid: " );
		printS( ret.com );
		printS( " to 10!\n" );
	} else {
		printS( "	Error: Command not recognized\n" );
	}
}

/* kjell
 * TYPE: void -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: runs a loop that prints a prompt and then parses whatever the
 *              user enters
 */
void kjell(){
	char *inString;
	while(1){
		printS("kolsyrad>");
		inString = getStr();
		parser(inString);
	}
}

#undef parsing_command
#undef parsing_args
#undef commands_and_args
#undef command
