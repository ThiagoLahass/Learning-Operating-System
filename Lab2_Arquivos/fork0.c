#include <stdio.h>
#include <unistd.h>     // For the syscall functions.
#include <sys/wait.h>   // For wait and related macros.


// For the syscall functions.
int main() {
	pid_t pid = fork(); // Fork a child process.
	if (pid < 0) { // Error occurred.
		fprintf(stderr, "Fork failed!\n");
		return 1;
	} else if (pid == 0) { // Child process.
		printf("[CHILD]: PID: %d - PPID: %d\n", getpid(), getppid());
	} else { // Parent process.
		printf("[PARENT]: PID: %d - PPID: %d\n", getpid(), getppid());
	}
	return 0;
}
