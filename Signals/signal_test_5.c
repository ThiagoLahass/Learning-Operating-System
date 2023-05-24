#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const * argv[]){
    pid_t pid  = fork();
    if( pid == -1){
        return 1;
    }

    // On child
    if(pid == 0 ){
        while(1){
            printf("Some text goes here\n");
            usleep(500000);
        } 
    }
    else{
        kill(pid, SIGSTOP);
        int t;
        do{
            printf("Time in seconds for execution: ");
            scanf("%d", &t);
            if( t > 0 ){
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }
        }while(t > 0);
        
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}