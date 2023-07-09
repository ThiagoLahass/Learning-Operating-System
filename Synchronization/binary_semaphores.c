#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semFuel;

int fuel = 50;

void* routine(void* args){
    sem_wait(&semFuel);
    fuel += 50;
    printf("Current value is %d \n", fuel);
    sem_post(&semFuel);
}

int main(int argc, char* argv[]){
    pthread_t th[THREAD_NUM];
    int i;
    sem_init(&semFuel, 0, 1);
    for( i = 0; i < THREAD_NUM; i++ ){
        int* a = calloc(1, sizeof(int));
        *a = i;
        if(pthread_create(&th[i], NULL, &routine, a) != 0 ){
            perror("Failed to create thread!\n");
        }
    }

    for( i = 0; i < THREAD_NUM; i++ ){
        if(pthread_join(th[i], NULL) != 0 ){
            perror("Failed to join thread!\n");
        }
    }

    sem_destroy(&semFuel);

    return 0;
}