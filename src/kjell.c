#include "kjell.h"
#include "stdlib.h"

#define parsing_command 0
#define parsing_arg1 1
#define parsing_arg2 2
#define commands_and_args 3
#define command 4

typedef struct pRet{
	char arg1[32];
	char arg2[32];
	char com[32];
	int indexA1;
	int indexA2;
	int indexC;
	int prog;
}pRet;

pRet ret;

/* parser(str)
 * TYPE: char& -> void
 * PRE: -
 * POST: -
 * SIDE-EFFECT: parses str and takes appropriate action
 */
void parser( char * str ){
	ret.indexA1 = 0;
	ret.indexA2 = 0;
	ret.indexC = 0;

	int s = parsing_command;

	int i;
	for( i = 0; str[i] != '\0'; i++ ){
		switch( s ){
		case parsing_command:
			if( str[i] == ' ' ){
				ret.com[ret.indexC] = '\0';
				s = parsing_arg1;
			} else {
				ret.com[ret.indexC] = str[i];
				ret.indexC += 1;
			}
			break;
		case parsing_arg1:
			if( str[i] == ' ' ){
				ret.arg1[ret.indexA1] = '\0';
				s = parsing_arg2;
			} else {
				ret.arg1[ret.indexA1] = str[i];
				ret.indexA1 += 1;
			}
			break;
		case parsing_arg2:
			ret.arg2[ret.indexA2] = str[i];
			ret.indexA2 += 1;
			break;
		}
	}
	ret.com[ret.indexC] = '\0';
	ret.arg2[ret.indexA2] = '\0';

	if( strcmp( ret.com, "malta_scroll" ) ){
		newP( 1, 25, NULL );
	} else if( strcmp( ret.com, "kjell") ){
		printS( "\n" );
		newP( 2, 2, NULL );
	} else if( strcmp( ret.com, "increment" ) ){
		if(ret.indexA1 != 0) {
			newP( 3, 15, atoi( ret.arg1 ) );
		} else {
			printS("Need a number. Try again.\n");
		}
	} else if(strcmp(ret.com, "prio") ){
		printN( getPriority( atoi( ret.arg1 ) ) );
		printC( '\n' );
	} else if( strcmp( ret.com, "fibonacci" ) ){
		if(ret.indexA1 != 0) {
			newP( 4, 15, atoi( ret.arg1 ) );
		} else {
			printS("Need a number. Try again.\n");
		}
	} else if( strcmp( ret.com, "ps" ) ){
		ps();
	} else if( strcmp(ret.com, "idle" ) ){
		newP( 0, 1, NULL );
	} else if( strcmp(ret.com, "kill" ) ){
		if(ret.indexA1 != 0) {
			kill( atoi( ret.arg1 ) );
		} else {
			printS("Need a PID. Try again.\n");
		}
	} else if( strcmp( ret.com, "state" ) ){
		printN( getState( atoi( ret.arg1 ) ) );
		printS( "\n" );
	} else if( strcmp( ret.com, "name" ) ){
		char * na = getName( atoi( ret.arg1 ) );
		if( na == NULL ){
			printS( "Not found" );
		} else {
			printS( na );
		}
		printS( "\n" );
	} else if( strcmp( ret.com, "setPrio" ) ){
		set_priority( atoi( ret.arg1 ), atoi( ret.arg2 ) );
		printS( "changed the priority of pid: " );
		printS( ret.arg1 );
		printS( " to " );
		printS( ret.arg2 );
		printS( ".\n" );
	} else if( strcmp( ret.com, "block" ) ){
		block_pid( atoi( ret.arg1 ) );
		printS( "Blocked pid:" );
		printS( ret.arg1 );
		printS( "\n" );
	} else if( strcmp( ret.com, "sleep" ) ){
		sleep_pid( atoi( ret.arg1 ), atoi( ret.arg2 ) );
		printS( ret.arg1 );
		printS( " was put to sleep... for " );
		printS( ret.arg2 );
		printS( " ms.\n" );
	} else if( strcmp( ret.com, "wake" ) ){
		unblock( atoi( ret.arg1 ) );
		printS( ret.arg1 );
		printS( " was unblocked.\n" );
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
