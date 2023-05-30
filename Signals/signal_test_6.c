#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 

void trata_SIGSEGV(int signum) {
	printf("Acesso indevido à memória.\n"); 
	printf("Nao vou esconder este erro. :-)\n"); 
	signal(SIGSEGV, SIG_DFL); 
	raise(SIGSEGV); /* equivale a kill(getpid(), SIGSEGV); */ 
}

int main() {
	signal(SIGSEGV, trata_SIGSEGV); 
    char *buffer;
    buffer[0] = 0;
    return 0; 
}
