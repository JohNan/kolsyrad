#include "api.h"

void print( int num ){
	char temp[12];
	itoa( num, temp, 10 );

	putStr( temp );
}

void print( char ch ){
	putCh( ch );
}

void print( char * str ){
	putStr( str );
}

void println( int num ){
	char temp[13];
	itoa( num, temp, 10 );
	println( temp );
}

void println( char ch ){
	putCh( ch );
	putCh( '\n' );
}
void println( char * str ){
	int i;
	for( i = 0; str[i] != '\0'; i++ ){

	}
	temp[i+1] = '\0';
	temp[i] = '\n';

	putStr( temp );
}

void printP(){
	pcb * temp = list_queue( 1 );

	if( temp != NULL ){
		println( "Active processes" );
		println( "----------------" );
		print( temp->pid );
		print( "\t" );
		print( temp->progid );
		print( "\t" );
		print( temp->priority );
		print( "\t" );
		println( temp->state );

		for( temp++; temp != list_queue( 1 ); temp++ ){
			print( temp->pid );
			print( "\t" );
			print( temp->progid );
			print( "\t" );
			print( temp->priority );
			print( "\t" );
			println( temp->state );
		}

		println( "-----------------------" );
		println( "End of active processes\n" );
	}
	temp = list_queue( 2 );

	if( temp != NULL ){
		println( "Waiting processes" );
		println( "-----------------" );
		print( temp->pid );
		print( "\t" );
		print( temp->progid );
		print( "\t" );
		print( temp->priority );
		print( "\t" );
		println( temp->state );

		for( temp++; temp != list_queue( 1 ); temp++ ){
			print( temp->pid );
			print( "\t" );
			print( temp->progid );
			print( "\t" );
			print( temp->priority );
			print( "\t" );
			println( temp->state );
		}
		println( "------------------------" );
		println( "End of waiting processes" );
	}
}
