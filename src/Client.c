/*
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 10, 2019
 * Course: Advanced Embedded Software Development
 * 
 * This program demonsrates IPC using Sockets for Project 1.
 * This is the Client Side.
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
#include <arpa/inet.h>

#define	LOG_FILE_NAME	"socketlog.txt"

void set_sig_handler(void);
long getMicrotime();


int sig_flag = 0;
int socket_fd;

int main()
{
	set_sig_handler();
	struct sockaddr_in server_addr;
	char msg_buf[10];
	char msg_buf1[10];
	char RxBuf[10][10];
	int tan;
	int send_data_len;

printf("Before scket();\n");
	
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd < 0)
	{
		perror("socket()");
		exit(1);
	}

	printf("created scket();\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(7000);
	//server_addr.sin_addr.s_addr = inet_addr("128.138.189.197");
	server_addr.sin_addr.s_addr = inet_addr("10.0.0.78");	
	//server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("About to Connect() scket();\n");
	/*If connection establishment failed, close socket*/
	if((connect(socket_fd,(struct sockaddr *)&server_addr, sizeof(server_addr))) < 0)
	{
		perror("Socket connect()");
		close(socket_fd);
		exit(1);
	}

while(1){
int msg_tx;
char input_cmd[20];
printf("\nEnter any of the following commands: \n");
printf("\"request_temp_data_kelvin\": for receiving temperature sensor values in Kelvin\n");
printf("\"request_temp_data_celcius\": for receiving temperature sensor values in Celcius \n");
printf("\"request_temp_data_fahren\": for receiving temperature sensor values in Fahrenheit\n");
printf("\"request_light_val\": for receiving light sensor values \n");
printf("\"request_sys_state\": for receiving live system stat \n");
printf("\"close\": for terminating connection \n\n");


scanf("\n%s", input_cmd);
int msg_txing[1];
		msg_txing[0] = msg_tx;
		send_data_len = send(socket_fd, &input_cmd, 17, 0);
		printf("Command being sent = %s\n",input_cmd);
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
