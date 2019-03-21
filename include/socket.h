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


/***************************************************************************************
*					MACROS AND ENUMS
****************************************************************************************/
#define	PORT_NUM	(7000)


/****************************************************************************************
* 					GLOBAL VARIABLES
*****************************************************************************************/
char *RxBuf[10] = {0};
int socket_fd;
int check_stat;
int sig_flag = 0;
int sock_stat;




#endif	SRC_SOCKET_H_
