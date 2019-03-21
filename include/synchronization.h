#ifndef SYNCHRONIZATION_H_
#define SYNCHRONIZATION_H_

/********************************************************************************************
*					FILENAME: synchronization.h
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
#include<pthread.h>
/***************************************************************************************
*					MACROS AND ENUMS
****************************************************************************************/


/**************************************************************************************
*				GLOBAL VARIABLES
****************************************************************************************/
extern pthread_mutex_t i2c_mutex;

#endif //SYNCHRONIZATION_H
