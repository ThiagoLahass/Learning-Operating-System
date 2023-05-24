#include <stdio.h>
#include <unistd.h>     // For the syscall functions.
#include <sys/wait.h>   // For wait and related macros.
#include <errno.h>

int main() {
    pid_t pid = fork(); // Fork a child process.

    if (pid < 0) { // Error occurred.
        fprintf(stderr, "Fork failed!\n");
        return 1;
    }
    else if (pid == 0) { // Child process.
        printf ("[CHILD]: I'm the child, PID = %d. I live, but I go sleep. Use the ps u command to see my and my parent status.\n", getpid () ) ;
        sleep (1000);
        printf("[CHILD]: I'm finished.\n");
        return 42;
    }
    else { // Parent process.
        printf("[PARENT]: Waiting on child.\n");
        int wstatus;
        int test = waitpid( pid, &wstatus, WUNTRACED );
        if( test == -1 ){
            perror("Error!\n");
            printf("Error code: %d\n", errno);
            if (errno == ECHILD ){
                printf("Error: no child processes found.\n");
            }
        }
        // if (WIFEXITED(wstatus)) {
        //     printf("[PARENT]: Child returned with code %d.\n", WEXITSTATUS(wstatus));
        // }
        if (WIFSIGNALED(wstatus)) {
            printf("[PARENT]: Child was finish by a signal, and the signal is %d.\n", WTERMSIG(wstatus));
        }
        if (WIFSTOPPED(wstatus)) {
            printf("[PARENT]: Child was stopped by a signal, and the signal is %d.\n", WSTOPSIG(wstatus));
        }

    }
    return 0;
}
