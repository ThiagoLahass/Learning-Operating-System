#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int arr[] = {1, 2, 3, 4, 1, 2, 7};
    int arrSize = sizeof(arr)/sizeof(int);
    int start, end;
    int fd[2];

    if(pipe(fd) == -1){
        return 1;
    }

    pid_t pid = fork();
    if(pid < 0){
        return 2;
    }

    if( pid == 0 ){ //Child
        start = 0;
        end = arrSize / 2;
    }
    else{
        start = arrSize / 2;
        end = arrSize;
    }

    int sum = 0;
    int i;
    for( i = start; i < end; i++ ){
        sum += arr[i];
    }

    printf("Calculated partial sum: %d\n", sum);

    if( pid == 0 ){ //Child
        close(fd[0]);
        if(write(fd[1], &sum, sizeof(sum)) == -1){
            return 3;
        }
        close(fd[1]);
    }
    else{
        int sumFromChild;
        close(fd[1]);
        if(read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1){
            return 4;
        }
        close(fd[0]);

        int totalSum = sum + sumFromChild;
        printf("Calculated Total sum: %d\n", totalSum);
        wait(NULL);
    }

    return 0;
}
