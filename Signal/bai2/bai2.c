#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0; 

void alarm_handler(int num)
{
	count++;
	printf("Timer: %d second\n",count);
	if(count >= 10)
	{
		exit(0);
	}

	alarm(1);
}

void main()
{
	signal(SIGALRM,alarm_handler);
	alarm(1);//thiet lap bo dem moi giay

	while(1)

}
