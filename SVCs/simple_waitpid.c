#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    pid_t pid1 = fork();

    if( pid1 == -1 ){
        printf("Error creating process");
        return 1;
    }
    if( pid1 == 0 ){
        sleep(4);
        printf("Finished execution (%d)\n", getpid());
        return 0;
    }

    pid_t pid2 = fork();
    if( pid2 == -1 ){
        printf("Error creating process");
        return 2;
    }
    if( pid2 == 0 ){
        sleep(1);
        printf("Finished execution (%d)\n", getpid());
        return 0;
    }

    // Verification if the child is finished
    // Do with the 'WNOHANG' flag
    pid_t pid1_res = waitpid(pid1, NULL, WNOHANG);
    printf("Status for (%d) %d\n", pid1, pid1_res);

    pid1_res = waitpid(pid1, NULL, 0);
    printf("Waited for %d\n", pid1_res);
    pid_t pid2_res = waitpid(pid2, NULL, 0);
    printf("Waited for %d\n", pid2_res);

    return 0;
}
