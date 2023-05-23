#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    char* arg[] = {
        "ls",
        "-l",
        NULL
    };

    execvp("ls", arg);

    return 0;
}
