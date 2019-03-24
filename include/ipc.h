#ifndef SRC_IPC_H_
#define	SRC_IPC_H_
/********************************************************************************************
*					FILENAME: ipc.h
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
***************************************************************************/

#include<stdint.h>

/***************************************************************************************
*					MACROS AND ENUMS
***************************************************************************/

typedef struct{
	char sensor_string[40];
	double sensor_data;
}client_data_t;

#endif //SRC_IPC_H
