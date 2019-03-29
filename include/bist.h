/********************************************************************************************
*					FILENAME: bist.h
**********************************************************************************************/
/* Title: bist.h
 * Brief: Responsible for providing helper function for built in self test
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: http://www.
 * 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#ifndef BIST_H_
#define BIST_H_

#include "temp_sensor.h"
#include "light_sensor.h"
#include "logger.h"
#include "ipc.h"
#include"i2c_status.h"
#include"thread.h"
#include<pthread.h>
/**************************************************************************************
*					     MACROS
****************************************************************************************/
					

/**************************************************************************************
*					FUNCTION PROTOTYPE
***************************************************************************************/
void built_in_self_test();

#endif 
