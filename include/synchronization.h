#ifndef SYNCHRONIZATION_H_
#define SYNCHRONIZATION_H_

/********************************************************************************************
*					FILENAME: synchronization.h
**********************************************************************************************/
/* Title: synchronization.h
* Brief: Responsible for providing various synchronization constructs
* Author: Tanmay Chaturvedi, Vikrant Waje
* Date Created: March 16, 2019
* Course: Advanced Embedded Software Development
* Project: 1
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
extern pthread_mutex_t logger_queue_mutex;
#endif //SYNCHRONIZATION_H
