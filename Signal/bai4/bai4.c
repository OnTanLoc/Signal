#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigtstp(int sig)
{
	printf("SIGTSTP ignored\n");
}

int main()
{
	signal(SIGTSTP, handle_sigtstp);
	printf("bam CTRL + Z de bo qua signal SIGTSTP");

	while (1)
	{
        	sleep(1);
	}

	return 0;
}
