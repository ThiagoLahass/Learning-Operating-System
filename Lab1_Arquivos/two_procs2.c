#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int glob = 6;

int main(void) {
	int var; 			/* external variable in initialized data */
	pid_t pid;			/* automatic variable on the stack */
	
	var = 88;
	printf("before fork\n");
	
	setpgid(getpid(), getppid());
	if ( (pid = fork()) < 0)
		fprintf(stderr, "fork error\n");
	else if (pid == 0) { 		/* ***child*** */
		glob++; 		/* modify variables */
		var++;
		setpgid(getpid(), getpid());
	}
	else
		sleep(3);		/* ***parent***; try to guarantee that child ends first*/

	printf("pid = %d, ppid = %d, uid = %d, pgid = %d\n", getpid(), getppid(), getuid(), __getpgid(getpid()));
	return 0;
}
