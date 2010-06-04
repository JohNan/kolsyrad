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
	char c[2];
	c[0] = ch;
	c[1] = '\0';
	printS( c );
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
	printC( ch );
	printC( '\n' );
}

void printSln( char * str ){
	putStr( str );
	printC( '\n' );
}

void ps(){
	syscall_ps();
}

void sleep( int ms ){
	syscall_sleep(ms, 255);
}

void sleep_pid( uint8_t p, int ms ){
	syscall_sleep( ms, p );
}

void block(){
	syscall_block(-1, 255);
}

void block_pid( uint8_t p ){
	syscall_block( -1, p );
}

void unblock( uint8_t p ){
	syscall_unblock( p );
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
