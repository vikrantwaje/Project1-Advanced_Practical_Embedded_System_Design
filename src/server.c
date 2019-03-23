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

//void set_sig_handler(void);
//long getMicrotime();

#include"server.h"



bool client_get_temp_flag;
bool client_get_lux_flag;
bool client_get_system_stat_flag;
/*******************************************************************************************
 * @brief Communicate with external client
 *
 * After connecting with external client, receives command from client and call respective
 * function.

 * @param null
 *
 * @return 0 if error, 1 if success
 ********************************************************************************************/
int server_establish()
{
	//set_sig_handler();

	/*Server Thread*/
	int recv_stat;
	char str[30];
	int send_data_len;


	int socket_flag = 0;	/*Not Connected*/
	while(socket_setup() != SOCKET_SETUP_SUCCESS);
	//while( socket_flag == 0 )
	//{
		if( socket_connect() == SOCKET_CONNECT_SUCCESS )
		{
			socket_flag = 1;

			while(socket_flag == 1)
			{
				memset(str,0,sizeof(str));
				if((recv_stat = recv(sock_stat, str,sizeof(str),0) < 0))
				{
					perror("read error");
					socket_flag = 0;
					break;
				}

				RxBuf[0] = str;

				if(strcmp(RxBuf[0],"request_temp_data") == 0)
				{
					printf("\n\rtemp func received ");
					/*call temp_read()*/
					client_get_temp_flag = 1;
				}

				else if(strcmp(RxBuf[0],"request_light_val") == 0)
				{
					printf("\n\rLight val func received ");
					/*call light_val()*/
					client_get_lux_flag = 1;
				}

				else if(strcmp(RxBuf[0],"request_sys_state") == 0)
				{
					printf("System State func received \n");
					/*System State func()*/
					client_get_system_stat_flag =1;
				}	

				else if(strcmp(RxBuf[0],"close") == 0)
				{
					printf("Closing Socket \n");
					socket_flag = 0;
					close(socket_fd);	

					break;
				}

				else 
				{
					printf("Unrecognized command. Please try again!\n");
				}	
			}
		//}
	}

}




/*******************************************************************************************
 * @brief Socket Setup Routines
 *
 * Call the socket(), bind() and returns 1 on successful setup

 * @param null
 *
 * @return 0 if error, 1 if success
 ********************************************************************************************/
server_response_t socket_setup()
{
	int sock_opt_true = 1;
	int listen_status = 0;
	socket_fd = socket(AF_INET, SOCK_STREAM,0);

	if(socket_fd < 0)
	{
		perror("Server: socket()");
		return SOCKET_FAIL;
	}

		if(setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&sock_opt_true,sizeof(int)) == -1){
		perror("Setsockopt");
		return REUSE_FAIL;
		}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT_NUM);
	socket_fd = socket(AF_INET, SOCK_STREAM,0);

	if(bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
	{
		perror("Server: bind()");
		return BIND_FAIL;
	}

	listen_status=listen(socket_fd, NO_OF_CLIENT);
	if(listen_status == -1){
		LISTEN_FAIL;}

	return SOCKET_SETUP_SUCCESS;
}


/*******************************************************************************************
 * @brief Socket Listening Routines
 *
 * Call the listen() and accept() and returns 1 on successful connection
 * with an external client

 * @param null
 *
 * @return 0 if error, 1 if success
 ********************************************************************************************/
server_response_t socket_connect(void)
{	

	sock_stat = accept(socket_fd, (struct sockaddr *) 0,0);

	if( sock_stat == -1)
	{
		perror("Server: accept()");
		return ACCEPT_FAIL;				
	}

	return SOCKET_CONNECT_SUCCESS;
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
