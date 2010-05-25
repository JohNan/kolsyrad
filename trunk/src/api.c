#include "api.h"

void new_p( int pibsNr, int prio ){
	/*
	 * TODO: Move to process handle to filter.
	 */
	syscall_newp(pibsNr, prio);
}

void printN( int num ){
	char temp[12];
	itoa( num, temp, 10 );

	putStr( temp );
}

void printC( char ch ){
	putCh( ch );
}

void printS( char * str ){
	putStr( str );
}

void printNln( int num ){
	char temp[13];
	itoa( num, temp, 10 );
	printSln( temp );
}

void printCln( char ch ){
	putCh( ch );
	putCh( '\n' );
}
void printSln( char * str ){
	int i;
	char *temp = str;
	for( i = 0; str[i] != '\0'; i++ ){

	}
	temp[i+1] = '\0';
	temp[i] = '\n';

	putStr( temp );
}

void printP(){
	pcb * temp = list_queue( 1 );

	if( temp != NULL ){
		printSln( "Active processes" );
		printSln( "----------------" );
		printN( temp->pid );
		printS( "\t" );
		printN( temp->progid );
		printS( "\t" );
		printN( temp->priority );
		printS( "\t" );
		printNln( temp->state );

		for( temp++; temp != list_queue( 1 ); temp++ ){
			printN( temp->pid );
			printS( "\t" );
			printN( temp->progid );
			printS( "\t" );
			printN( temp->priority );
			printS( "\t" );
			printCln( temp->state );
		}

		printSln( "-----------------------" );
		printSln( "End of active processes\n" );
	}
	temp = list_queue( 2 );

	if( temp != NULL ){
		printSln( "Waiting processes" );
		printSln( "-----------------" );
		printN( temp->pid );
		printS( "\t" );
		printN( temp->progid );
		printS( "\t" );
		printN( temp->priority );
		printS( "\t" );
		printNln( temp->state );

		for( temp++; temp != list_queue( 1 ); temp++ ){
			printN( temp->pid );
			printS( "\t" );
			printN( temp->progid );
			printS( "\t" );
			printN( temp->priority );
			printS( "\t" );
			printNln( temp->state );
		}
		printSln( "------------------------" );
		printSln( "End of waiting processes" );
	}
}
