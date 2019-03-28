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

void open_message_queue_server(mqd_t *mqdes, struct mq_attr * attribute){
	attribute->mq_maxmsg= 10;
	attribute->mq_msgsize = sizeof(client_data_t);
	*mqdes = mq_open("/msgqueue1",O_CREAT|O_RDWR,0666,attribute); 
	if(*mqdes == -1){
		perror("Failed to open message queue fro server");

	}
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


void close_message_queue_server(mqd_t *mqdes){
	if(mq_close(*mqdes)==-1){
		perror("Message queue for server failed to close");
	}

	if(mq_unlink("/msgqueue1")<0){
		perror("Message queue for server failed to unlinked");
	}

}

/******************************************************************************************
 * @brief Open message queue for logger
 *
 * Initialises a message queue that can be used to transfer logs periodically to logger task
 *
 * @param mqdes: Message queue descriptor
 * @param attribute: Attribute of message queue 
 *
 * @return null
 ********************************************************************************************/

void open_message_queue_logger(mqd_t *mqdes, struct mq_attr * attribute){
	attribute->mq_maxmsg= 10;
	attribute->mq_msgsize = sizeof(log_t);
	*mqdes = mq_open("/msgqueue2",O_CREAT|O_RDWR,0666,attribute); 
	if(*mqdes == -1){
		perror("Failed to open message queue for logger");

	}
}

/*******************************************************************************************
 * @brief Close message queue for logger
 *
 * Unlinks and Closes  message queue that was used to transfer sensor values to logger task periodically
 *
 * @param mqdes: Message queue descriptor
 * @param attribute: Attribute of message queue 
 *
 * @return null
 ********************************************************************************************/


void close_message_queue_logger(mqd_t *mqdes){
	if(mq_close(*mqdes)==-1){
		perror("Message queue for logger failed to close");
	}

	if(mq_unlink("/msgqueue2")<0){
		perror("Message queue for logger failed to unlinked");
	}

}

/***************************************************************************************

 * @brief Open message queue for logging heartbeat to main task
 *
 * Initialises a message queue that can be used to transfer keep alive notification to main task
 *
 * @param mqdes: Message queue descriptor
 * @param attribute: Attribute of message queue 
 *
 * @return null
 ********************************************************************************************/

void open_message_queue_heartbeat(mqd_t *mqdes, struct mq_attr * attribute){
	attribute->mq_maxmsg= 10;
	attribute->mq_msgsize = sizeof(heartbeat_data_t);
	*mqdes = mq_open("/msgqueue3",O_CREAT|O_RDWR,0666,attribute); 
	if(*mqdes == -1){
		perror("Failed to open message queue for logging heartbeat");

	}
}


/*******************************************************************************************
 * @brief Close message queue for logger
 *
 * Unlinks and Closes  message queue that was used to transfer sensor values to logger task periodically
 *
 * @param mqdes: Message queue descriptor
 * @param attribute: Attribute of message queue 
 *
 * @return null
 ********************************************************************************************/


void close_message_queue_heartbeat(mqd_t *mqdes){
	if(mq_close(*mqdes)==-1){
		perror("Message queue for heartbeat failed to close");
	}

	if(mq_unlink("/msgqueue3")<0){
		perror("Message queue for heartbeat failed to unlinked");
	}

}


