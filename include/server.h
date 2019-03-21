#ifndef SRC_SOCKET_H_
#define	SRC_SOCKET_H_
/********************************************************************************************
*					FILENAME: socket.h
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

/***************************************************************************************
*					MACROS AND ENUMS
****************************************************************************************/
#define	PORT_NUM	(7000)
#define	LOG_FILE_NAME	"socketlog.txt"

/****************************************************************************************
* 					GLOBAL VARIABLES
*****************************************************************************************/
char *RxBuf[10] = {0};
int socket_fd;
int check_stat;
int sig_flag = 0;
int sock_stat;

/****************************************************************************************
* 					FUNCTION PROTOTYPES
*****************************************************************************************/
/*******************************************************************************************
 * @brief Socket Connection Routines
 *
 * Call the socket(), bind(), listen() and accept() and returns 1 on successful connection
 * with an external client
 
 * @param null
 *
 * @return 0 if error, 1 if success
 ********************************************************************************************/
int socket_connect(void);


#endif	SRC_SOCKET_H_
