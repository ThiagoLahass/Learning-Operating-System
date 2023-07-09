#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semaphore;

void* routine(void* args){
    int index = *(int*)args;
    sem_wait(&semaphore);
    sleep(index+1);
    int semVal;
    sem_getvalue(&semaphore, &semVal);
    printf("(%d) Current semaphore value is %d\n", index, semVal);
    sem_post(&semaphore);
    free(args);
}

int main(int argc, char* argv[]){
    pthread_t th[THREAD_NUM];
    int i;
    sem_init(&semaphore, 0, 4);

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

    sem_destroy(&semaphore);

    return 0;
}