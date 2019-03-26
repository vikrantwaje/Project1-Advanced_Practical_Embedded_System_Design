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


#include"server.h"
#include"temp_sensor.h"

mqd_t mqdes_server;
client_request_t client_request;
request_cmd_t client_temperature_type_request;
client_data_t client_data;
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

	/*Server Thread*/
	int recv_stat;
	char str[30];
	int send_data_len = 0;

	int socket_flag = 0;	/*Not Connected*/
	if(socket_setup() != SOCKET_SETUP_SUCCESS){
		perror("Error in setup of socket");
	}
	if( socket_connect() == SOCKET_CONNECT_SUCCESS )
	{
		socket_flag = 1;
	}

	else{
		perror("Error in socket connect");

	}

	while(socket_flag == 1)
	{
		memset(str,0,sizeof(str));
		if((recv_stat = recv(sock_stat, str,sizeof(str),0) < 0))
		{
			perror("read error");
			socket_flag = 0;
			break;
		}
		else{


			RxBuf[0] = str;

			if(strcmp(RxBuf[0],"request_temp_data") == 0)
			{
				printf("\n\rtemp func received ");
				/*call temp_read()*/
				client_temperature_type_request = REQUEST_CELSIUS;
				client_request.client_get_temp_flag = 1;
				//	strcpy(client_data.sensor_string,"temp: ");
				//	client_data.sensor_data = 26.0;
				if(mq_receive(mqdes_server,(char *)&client_data,sizeof(client_data_t),NULL) ==-1){
					perror("Reception of data from temperature thread unsuccessfull");	
				}	
				if((send(sock_stat,&client_data ,sizeof(client_data_t),0))<0){
					perror("Error while sending temperature structure. Please try again!!");
					client_request.client_get_temp_flag = 0;
				} 


			}

			else if(strcmp(RxBuf[0],"request_light_val") == 0)
			{
				printf("\n\rLight val func received ");
				/*call light_val()*/
				client_request.client_get_lux_flag = 1;
				//strcpy(client_data.sensor_string,"light: ");
				//client_data.sensor_data = 1533.0;
				if(mq_receive(mqdes_server,(char *)&client_data,sizeof(client_data_t),NULL) ==-1){
					perror("Reception of data from light sensor thread unsuccessfull");	
				}	

				if((send(sock_stat,&client_data ,sizeof(client_data_t),0))<0){
					perror("Error while sending light structure. Please try again!!");
					client_request.client_get_lux_flag = 0;
				} 
			}

			else if(strcmp(RxBuf[0],"request_sys_state") == 0)
			{
				printf("System State func received \n");
				/*System State func()*/
				client_request.client_get_system_stat_flag =1;
			}	

			else if(strcmp(RxBuf[0],"close") == 0)
			{
				printf("Closing Socket \n");
				socket_flag = 0;
				//		close(socket_fd);	

				exit;
			}

			else 
			{
				printf("Unrecognized command. Please try again!\n");
			}	
		}
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

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT_NUM);

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



