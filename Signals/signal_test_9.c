#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

main() {
	int (*oldHandler) (); 	   /* To hold old handler value */

	printf("I can be Control-C'ed\n");
	sleep(3);

	oldHandler = signal (SIGINT, SIG_IGN);  /* Ignore Control-C */
	printf("I'm protected from Control-C now\n");
	sleep(3);

	signal (SIGINT, oldHandler);         /* Restore old handler */
	printf("I can be Control-C'ed again\n");
	sleep(3);
	
	printf("Bye!\n"); 
}
