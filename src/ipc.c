/********************************************************************************************
 *					FILENAME: ipc.c
 **********************************************************************************************/
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
/****************************************************************************************
 *					HEADER FILE SECTION
 *****************************************************************************************/


#include"ipc.h"


/**************************************************************************************
 *					     MACROS
 ****************************************************************************************/

/**************************************************************************************
 *					     GLOBAL VARIABLES
 ****************************************************************************************/


/**************************************************************************************
 *					     FUNCTION DEFINITION
 ****************************************************************************************/


void open_message_queue_server(mqd_t *mqdes, struct mq_attr * attribute){
	attribute->mq_maxmsg= 10;
	attribute->mq_msgsize = sizeof(client_data_t);
	*mqdes = mq_open("/msgqueue1",O_CREAT|O_RDWR,0666,attribute); 
	if(*mqdes == -1){
		perror("Failed to open message queue fro server");

	}
}


void close_message_queue_server(mqd_t *mqdes){
	if(mq_close(*mqdes)==-1){
		perror("Message queue for server failed to close");
	}

	if(mq_unlink("/msgqueue1")<0){
		perror("Message queue for server failed to unlinked");
	}

}
