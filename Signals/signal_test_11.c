#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(int argc, char *argv[]){

	sigset_t intmask;

	sigemptyset(&intmask);
	sigaddset(&intmask, SIGINT);
	sigprocmask(SIG_BLOCK, &intmask, NULL);

	/* se Ctrl-c é pressionado enquanto este código está
	executando, o sinal SIGINT é bloqueado*/

	sigprocmask(SIG_UNBLOCK, &intmask, NULL);
	
	/* se Ctrl-c é pressionado enquanto este código está executando, ou durante a execução do código acima, o sinal é tratado aqui*/;



	sigset_t blockmask;
	sigset_t oldset;

	sigfillset(&blockmask);
	sigprocmask(SIG_SETMASK, &blockmask, &oldset);

	/* todos os sinais estão bloqueados neste trecho*/

	sigprocmask(SIG_SETMASK, &oldset, NULL);

	/* a antiga máscara de sinais é reestabelecida aqui */

}
