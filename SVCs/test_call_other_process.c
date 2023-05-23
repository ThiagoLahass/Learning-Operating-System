#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){

    pid_t pid = fork();

    if( pid == -1 ){
        return 1;
    }

    if( pid == 0 ){
        // Child Process
        execlp("ping", "ping", "-c", "3", "8.8.8.8", NULL);
    }
    else{
        // Parent Process
        wait(NULL);
        printf("Success!\n");
        printf("Some post processing goes here!\n");
    }


    return 0;
}
