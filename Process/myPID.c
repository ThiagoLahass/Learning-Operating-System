#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
   pid_t childpid;
   
   childpid = fork();

   if (childpid == -1) {
	   perror("Failed to fork");
	   return 1;
   }

   if (childpid == 0){
      printf("I am child %d, my parent is = %d\n", getpid(), getppid());
   }
   else{
	   printf("I am parent %d, my parent is = %d\n", getpid(), getppid());
   }
   
   return 0;
}
