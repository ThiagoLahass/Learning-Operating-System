#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {

    int fd[3][2];
    int i;
    for(i = 0; i < 3; i++){
        if(pipe(fd[i]) == -1){
            return 1;
        }
    }

    pid_t pid1 = fork();
    if( pid1 < 0 ){
        return 2;
    }

    if( pid1 == 0 ){ // Child Process 1
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        int x;
        if(read(fd[0][0], &x, sizeof(int)) < 0){
            return 3;
        }
        x += 5;
        if(write(fd[1][1], &x, sizeof(int)) < 0){
            return 4;
        }
        close(fd[0][0]);
        close(fd[1][1]);

        return 0;
    }

    pid_t pid2 = fork();
    if( pid2 < 0 ){
        return 5;
    }

    if( pid2 == 0 ){ // Child Process 2
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        int x;
        if(read(fd[1][0], &x, sizeof(int)) < 0){
            return 6;
        }
        x += 5;
        if(write(fd[2][1], &x, sizeof(int)) < 0){
            return 7;
        }
        close(fd[1][0]);
        close(fd[2][1]);

        return 0;
    }

    // Parent Process
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    int x = 0;
    printf("Input number: ");
    scanf("%d", &x);
    if(write(fd[0][1], &x, sizeof(int)) < 0){
        return 8;
    }

    if(read(fd[2][0], &x, sizeof(int)) < 0){
        return 9;
    }

    close(fd[0][1]);
    close(fd[2][0]);

    printf("Result is %d\n", x);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0; 
}
