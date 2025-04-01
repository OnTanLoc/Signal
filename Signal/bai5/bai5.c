#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <string.h>
#include <errno.h>

int got_sigint = 0;
int got_sigterm = 0;

void handler(int num)
{
	printf("\nPID:%d\n",getpid());
    if (num == SIGINT)
    {
        got_sigint = 1;
    }
    else if (num == SIGTERM)
    {
        got_sigterm = 1;

    }
}

void main()
{
	signal(SIGINT,handler);
	signal(SIGTERM,handler);

    	printf("Program running. Press Ctrl+C for SIGINT or send SIGTERM to exit.\n");

    	struct pollfd fds[1];//theo doi du lieu vao
    	fds[0].fd = STDIN_FILENO;//fd kiem tra la dau vao
    	fds[0].events = POLLIN;//kiem tra co du kieu doc khong
	fds[0].revents;//kt sau poll tra ve
    
    while (1) {
        if (got_sigint) 
	{
		printf("SIGINT received.\n");
		got_sigint = 0;//dat lai gia tri nhan SIGINT
        }
        
        if (got_sigterm)
       	{
            printf("SIGTERM received. Exiting...\n");
            break;
        }

        int ready = poll(fds, 1, -1);//kiem tra doc ghi file fds. 1: so file doc ghi -1: thoi gian cho
        
        if (ready == -1)
       	{
            if (errno == EINTR) 
	    {
                continue;
            }
            perror("poll");
            break;
        }

	char buffer[256];

        if (fds[0].revents & POLLIN)//co du lieu
       	{
            ssize_t bytes = read(STDIN_FILENO, buffer, sizeof(buffer)-1);
            
	    buffer[bytes]='\0';
            printf("You entered: %s", buffer);
            
            if (strcmp(buffer, "quit\n") == 0) {
                printf("Exiting...\n");
                break;
            }
        }
    }

}
