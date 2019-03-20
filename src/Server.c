/*
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 10, 2019
 * Course: Advanced Embedded Software Development
 * 
 * This program demonsrates IPC using Sockets for Project 1.
 * This is the Server Side.
 * Reference[1]: http://www.it.uom.gr/teaching/distrubutedSite/dsIdaLiu/labs/lab2_1/sockets.html
 * Reference[2]: https://www.youtube.com/watch?v=pFLQmnmDOo
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netdb.h>

#define	LOG_FILE_NAME	"socketlog.txt"
#define	PORT_NUM	(7000)

// typedef struct 
// {
// 	char string[20];
// 	int len;
// 	int led;
	
// }IPCMessage_t;

char *RxBuf[10] = {0};

void set_sig_handler(void);
long getMicrotime();

int socket_fd;
int check_stat;
int sig_flag = 0;
int sock_stat;

int main()
{
	set_sig_handler();
	int recv_stat;
	char str[20];
	int send_data_len;
	struct sockaddr_in server_addr;
//	set_sig_handler();
//	int send_data_len;

	socket_fd = socket(AF_INET, SOCK_STREAM,0);

	if(socket_fd < 0)
	{
		perror("Server: socket()");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(7000);
	socket_fd = socket(AF_INET, SOCK_STREAM,0);

	if(socket_fd < 0)
	{
		perror("Server: socket()");
		exit(1);
	}

	if(bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
	{
		perror("Server: bind()");
		exit(1);
	}

	listen(socket_fd, 5);

	sock_stat = accept(socket_fd, (struct sockaddr *) 0,0);

	if( sock_stat == -1)
	{
			perror("Serve: accept()");
	}

	while(1){
			memset(str,0,sizeof(str));
			if((recv_stat = recv(sock_stat, str,sizeof(str),0) < 0))
			{
				perror("read error");
			}
			RxBuf[0] = str;

			if(strcmp(RxBuf[0],"request_temp_data") == 0)
			{
				printf("temp func received \n");
				/*call temp_read()*/
			}

			else if(strcmp(RxBuf[0],"request_light_val") == 0)
			{
				printf("Light val func received \n");
				/*call light_val()*/
			}

			else if(strcmp(RxBuf[0],"request_sys_state") == 0)
			{
				printf("System State func received \n");
				/*System State func()*/
			}

			else if(strcmp(RxBuf[0],"close") == 0)
			{
				printf("Closing Socket \n");
				close(socket_fd);
				return 0;
			}
				
			else 
				printf("Unrecognized command. Please try again!\n");
	}

	return 0;

}



/*Below signals not called now*/



void sig_handler(int signo, siginfo_t *info, void *extra)
{
	sig_flag = 1;
	// fptr = fopen(LOG_FILE_NAME, "a");
	// fprintf(fptr, "Time - %ld", getMicrotime());
	// fprintf(fptr, "SIG Detected, Exiting!\n");
	// fclose(fptr);
	close(socket_fd);
	exit(0);
}

void set_sig_handler(void)
{
    struct sigaction action;
    action.sa_flags = SA_SIGINFO; 

    action.sa_sigaction = sig_handler;
 
    if (sigaction(SIGINT, &action, NULL) == -1)
    { 
        perror("sigusr: sigaction");
        _exit(1);
    }
}

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
