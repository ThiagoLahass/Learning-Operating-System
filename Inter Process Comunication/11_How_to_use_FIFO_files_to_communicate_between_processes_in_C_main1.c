#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int arr[5];
    srand(time(NULL));

    int i;
    for(i = 0; i < 5; i++){
        arr[i] = rand() % 100;
        printf("Generated %d\n", arr[i]);
    }

    if(mkfifo("sum", 0777) == -1 && errno != EEXIST){
        printf("Could not create fifo file\n");
        return 1;
    }

    int fd = open("sum", O_WRONLY);
    if( fd == -1 ){
        return 2;
    }

    if(write(fd, arr, sizeof(arr)) == -1){
        return 3;
    }
    close(fd);

    return 0;
}
