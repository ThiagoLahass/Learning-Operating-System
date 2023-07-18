#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>
#include <fcntl.h>

int main() {
    
    if(mkfifo("myfifo1", 0777) == -1 && errno != EEXIST){
        printf("Could not create fifo file\n");
        return 1;
    }

    int fd = open("myfifo1", O_RDWR);
    int x = 97;
    if(write(fd, &x, sizeof(x)) == -1){
        return 2;
    }
    close(fd);

    return 0;
}
