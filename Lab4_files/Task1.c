#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {

    int x = 0;
    printf("Input number betwen 1 and 5: ");
    scanf("%d", &x);

    int fd[3][2];                                               // 3 Pipes
    int i;
    for(i = 0; i < 3; i++){
        if(pipe(fd[i]) == -1){                                  // Open the pipes
            return 1;   
        }
    }

    pid_t pid1 = fork();                                        // Create Child process 1
    if( pid1 < 0 ){
        return 2;
    }

    if( pid1 == 0 ){                                            // Child Process 1
        close(fd[0][1]);                                        // Fecha pipes desnecessarios para esse processo
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        int x;

        // Read x value from the parent
        if(read(fd[0][0], &x, sizeof(int)) < 0){                // fd[0][0] => pipe P(WRITE) -> C1(READ)
            return 3;
        }

        // Read the leng of the message to
        int leng;
        if(read(fd[0][0], &leng, sizeof(int)) < 0){             // fd[0][0] => pipe P(WRITE) -> C1(READ)
            return 4;
        }

        // Read the message
        char my_string[leng];
        if(read(fd[0][0], my_string, sizeof(char)*leng) < 0){   // fd[0][0] => pipe P(WRITE) -> C1(READ)
            return 5;
        }

        // Print the message
        printf("%s\n", my_string);

        // Print the message
        printf("x = %d\n", x);

        srand(time(NULL));
        int arr_size = rand() % 10 + 1;

        int arr[arr_size];
        int i;
        printf("Send: ");
        for(i = 0; i < arr_size; i++){
            arr[i] = rand() % x + 1;
            printf("%d ", arr[i]);
        }
        printf("\n");
        
        // Send the array size to Child Process 2
        if(write(fd[1][1], &arr_size, sizeof(arr_size)) < 0){    // fd[1][1] => pipe C1(WRITE) -> C2(READ)
            return 6;
        }

        // Send the array to Child Process 2
        if(write(fd[1][1], arr, sizeof(arr)) < 0){              // fd[1][1] => pipe C1(WRITE) -> C2(READ)
            return 7;
        }

        close(fd[0][0]);
        close(fd[1][1]);

        return 0;
    }
    pid_t pid2 = fork();
    if( pid2 < 0 ){
        return 8;
    }

    if( pid2 == 0 ){ // Child Process 2
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

        int arr_size;
        // Read the array leng from Child Process 1
        if(read(fd[1][0], &arr_size, sizeof(arr_size)) < 0){
            return 9;
        }

        // Read the array from Child Process 1
        int arr[arr_size];
        if(read(fd[1][0], arr, sizeof(int) * arr_size) < 0){
            return 10;
        }
        int i, sum = 0;

        printf("Received: ");
        for(i = 0; i < arr_size; i++){
            sum += arr[i];
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Send the sum to the Parent
        if(write(fd[2][1], &sum, sizeof(int)) < 0){             // fd[2][1] => pipe C2(WRITE) -> P(READ)
            return 11;
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
    
    // Send value of x to C1
    if(write(fd[0][1], &x, sizeof(int)) < 0){                   // fd[0][1] => pipe P(WRITE) -> C1(READ)
        return 12;
    } 

    static const char my_string[] = "Meu filho, crie e envie para o seu irmão um array "
                                     "de números inteiros com valores randômicos entre 1 e o valor enviado anteriormente. O "
                                     "tamanho do array também deve ser randômico, na faixa de 1 a 10";

    // Send the leng of the message to C1
    int leng = strlen(my_string) + 1;
    if(write(fd[0][1], &leng, sizeof(leng)) < 0){               // fd[0][1] => pipe P(WRITE) -> C1(READ)
        return 13;
    } 

    // Send message to C1
    if(write(fd[0][1], my_string, sizeof(my_string)) < 0){      // fd[0][1] => pipe P(WRITE) -> C1(READ)
        return 14;
    } 

    // Send the value of x to C1
    if(write(fd[0][1], &x, sizeof(int)) < 0){                   // fd[2][1] => pipe P(WRITE) -> C1(READ)
        return 15;
    }

    int sum;
    // Receives the value of the sum from C2
    if(read(fd[2][0], &sum, sizeof(int)) < 0){                  // fd[2][0] => pipe C2(WRITE) -> P(READ)
        return 16;
    }

    close(fd[0][1]);
    close(fd[2][0]);

    printf("The Sum result is %d\n", sum);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // Execute 'date' command
    int pfd[2];
    char buffer[128];
    pid_t pid3;

    if(pipe(pfd) == -1){                                        // Open the pipe
        return 17;
    }

    if (pid3 = fork() == 0) {                                   // Child Process 3
        close(pfd[0]);                                          // Closes the READ fd
        dup2(pfd[1], STDOUT_FILENO);		                    // Duplicate FD to FD2, closing FD2 and making it open on the same file.
        close(pfd[1]);                                          // Closes the READ fd
        execlp("date", "date", NULL);
        perror("Error in execution of 'date'");
        exit(EXIT_FAILURE);

    } else {                                                    // Parent Process
        close(pfd[1]);                                          // Closes the READ fd
        
        read(pfd[0], buffer, sizeof(buffer));

        printf("%s", buffer);
        
        waitpid(pid3, NULL, 0);
    }

    return 0; 
}
