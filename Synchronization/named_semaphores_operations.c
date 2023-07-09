#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

sem_t *sem_open (const char *name, int oflag);
sem_t *sem_open (const char *name, int oflag, mode_t mode, unsigned int value);

// V operation
int sem_post (sem_t *sem); 

//P operation
int sem_wait (sem_t *sem);

//Same at P operation, but not block the calling process
int sem_trywait (sem_t *sem);

//Same at P operation, but not waiting for the abs_timeout time, before return
int sem_timedwait (sem_t *sem, const struct timespec *abs_timeout);


struct timespec { 
    time_t tv_sec;      /* Seconds */ 
    long   tv_nsec;     /* Nanoseconds [0 .. 999999999] */
};         

//Get the value of sem
int sem_getvalue (sem_t *sem, int *sval);

//sem_unlink removes the semaphore associated with the name
int sem_unlink (const char *name);

