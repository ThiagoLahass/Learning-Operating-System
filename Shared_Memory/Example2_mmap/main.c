#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define  PAGESIZE 4096

int main(int argc, char* argv[]){

    int v = 5;
    u_int8_t* shared_memory = mmap( NULL, PAGESIZE, 
                                    PROT_READ | PROT_WRITE,
                                    MAP_SHARED, -1, 0);

    *shared_memory = 15;

    pid_t pid;
    pid = fork();
    if(pid == 0){
        v = 80;
        *shared_memory = 15;
    }
    else{
        wait(NULL);
    }

    printf("Not shared: %i\n", v);
    printf("Shared: %i\n", *shared_memory);

    return 0;
}