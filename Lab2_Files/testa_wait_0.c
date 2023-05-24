/* arquivo test_wait0.c */

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

	pid_t child pid;

	if ((pid=fork()) == 0) {
		printf("\tOi, eu sou o Filho1, PID = %d, PPID = %d.\n",getpid(),getppid()) ;
		printf("\tVou ficar num loop infinito.\n") ;
		for(;;) ;
	}else {
		while (childpid = waitpid(-1, NULL, WNOHANG)){
   			if ((childpid == -1) && (errno != EINTR))
				break;
			else {
				printf("\tMeu filho ainda nao morreu ... vou esperar mais um pouco!\n") ;
				sleep(5);
			}
		}
	}

exit(0);
}

