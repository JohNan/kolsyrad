#include "api.h"

void kill(int pid){
	syscall_kill(pid);
}

int newP(int pibsNr, int prio, uint32_t args){
	return syscall_newp(pibsNr, prio, args);
}


void printN( int num ){
	char temp[12];
	itoa( num, temp, 10 );

	putStr( temp );
}

void printC( char ch ){
	putCh( ch );
}

char *getStr(){
	return syscall_getS();
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
	pcb *temp = list_queue( 1 );

	if( temp != NULL ){
		printS( "Active processes" );
		printS( "----------------\n" );
		printS( "PID      Pname      Priority      State\n" );
		printN( temp->pid );
		printS( "      ");
		printS( "\t" );
		printS( temp->progid->pname );
		printS( "      ");
		printS( "\t" );
		printN( temp->priority );
		printS( "      ");
		printS( "\t" );
		printN( temp->state );
		printS( "\n");

		for( temp=temp->next; temp != list_queue( 1 ); temp=temp->next ){

			printN( temp->pid );
			printS( "      ");
			printS( "\t" );
			printS( temp->progid->pname );
			printS( "      ");
			printS( "\t" );
			printN( temp->priority );
			printS( "      ");
			printS( "\t" );
			printN( temp->state );
			printS( "\n");
		}

		printS( "-----------------------" );
		printS( "End of active processes\n" );
	}
	temp = list_queue( 2 );

	if( temp != NULL ){
		printS( "Waiting processes\n" );
		printS( "----------------\n" );
		printS( "PID      Pname      Priority      State\n" );
		printN( temp->pid );
		printS( "      ");
		printS( "\t" );
		printS( temp->progid->pname );
		printS( "      ");
		printS( "\t" );
		printN( temp->priority );
		printS( "      ");
		printS( "\t" );
		printN( temp->state );
		printS( "\n");

		for( temp=temp->next; temp != list_queue( 2 ); temp=temp->next ){
			printN( temp->pid );
			printS( "      ");
			printS( "\t" );
			printS( temp->progid->pname );
			printS( "      ");
			printS( "\t" );
			printN( temp->priority );
			printS( "      ");
			printS( "\t" );
			printN( temp->state );
			printS( "\n");
		}
		printS( "\n------------------------" );
		printS( "End of waiting processes" );
	}
}

void sleep( int ms ){
	//TODO: Add syscall
	ksleep( ms, getCurrent() );
}

void block(){
	//TODO: Add syscall
	ksleep( -1, getCurrent() );
}
