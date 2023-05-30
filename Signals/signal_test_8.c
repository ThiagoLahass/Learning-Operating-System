#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void morte_filho(int n){
	printf("morreu o meu filho %d eu sou %d\n", wait(NULL), getpid());
}
 
int main() {
	signal(SIGCHLD, morte_filho);
	//signal(SIGCHLD, SIG_DFL);
	//signal(SIGCHLD, SIG_IGN);
	pid_t pid=fork();
	if (pid==0) {
		if(fork() == 0){
			printf("NETO..... pid=%d\n",getpid());
			sleep(5);
			exit(0);
		}else{
			printf("FILHO... pid=%d\n",getpid());
			sleep(30);
			exit(0);
		}
	}
	else {
		printf("PAI..... pid=%d\n",getpid());
		while(1);
			exit(0); 
	}
}
