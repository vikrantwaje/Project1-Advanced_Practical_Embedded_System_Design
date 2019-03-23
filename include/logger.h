/********************************************************************************************
*					FILENAME: logger.h
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
#ifndef LOGGER_H_
#define LOGGER_H_

#include<stdio.h>
#include<stdint.h>
/**************************************************************************************
*					     MACROS
****************************************************************************************/



#define LOG(time) fprintf(fptr,"\n%c%c%lf%c%s %s %lu ",'\n','[',time,']'," Entering thread,","pid = ",pthread_self());	//Log into the file


typedef struct{
	double timestamp;
	int log_level;
	uint8_t * source_ID;
	double data;
}log_t;


/**************************************************************************************
*					GLOBAL VARIABLES
****************************************************************************************/

/**************************************************************************************
*					FUNCTION PROTOTYPE
***************************************************************************************/



#endif /* LOGGER_H_ */

