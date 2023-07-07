#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* function(void* arg) {
    printf( "This is thread %ld\n", pthread_self() );
    sleep(5);
    return (void *)99;
}

int main(void) {
    pthread_t t2;
    pthread_attr_t attr;
    void *result;

    pthread_attr_init( &attr );
    pthread_create( &t2, &attr, function, NULL );
    pthread_join(t2,&result);

    printf("Thread t2 returned %d\n", (int)result);

    return 0;
}