#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#define NUM_THREADS 5

void *PrintHello(void *threadid) {
    int tid;
    tid = (int)threadid;
    printf("Hello World! It's me, thread #%d!\n", tid);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {

    pthread_attr_t tattr;
    pthread_t tid;
    void *arg;
    int ret;

    /* default behavior*/
    ret = pthread_create(&tid, NULL, PrintHello, arg);

    /* initialized with default attributes */
    ret = pthread_attr_init(&tattr);

    /* default behavior specified*/
    ret = pthread_create(&tid, &tattr, PrintHello, arg);
    
    pthread_exit(NULL);
} 