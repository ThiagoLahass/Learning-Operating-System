#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){

   int pfd[2];
   pipe(pfd);                           // Open the pipe
   
   if (fork() == 0) {                   // Child Process
	close(pfd[1]);                      // Closes the WRITE fd
	dup2(pfd[0], STDIN_FILENO);			// Duplicate FD to FD2, closing FD2 and making it open on the same file.
	close(pfd[0]);                      // Closes the READ fd
	execlp("wc", "wc", (char *) 0);

   } else {                             // Dad Process
	close(pfd[0]);                      // Closes the READ fd
	dup2(pfd[1], STDOUT_FILENO);                    // Duplicate FD to FD2, closing FD2 and making it open on the same file.
	close(pfd[1]);                      // Closes the READ fd
	execlp("ls", "ls", (char *) 0);
   }

   exit(0);
}
