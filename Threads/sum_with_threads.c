#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define array_size 1000
#define no_threads 10

int a[array_size];
int global_index = 0;
int sum = 0;

pthread_mutex_t mutex1;

void * slave ( void *nenhum ) {
    int local_index, partial_sum = 0;

    do {
        pthread_mutex_lock(&mutex1);

        local_index = global_index;
        global_index++;

        pthread_mutex_unlock(&mutex1);

        if (local_index < array_size)
            partial_sum += *(a+local_index);

    } while (local_index < array_size);

    pthread_mutex_lock(&mutex1);
    sum+= partial_sum;
    pthread_mutex_unlock(&mutex1);

    return(NULL);
}

main() {
    int i;

    pthread_t thread [no_threads] ;

    pthread_mutex_init(&mutex1, NULL);

    for (i = 0; i < array_size; i++)
        a[i] = i+1;

    for (i = 0; i < no_threads; i++)
        if (pthread_create(&thread[i], NULL, slave, NULL) != 0) {
            perror("Pthread_create falhou");
            exit(1);
        }

    for (i = 0; i < no_threads; i++)
        if (pthread_join(thread[i], NULL) != 0) {
            perror("Pthread_join falhou");
            exit(1);
        }
    printf("A soma é %d \n", sum);

}