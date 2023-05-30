#include <sys/types.h>  
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
int main() {
	alarm(10);
	int i = 1;
	
	printf("Looping forever...\n");
	for(;;){
		sleep(1);
		printf("Elapsed %d second(s)\n", i);
		i++;
	}

	return 0;
}
