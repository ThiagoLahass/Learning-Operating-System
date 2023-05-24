#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[]){
    pid_t pid = fork();
    printf("Hello world from pid: %d\n", pid);

    return 0;
}
