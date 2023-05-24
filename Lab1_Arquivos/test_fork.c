#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc , char * argv []) {
    pid_t childpid = 1;
    int i , n ;

    /* check for valid number of command - line arguments */
    n = atoi ( argv [1]) ;
    
    for ( i = 1; i <= n ; i ++){
        if( childpid != 0 )
            childpid = fork();
        else
            break;
    }

    if( childpid != 0) sleep(1);
    fprintf ( stderr ,"process ID :% ld parent ID :% ld child ID :% ld\n", ( long ) getpid () , ( long ) getppid () , ( long ) childpid ) ;

    return 0;
}