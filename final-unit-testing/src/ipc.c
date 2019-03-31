/********************************************************************************************
 *					FILENAME: ipc.c
 **********************************************************************************************/
/* Title: ipc.c
 * Brief: Responsible for implementing various helper function that helps in setting up interthread communication 
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1
 *
 * 
 * 
 * */
/****************************************************************************************
 *					HEADER FILE SECTION
 *****************************************************************************************/


#include"ipc.h"
#include<mqueue.h>

/**************************************************************************************
 *					     MACROS
 ****************************************************************************************/

/**************************************************************************************
 *					     GLOBAL VARIABLES
 ****************************************************************************************/


/**************************************************************************************
 *					     FUNCTION DEFINITION
/ ****************************************************************************************/

 /* @brief Open message queue for server
 *
 * Initialises a message queue that can be used to transfer sensor values to server when client requests it
 *
 * @param mqdes: Message queue descriptor
 * @param attribute: Attribute of message queue 
 *
 * @return null
 ********************************************************************************************/

ipc_return_t open_message_queue_server(mqd_t *mqdes, struct mq_attr * attribute){
	attribute->mq_maxmsg= 10;
	attribute->mq_msgsize = sizeof(client_data_t);
	*mqdes = mq_open("/msgqueue4",O_CREAT|O_RDWR,0666,attribute); 
	if(*mqdes == -1){
		//perror("Failed to open message queue fro server");
		return MQ_FAIL;

	}
	return MQ_SUCCESS;
}


/*******************************************************************************************
 * @brief Close message queue for server
 *
 * Unlinks and Closes  message queue that was used to transfer sensor values to server when client requests it
 *
 * @param mqdes: Message queue descriptor
 * @param attribute: Attribute of message queue 
 *
 * @return null
 ********************************************************************************************/


ipc_return_t close_message_queue_server(mqd_t *mqdes){
	if(mq_close(*mqdes)==-1){
		return MQ_FAIL;
	}

	if(mq_unlink("/msgqueue4")<0){
		return MQ_FAIL;
	}
return MQ_SUCCESS;
}
