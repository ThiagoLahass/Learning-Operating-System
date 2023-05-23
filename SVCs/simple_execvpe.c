#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    char* arg[] = {
        "ls",
        "-l",
        NULL
    };

    char* env[] = {
        "TEST=enviroment variable",
        NULL
    };

    execvpe("ls", arg, env);

    return 0;
}
