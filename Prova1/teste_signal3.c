#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void trata_signal(int num) {
    printf("Teste\n");
    signal(SIGINT, trata_signal);
    printf("Operação negada.\n");
}

int main(void) {
    if (signal(SIGINT, trata_signal) == SIG_ERR){
        printf("Erro no signal");
    }
    printf("OK\n");
    for (;;) {sleep(10);}
    exit(0);
}