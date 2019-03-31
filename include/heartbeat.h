/********************************************************************************************
*					FILENAME: heartbeat.h
**********************************************************************************************/
/* Title: heartbeat.h
 * Brief: Responsible for providing various helper function to support heartbeat functionality
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: http://www.
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#ifndef HEARTBEAT_H_
#define HEARTBEAT_H_

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
/**************************************************************************************
*					     MACROS
****************************************************************************************/


typedef struct{
	double timestamp;
	int log_level;
	uint8_t  source_ID[20];
	double sensor_data;
	bool error_flag;
}heartbeat_data_t;

typedef struct{
	bool heartbeat_temp_sensor_flag;
	bool heartbeat_light_sensor_flag;
	bool heartbeat_logger_flag;
	bool heartbeat_server_flag;
}heartbeat_flag_t;

/**************************************************************************************
*					GLOBAL VARIABLES
****************************************************************************************/

/**************************************************************************************
*					FUNCTION PROTOTYPE
***************************************************************************************/

#endif /* HEARTBEAT_H_ */

