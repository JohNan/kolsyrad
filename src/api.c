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
	printS( temp );
	printC( '\n' );
}

void printCln( char ch ){
	putCh( ch );
	putCh( '\n' );
}

void printSln( char * str ){
	putStr( str );
	printC( '\n' );
}

void ps(){
	syscall_ps();
}

void sleep( int ms ){
	syscall_sleep(ms, NULL);
}

void block(){
	syscall_block(-1, NULL);
}

uint8_t getPriority(uint8_t p){
	return syscall_getPriority(p);
}

uint8_t getState(uint8_t p){
	return syscall_getState(p);
}

char *getName(uint8_t p){
	return syscall_getName(p);
}

void set_priority( int pib, uint8_t p ){
	syscall_set_prio( pib, p );
}
