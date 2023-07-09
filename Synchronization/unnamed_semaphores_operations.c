#include <semaphore.h>

// pshared indicates whether the semaphore is shared between threads of a process or between processes
// pshared == 0, the semaphore is shared between threads of a process
// If pshared has a nonzero value, it indicates that the semaphore is shared by processes
// In that case the semaphore has to be placed in a shared memory segment which is attached to the concerned processes
int sem_init (sem_t *sem, int pshared, unsigned int value);

int sem_destroy (sem_t *sem);
