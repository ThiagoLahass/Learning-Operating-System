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
    int fd = open("sum", O_RDONLY);
    if( fd == -1 ){
        return 1;
    }

    int i;
    if(read(fd, arr , sizeof(arr)) == -1){
        return 2;
    }
    close(fd);

    int sum;
    for(i = 0; i < 5; i++){
        sum += arr[i];
    }
    printf("Sum is %d\n", sum);

    return 0;
}
