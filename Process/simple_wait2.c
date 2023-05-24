#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    pid_t pid = fork();
    int n;

    // Child Process
    if( pid == 0 ){
        n = 1;
    }
    else{
        n = 6;
    }

    // Parent Process
    if( pid != 0 )
        wait(NULL);
    
    for( int i = n; i < n+5; i++ ){
        printf("%d ", i);
        fflush(stdout);
    }
    
    // Parent Process
    if( pid != 0 ){
        puts("");
    }

    return 0;
}
