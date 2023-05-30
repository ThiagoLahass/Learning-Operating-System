#include <sys/types.h>  
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
int main() {

	signal(SIGALRM, SIG_IGN);

	alarm(1);

	int i = 1;
	
	for( i = 1; i <= 5; i++){
		sleep(1);
		printf("Elapsed %d second(s)\n", i);
	}

	signal(SIGALRM, SIG_DFL);

	alarm(1);

	for( i = 0; i < 5; i++){
		sleep(1);
		printf("Elapsed %d second(s)\n", i);
	}

	return 0;
}
