/********************************************************************************************
*					FILENAME: main.h
**********************************************************************************************/
/* Title: main.h
 * Brief: Responsible for creating threads, joining them and initiating built in self test
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
#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "thread.h"
#include"timer.h"
#include"temp_sensor.h"
#include"light_sensor.h"
#include"logger.h"
#include"synchronization.h"
#include"server.h"
#include"ipc.h"
#include"led.h"
#include"bist.h"
/**************************************************************************************
*					     MACROS
****************************************************************************************/

/**************************************************************************************
*					GLOBAL VARIABLES
****************************************************************************************/


/**************************************************************************************
*					ENUM FOR ERRORS
***************************************************************************************/
typedef enum{

	PTHREAD_SUCCESS, PTHREAD_FAIL	
}return_type_t;

/**************************************************************************************
*					FUNCTION PROTOTYPE
***************************************************************************************/
return_type_t main_func();



#endif /* SRC_MAIN_H_ */
