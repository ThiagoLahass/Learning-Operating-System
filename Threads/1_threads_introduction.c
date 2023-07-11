#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine(void* args){
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
}

int main(int argc, char* argv[]){
    pthread_t t1, t2;
    if(pthread_create(&t1, NULL, &routine, NULL) != 0 ){
        perror("Error in pthread create");
        return 1;
    }
    if(pthread_create(&t2, NULL, &routine, NULL) != 0 ){
        perror("Error in pthread create");
        return 2;
    }

    if(pthread_join(t1, NULL) != 0){
        perror("Error in pthread join");
        return 3;
    }
    if(pthread_join(t2, NULL) != 0){
        perror("Error in pthread join");
        return 4;
    }

    return 0;
}