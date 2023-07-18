#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int fd[2];
	pid_t pid;

    if ( pipe(fd) < 0 ) {                   // Open the pipe  
        fprintf(stderr,"An error ocurred with opening the pipe\n");
        return 1;
    }

    if ( (pid=fork()) < 0 ) {
        fprintf(stderr,"An error ocurred with fork\n");
        return 2;
    }

    if ( pid == 0 ) {               /* child */
        close(fd[0]);
        srand(time(NULL));
        int n, i;
        int arr[10];
        n = rand() % 10 + 1;
        for(i = 0; i < n; i++){
            arr[i] = rand() % 11;
            printf("%d ", arr[i]);
        }
        printf("\n");
        if(write(fd[1], &n, sizeof(int)) == -1 ){
            fprintf(stderr,"An error ocurred with writing to the pipe\n");
            return 3;
        }
        if(write(fd[1], arr, sizeof(int) * n) == -1 ){
            fprintf(stderr,"An error ocurred with writing to the pipe\n");
            return 3;
        }
        close(fd[1]);
    }
    else {
        close(fd[1]);
        int arr[10];
        int n, i;
        if(read(fd[0], &n, sizeof(int)) == -1){
            fprintf(stderr,"An error ocurred with reading from the pipe\n");
            return 4;
        }
        if(read(fd[0], arr, sizeof(int) * n) == -1){
            fprintf(stderr,"An error ocurred with reading from the pipe\n");
            return 4;
        }
        close(fd[0]);

        int sum = 0;
        for(i = 0; i < n; i++){
            sum += arr[i];
        }
        printf("Result of sum is: %d\n", sum);
        wait(NULL);
    }   
}
