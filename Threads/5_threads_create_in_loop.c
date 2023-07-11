#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    pthread_mutex_init(&mutex, NULL);

    int num_threads = 8;
    pthread_t th[num_threads];

    for( int i=0; i < num_threads; i++ ){
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0){
            return 1;
        }
        printf("Thread %d has started\n", i);
    }

    for( int i=0; i < num_threads; i++ ){
        if(pthread_join(th[i], NULL) != 0){
            return 2;
        }
        printf("Thread %d has finished\n", i);
    }

    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}