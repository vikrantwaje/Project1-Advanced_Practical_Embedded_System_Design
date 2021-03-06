#ifndef SRC_IPC_H_
#define	SRC_IPC_H_
/********************************************************************************************
*					FILENAME: ipc.h
**********************************************************************************************/
/* Title: ipc.h
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
***************************************************************************/

#include<stdint.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<mqueue.h>
#include<signal.h>
#include<string.h>
#include<stdio.h>
#include"logger.h"
#include"heartbeat.h"
#include"synchronization.h"
/***************************************************************************************
*					MACROS AND ENUMS
***************************************************************************/

typedef struct{
	char sensor_string[40];
	double sensor_data;

}client_data_t;

/*******************************************************************************************
*					GLOBAL VARIABLES
*******************************************************************************************/
extern mqd_t mqdes_server;
extern mqd_t mqdes_logger;
extern mqd_t mqdes_heartbeat;
/*******************************************************************************************
*					FUNCTION DEFINITION
*******************************************************************************************/

void open_message_queue_server(mqd_t *mqdes, struct mq_attr * attribute);
void close_message_queue_server(mqd_t *mqdes);
void open_message_queue_logger(mqd_t *mqdes, struct mq_attr * attribute);
void close_message_queue_logger(mqd_t *mqdes);
void open_message_queue_heartbeat(mqd_t *mqdes, struct mq_attr * attribute);
void close_message_queue_heartbeat(mqd_t *mqdes);

#endif //SRC_IPC_H
