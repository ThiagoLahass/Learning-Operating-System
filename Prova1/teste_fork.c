#include <stdio.h>
#include <unistd.h>

int main(){

    if (fork() && (fork())) {

        printf("IF 1 => I'm process: %d, and my parent is: %d\n", getpid(), getppid());
        sleep(10);

        if (fork() || fork()) {

            printf(" IF 2 =>  I'm process: %d, and my parent is: %d\n", getpid(), getppid());
            sleep(10);
            fork();

            printf(" IF 3 =>  I'm process: %d, and my parent is: %d\n", getpid(), getppid());

        }
    }
    printf("I'm process: %d, and my parent is: %d; I have finish my execution\n", getpid(), getppid());
    return 0;
}