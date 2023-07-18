#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

int main() {
	int p1[2]; // CHILD => PARENT
    int p2[2]; // PARENT => CHILD
	pid_t pid;

    if ( pipe(p1) < 0 ) { // Open the pipe  1
        fprintf(stderr,"An error ocurred with opening the pipe 1\n");
        return 1;
    }
    if ( pipe(p2) < 0 ) { // Open the pipe  2
        fprintf(stderr,"An error ocurred with opening the pipe 2\n");
        return 2;
    }

    if ( (pid=fork()) < 0 ) {
        fprintf(stderr,"An error ocurred with fork\n");
        return 3;
    }

    if ( pid == 0 ) { /* child */
        close(p1[0]);
        close(p2[1]);
        int x;
        if(read(p2[0], &x, sizeof(x)) == -1){
            fprintf(stderr,"An error ocurred with reading from the pipe\n");
            return 4;
        }
        printf("Received: %d\n", x);
        x *= 4;
        if(write(p1[1], &x, sizeof(int)) == -1 ){
            fprintf(stderr,"An error ocurred with writing to the pipe\n");
            return 5;
        }
        printf("Wrote: %d\n", x);
        close(p1[1]);
        close(p2[0]);
    }
    else {
        srand(time(NULL));
        close(p1[1]);
        close(p2[0]);
        int x = rand() % 10;
        if(write(p2[1], &x, sizeof(int)) == -1 ){
            fprintf(stderr,"An error ocurred with writing to the pipe\n");
            return 6;
        }
        printf("Wrote: %d\n", x);
        if(read(p1[0], &x, sizeof(x)) == -1){
            fprintf(stderr,"An error ocurred with reading from the pipe\n");
            return 7;
        }
        close(p1[0]);
        close(p2[1]);
        printf("Result: %d\n", x);
        wait(NULL);
    }   
}
