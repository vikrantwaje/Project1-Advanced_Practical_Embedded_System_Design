/*********************************************************************************************
*					FILENAME: server.c
**********************************************************************************************/

/* Title: server.c
 * Brief: Responsible for providing various helper functions for setting up the server side
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 10, 2019
 * Course: Advanced Embedded Software Development
 * 
 * This program demonsrates IPC using Sockets for Project 1.
 * This is the Server Side.
 * Reference[1]: http://www.it.uom.gr/teaching/distrubutedSite/dsIdaLiu/labs/lab2_1/sockets.html
 * Reference[2]: https://www.youtube.com/watch?v=pFLQmnmDOo
 */

/*********************************************************************************************
*					HEADER SECTION
**********************************************************************************************/
#include"server.h"
#include"temp_sensor.h"

/********************************************************************************************
*					GLOBAL VARIABLE SECTION
*********************************************************************************************/
mqd_t mqdes_server;
client_request_t client_request;
request_cmd_t client_temperature_type_request;
client_data_t client_data;


mqd_t mqdes_heartbeat;
heartbeat_flag_t heartbeat_flag;
heartbeat_data_t heartbeat_server_data_src;
pthread_mutex_t heartbeat_queue_mutex;

/******************************************************************************************
*					FUNCTION DEFINITION
********************************************************************************************/
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

		//send heartbeat
			if(heartbeat_flag.heartbeat_server_flag == 1){
			heartbeat_server_data_src.timestamp = record_time(); 
			heartbeat_server_data_src.log_level = 1;
			strcpy(heartbeat_server_data_src.source_ID,"SERVER_TASK ALIVE");
			pthread_mutex_lock(&heartbeat_queue_mutex);
			if(mq_send(mqdes_heartbeat,(char *)&heartbeat_server_data_src,sizeof(heartbeat_data_t),0)==-1){
				perror("Sending server heartbeat to main unsuccessfull");
			}
			pthread_mutex_unlock(&heartbeat_queue_mutex);

			heartbeat_flag.heartbeat_server_flag =0;


		}
		memset(str,0,sizeof(str));
		if((recv_stat = recv(sock_stat, str,sizeof(str),0) < 0))
		{
			perror("read error");
			socket_flag = 0;
			break;
		}
		else{


			//RxBuf[0] = str;

			if(strcmp(str,"1") == 0)
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

			else if(strcmp(str,"2") == 0)
			{
				printf("\n\rtemp func received ");
				/*call temp_read()*/
				client_temperature_type_request = REQUEST_KELVIN;
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
			
			else if(strcmp(str,"3") == 0)
			{
				printf("\n\rtemp func received ");
				/*call temp_read()*/
				client_temperature_type_request = REQUEST_FAHRENHEIT;
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

			else if(strcmp(str,"4") == 0)
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

			else if(strcmp(str,"5") == 0)
			{
				printf("LED func received \n");
				/*System State func()*/
				led_on(RED_LED);
				led_on(YELLOW_LED);
				led_on(BLUE_LED);
				led_on(GREEN_LED);
			}	

			else if(strcmp(str,"6") == 0)
			{
				printf("LED func received \n");
				/*System State func()*/
				led_off(RED_LED);
				led_off(YELLOW_LED);
				led_off(BLUE_LED);
				led_off(GREEN_LED);
			}


			else if(strcmp(str,"7") == 0)
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



