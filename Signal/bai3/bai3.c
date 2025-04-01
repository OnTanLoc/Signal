#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int count = 0;

void SIGUSR1_handler(int num)
{
	count ++;
	printf("received signal form parent\n");
	if(count >= 5)
	{
		exit(0);
	}
}

void main()
{
	int ret_var = fork();
	
	if(ret_var == 0)
	{
		signal(SIGUSR1,SIGUSR1_handler);
		while(1)
		{
			pause();
		}
	}
	else if (ret_var > 0)
	{
		for(int i = 0; i < 5; i++)
		{
			sleep(1);//doi process children dang ki signal  handler
			kill(ret_var,SIGUSR1);
		}
	}	
}
