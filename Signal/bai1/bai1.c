#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int count = 0;

void signal_handler(int signum)//ham xu li SIGINT
{
	count++;
	printf("SIGINT recived\n");

	if(count >= 3)
	{
		exit(0);//lap 3 lan-> thoat
	}
}

void main()
{
	signal(SIGINT,signal_handler);//dang ki ham xu li SIGINT

	while(1);
}
