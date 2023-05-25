#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef SLEEP
#define SLEEP 5
#endif


static void sig_usr1( int sig ){
    printf("Eu apanhei o SIGUSR1\n");
}

int main(int argc, char const * argv[]){
    pid_t pid = fork();
    int status;

    if( pid == 0 ){ //Child
        printf("Eu sou o processo filho, pid = %d\n", getpid());
        if(signal(SIGUSR1, sig_usr1) == SIG_ERR){
            fprintf( stderr, "Can't set signal handler\n");
            exit(EXIT_FAILURE);
        }
        char c;
        while (scanf("%c", &c) != EOF) {
            printf("%c", c);
        }
    }
    else{ // Parent
        printf("Eu sou o processo pai, pid = %d\n", getpid());

        sleep(5);

        if (kill(pid, SIGUSR1) == -1) {
            perror("Erro ao enviar sinal para o processo filho\n");
            exit(1);
        }

        // Aguarda o término do processo filho por 20 segundos
        if (waitpid(pid, &status, WNOHANG) == 0) {
            sleep(20);
            if (waitpid(pid, &status, WNOHANG) == 0) {
                printf("Meu filho ainda não terminou. Cansei de esperar, vou vazar com um sinal SIGKILL\n");
                kill(pid, SIGKILL);
            }
        }
    }
    
    return 0;
}