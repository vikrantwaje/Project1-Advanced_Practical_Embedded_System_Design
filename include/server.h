#ifndef SRC_SERVER_H_
#define	SRC_SERVER_H_
/********************************************************************************************
*					FILENAME: server.h
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
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netdb.h>
#include<stdbool.h>
#include"temp_sensor.h"
#include"ipc.h"
/***************************************************************************************
*					MACROS AND ENUMS
****************************************************************************************/
#define	PORT_NUM	(7000)
#define	LOG_FILE_NAME	"socketlog.txt"
#define NO_OF_CLIENT	(5)

typedef enum{
	SOCKET_FAIL,REUSE_FAIL,BIND_FAIL,LISTEN_FAIL,ACCEPT_FAIL,SOCKET_CONNECT_SUCCESS,SOCKET_SETUP_SUCCESS
}server_response_t;




/****************************************************************************************
* 					GLOBAL VARIABLES
*****************************************************************************************/
char *RxBuf[10] ;
int socket_fd;
int check_stat;
int sig_flag ;
int sock_stat;
struct sockaddr_in server_addr;

typedef struct{
 bool client_get_temp_flag;
 bool client_get_lux_flag;
 bool client_get_system_stat_flag;
}client_request_t;

/****************************************************************************************
* 					FUNCTION PROTOTYPES
*****************************************************************************************/
/*******************************************************************************************
 * @brief Socket Listening Routines
 *
 * Call the listen() and accept() and returns 1 on successful connection
 * with an external client
 
 * @param null
 *
 * @return 0 if error, 1 if success
 ********************************************************************************************/
server_response_t socket_connect(void);


/*******************************************************************************************
 * @brief Socket Setup Routines
 *
 * Call the socket(), bind() and returns 1 on successful setup
 
 * @param null
 *
 * @return 0 if error, 1 if success
 ********************************************************************************************/
server_response_t socket_setup(void);


/*******************************************************************************************
 * @brief Communicate with external client
 *
 * After connecting with external client, receives command from client and call respective
 * function.

 * @param null
 *
 * @return 0 if error, 1 if success
 ********************************************************************************************/
int server_establish(void);

#endif //SRC_SERVER_H_
