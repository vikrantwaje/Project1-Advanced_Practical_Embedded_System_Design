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


#include"Client.h"

client_data_t client_data;


int main()
{
	//	set_sig_handler();
	struct sockaddr_in server_addr;
	int send_data_len =0;
	char input_cmd[20];

	printf("Setting up the connection..............\n");

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd < 0)
	{
		perror("socket()");
		exit(1);
	}

	printf("creating socket .........................\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(7000);
	//server_addr.sin_addr.s_addr = inet_addr("128.138.189.197");
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.2");	
	//server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("Socket created successfull\n");
	/*If connection establishment failed, close socket*/
	if((connect(socket_fd,(struct sockaddr *)&server_addr, sizeof(server_addr))) < 0)
	{
		perror("Socket connect()");
		close(socket_fd);
		exit(1);
	}



	while(1){
		printf("\n\r********************************************************************************\
				\n\r*				BUFF CLIENT					   \
				\n\r***********************************************************************************\n\r");

		printf("\nEnter any of the following commands: \n");
		printf("\"1.Request temperature sensor values in Celsius\n");
		printf("\"2.Request temperature sensor values in Kelvin \n");
		printf("\"3.Request temperature sensor values in Fahrenheit\n");
		printf("\"4.Request light sensor values \n");
		printf("\"5.Request live system status \n");
		printf("\"6.Close connection \n\n");

	
		printf("\n\rEnter command here: ");

		scanf("\n%s", input_cmd);  //Blocking statement
		send_data_len = send(socket_fd, &input_cmd, 17, 0);
		printf("Command being sent = %s\n",input_cmd);
		if(strcmp(input_cmd,"6") ==0 ){
			close(socket_fd);
			printf("\n\rClosing socket");
			break;
		}
		if(recv(socket_fd,&client_data,sizeof(client_data_t), 0)<0){
			perror("Error in receiving structure for sensor. Try again!!");
		}
		else{
			
			printf("\n\r********************************************************************************\
				\n\r*				SERVER RESPONSE					   \
				\n\r***********************************************************************************\n\r");

			


			printf("%s %lf\n\n\n\n\n\n\n\n\r",client_data.sensor_string,client_data.sensor_data);
		}




	}
	return 0;

}



