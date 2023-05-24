#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

void handler_sigstp( int sig ){
    printf("Stop not allowed\n");
}

void handler_sigcont( int sig ){
    printf("Input number: ");
    fflush(stdout);
}

int main(int argc, char const * argv[]){
    struct sigaction sa;
    sa.sa_handler = &handler_sigcont;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa, NULL);

    // signal(SIGTSTP, &handler_sigstp);

    int x;
    puts("Input number: ");
    scanf("%d", &x);
    printf("Result of %d * 5 = %d\n", x, x * 5 );
    
    return 0;
}