/*
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: http://www.it.uom.gr/teaching/distrubutedSite/dsIdaLiu/labs/lab2_1/sockets.html
 * Reference[2]: Based on code from https://riptutorial.com/posix/example/16306/posix-timer-with-sigev-thread-notification
 * 
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netdb.h>
#include "main.h"


int main()
{
	pthread_t thread1, thread2, thread3, thread4;

	int ret_status1, ret_status2, ret_status3, ret_status4;
	
	ret_status1 = pthread_create( &thread1, NULL, socket_thread, /*(void*)&fileinstance*/);
	ret_status1 = pthread_create( &thread2, NULL, temperature_thread, /*(void*)&fileinstance*/);
	ret_status1 = pthread_create( &thread3, NULL, light_sensor_thread, /*(void*)&fileinstance*/);
	ret_status1 = pthread_create( &thread4, NULL, logger_thread, /*(void*)&fileinstance*/);

	if( ret_status1 )
	{
		fprintf( stderr, "socket_thread not created, Error Code: %d\n", ret_status1);
		return 0;
	}
	if( ret_status2 )
	{
		fprintf( stderr, "temperature_thread not created, Error Code: %d\n", ret_status2);
		return 0;
	}
	if( ret_status3 )
	{
		fprintf( stderr, "light_sensor_thread not created, Error Code: %d\n", ret_status3);
		return 0;
	}
	if( ret_status4 )
	{
		fprintf( stderr, "logger_thread not created, Error Code: %d\n", ret_status4);
		return 0;
	}

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	pthread_join( thread3, NULL);
	pthread_join( thread4, NULL);

	printf("Main Thread Exited Successfully \n");
	
	return 1;
}


/**
* @brief Socket thread
*
* Waits for a connection initiated by an external client.
* Once connected, accepts commands from client and acts accordingly.
* If clients commands the connection to "close", server thread disconnects,
* closes the socket connection and waits for a new connection.
*
* @param null
*
* @return null
*/
void *socket_thread(void)
{
	/*Server Thread*/
	int recv_stat;
	char str[20];
	int send_data_len;
	struct sockaddr_in server_addr;

	int socket_flag = 0;	/*Not Connected*/

	while( socket_flag == 0 )
	{
		socket_fd = socket(AF_INET, SOCK_STREAM,0);

		if(socket_fd < 0)
		{
			perror("Server: socket()");
			exit(1);
		}

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = INADDR_ANY;
		server_addr.sin_port = htons(PORT_NUM);
		socket_fd = socket(AF_INET, SOCK_STREAM,0);

		if(bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
		{
			perror("Server: bind()");
			exit(1);
		}

		listen(socket_fd, 5);

		sock_stat = accept(socket_fd, (struct sockaddr *) 0,0);

		if( sock_stat == -1)
		{
				perror("Server: accept()");
	//			socket_flag = 0;
		}

		socket_flag = 1;

		while(socket_flag == 1)
		{
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
				socket_flag = 0;
				close(socket_fd);
				//return 0;
			}
				
			else 
				printf("Unrecognized command. Please try again!\n");
		}
	}
}