#include "api.h"

/* newP(pibNr, prio, args)
 * TYPE: int * int * uint32_t -> void
 * PRE: exceptions must be enabled
 * POST: -
 * SIDE-EFFECT: starts a new process, running the program identified by pibNr,
 *              with priority prio and argument args
 */
void newP(int pibsNr, int prio, uint32_t args){
	syscall_newp(pibsNr, prio, args);
}

/* printN(num)
 * TYPE: int -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints num to the console
 */
void printN( int num ){
	char temp[12];
	itoa( num, temp, 10 );

	putStr( temp );
}

/* printC(ch)
 * TYPE: char -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints ch to the console
 */
void printC( char ch ){
	putCh( ch );
}

/* getStr
 * TYPE: void -> char&
 * PRE: -
 * POST: a string read from the console
 * SIDE-EFFECT: puts the current process to sleep until a newline is read
 */
char *getStr(){
	return syscall_getS();
}

/* printS(str)
 * TYPE: char[] -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints str to the console
 */
void printS( char * str ){
	putStr( str );
}

/* printNln(num)
 * TYPE: int -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints num to the console followed by a newline
 */
void printNln( int num ){
	char temp[13];
	itoa( num, temp, 10 );
	printSln( temp );
}

/* printCln(ch)
 * TYPE: char -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints ch to the console followed by a newline
 */
void printCln( char ch ){
	putCh( ch );
	putCh( '\n' );
}

/* printSln(str)
 * TYPE: char[] -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints str to the console followed by a newline
 */
void printSln( char * str ){
	int i;
	char *temp = str;
	for( i = 0; str[i] != '\0'; i++ ){

	}
	temp[i+1] = '\0';
	temp[i] = '\n';

	putStr( temp );
}

/* printP
 * TYPE: void -> void
 * PRE: console must be initialized
 * POST: -
 * SIDE-EFFECT: prints all processes to the console
 */
void printP(){
	pcb * temp = list_queue( 1 );

	if( temp != NULL ){
		printSln( "Active processes" );
		printSln( "----------------" );
		printSln( "PID      Pname      Priority      State" );
		printN( temp->pid );
		printS( "      ");
		printS( "\t" );
		printS( temp->progid->pname );
		printS( "      ");
		printS( "\t" );
		printN( temp->priority );
		printS( "      ");
		printS( "\t" );
		printNln( temp->state );

		for( temp++; temp != list_queue( 1 ); temp++ ){
			printN( temp->pid );
			printS( "\t" );
			printN( temp->progid->progid );
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
		printN( temp->progid->progid );
		printS( "\t" );
		printN( temp->priority );
		printS( "\t" );
		printNln( temp->state );

		for( temp++; temp != list_queue( 1 ); temp++ ){
			printN( temp->pid );
			printS( "\t" );
			printN( temp->progid->progid );
			printS( "\t" );
			printN( temp->priority );
			printS( "\t" );
			printNln( temp->state );
		}
		printSln( "------------------------" );
		printSln( "End of waiting processes" );
	}
}

/* sleep(ms)
 * TYPE: int -> void
 * PRE: exceptions must be initialized
 * POST: -
 * SIDE-EFFECT: puts current process to sleep for ms milliseconds
 */
void sleep( int ms ){
	//TODO: Add syscall
	ksleep( ms, getCurrent() );
}

/* block
 * TYPE: void -> void
 * PRE: exceptions must be initialized
 * POST: -
 * SIDE-EFFECT: puts current process to sleep until woken by another process
 */
void block(){
	//TODO: Add syscall
	ksleep( -1, getCurrent() );
}
