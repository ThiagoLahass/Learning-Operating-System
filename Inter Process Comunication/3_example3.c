#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int count=0;

void alarm_action(int par){
    printf("write blocked after %d chars \n", count);
    exit(0);
}

int main(){
    int p[2];
    char c = 'x';
    if (pipe(p) < 0)
        perror("pipe call");

    signal(SIGALRM,alarm_action);

    for(;;) {
        alarm(20); 
        write(p[1], &c, 1);
        if((++count%1024) == 0)
            printf("%d chars in pipe\n", count);
    }
}
