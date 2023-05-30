#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>

int alarmFlag = 0; /* Global alarm flag */
void alarmHandler();   /* Forward declaration of alarm handler */
/**************************************************************/
int main() {
	signal (SIGALRM, alarmHandler); /* Install signal handler */
	alarm(3); /* Schedule an alarm signal in three seconds */
	printf("Looping...\n"); 
	while (!alarmFlag){          /* Loop until flag set */
		pause();                   /* Wait for a signal */
	}
	printf("Loop ends due to alarm signal\n");
	return 0;
}
/***********************************************************/
void alarmHandler() {
	printf("An alarm clock signal was received\n");
	alarmFlag = 1;
}
