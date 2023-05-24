#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    pid_t pid = fork();

    // Child Process
    if( pid == 0 ){
        sleep(1);
    }

    printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());

    int res = wait(NULL);
    if( res == -1 ){
        puts("\nChildren Process:");
        printf("No children to wait for.\n");
    }
    else{
        puts("\nParent Process:");
        printf("Process %d finished execution!\n", res);
    }

    return 0;
}
