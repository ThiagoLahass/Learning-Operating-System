#include <stdio.h>
#include <string.h>
#include <sys/file.h>

#define LEN 100
#define FNAME "testFIFO"

main() {
    int fd, i;
    char msg[LEN];
    
    do {
        fd = open(FNAME,O_WRONLY);
        if (fd == -1) sleep(1);
    } while (fd == -1);

    for( i = 1; i <= 3; i++ ) {
        sprintf(msg,"Hello no %d from process %d\n", i, getpid());
        write( fd, msg, strlen(msg)+1 );
        sleep(3);
        }
    close(fd);
}
