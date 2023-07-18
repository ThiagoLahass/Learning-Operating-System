#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
	int fd[2];
	pid_t pid;

    if ( pipe(fd) < 0 ) {           // Open the pipe  
        fprintf(stderr,"An error ocurred with opening the pipe\n");
        return 1;
    }

    if ( (pid=fork()) < 0 ) {
        fprintf(stderr,"An error ocurred with fork\n");
        return 2;
    }

    if ( pid == 0 ) {               /* child */
        close(fd[0]);
        printf("Input a number: ");
        int x;
        scanf("%d", &x);
        if(write(fd[1], &x, sizeof(int)) == -1 ){
            fprintf(stderr,"An error ocurred with writing to the pipe\n");
            return 3;
        }
        close(fd[1]);
    }
    else {
        close(fd[1]);
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1){
            fprintf(stderr,"An error ocurred with reading from the pipe\n");
            return 4;
        }
        close(fd[0]);

        // Changes the output from STDOUT_FILENO to testeResult.txt
        int file = open("testeResult.txt", O_WRONLY | O_CREAT, 0777 );
        if( file == -1 ){
            return 5;
        }
        dup2(file, STDOUT_FILENO);
        close(file);        

        //Print's on testeResult.txt
        printf("Got from child process: %d\n", y);
    }   
}
