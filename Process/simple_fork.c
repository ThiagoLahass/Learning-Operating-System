#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
   int x;

   x = 0;
   pid_t pid = fork();

   // Child Process
   if( pid == 0 ){
      x = 1;
   }

   printf("I am process %ld and my x is %d\n", (long)getpid(), x);

   return 0;
}
