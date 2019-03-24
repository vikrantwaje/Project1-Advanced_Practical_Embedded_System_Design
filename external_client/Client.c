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
//void set_sig_handler(void);
//long getMicrotime();


int main()
{
	//	set_sig_handler();
	struct sockaddr_in server_addr;
	char msg_buf[10];
	char msg_buf1[10];
	char RxBuf[10][10];
	int tan;
	int send_data_len;
	char temp_num[30];

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
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.2");	
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
		//	int msg_tx;
		char input_cmd[20];
		printf("\nEnter any of the following commands: \n");
		printf("\"request_temp_data_kelvin\": for receiving temperature sensor values in Kelvin\n");
		printf("\"request_temp_data_celcius\": for receiving temperature sensor values in Celcius \n");
		printf("\"request_temp_data_fahren\": for receiving temperature sensor values in Fahrenheit\n");
		printf("\"request_light_val\": for receiving light sensor values \n");
		printf("\"request_sys_state\": for receiving live system stat \n");
		printf("\"close\": for terminating connection \n\n");


		scanf("\n%s", input_cmd);  //Blocking statement
		//	int msg_txing[1];
		//	msg_txing[0] = msg_tx;
		send_data_len = send(socket_fd, &input_cmd, 17, 0);
		printf("Command being sent = %s\n",input_cmd);
		if(strcmp(input_cmd,"close") ==0 ){
			close(socket_fd);
			printf("\n\rClosing socket");
			break;
		}
		if(recv(socket_fd,&client_data,sizeof(client_data_t), 0)<0){
			perror("Error in receiving structure for sensor. Try again!!");
		}
		else{
			printf("%s %lf",client_data.sensor_string,client_data.sensor_data);
		}




	}
	return 0;

}



