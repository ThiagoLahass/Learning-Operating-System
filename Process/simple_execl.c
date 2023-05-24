#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    execl("/bin/ls", "ls", "-l", NULL);

    return 0;
}
