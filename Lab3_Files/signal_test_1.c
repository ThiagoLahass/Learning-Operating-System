#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#ifndef SLEEP
#define SLEEP 5
#endif

int s = 0;

static void sig_quit( int sig ){
    printf("In sig_quit, s=%d. Now sleeping...\n", ++s);
    sleep(SLEEP);
    printf("sig_quit, s=%d: exiting\n", s);
}

static void sig_int( int sig ){
    printf("In sig_int, s=%d. Returning immediately.\n", ++s);
}

int main(int argc, char const * argv[]){
    printf("\n=> Establishing initial signal hander via signal(3).\n");
    if(signal(SIGQUIT, sig_quit) == SIG_ERR){
        fprintf( stderr, "Can't set signal handler\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGINT, sig_int) == SIG_ERR){
        fprintf( stderr, "Can't set signal handler\n");
        exit(EXIT_FAILURE);
    }

    sleep(SLEEP);

    printf("=> Time for a secong interruption\n");
    sleep(SLEEP);
    printf("Now exiting.\n");
    exit(EXIT_SUCCESS);
    
    return 0;
}