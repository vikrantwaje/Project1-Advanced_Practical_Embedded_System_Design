/********************************************************************************************
*					FILENAME: logger.h
**********************************************************************************************/
/* Title: logger.h
 * Brief: Responsible for providing various helper function to support logger functionality
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
#ifndef LOGGER_H_
#define LOGGER_H_

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
/**************************************************************************************
*					     MACROS
****************************************************************************************/



#define LOG(fptr,time,log_level,source_id,sensor_value) fprintf(fptr,"\n %c%lf%c [%s]: loglevel:%d sensor value: %lf ",'[',time,']',source_id,log_level,sensor_value);	//Log into the file


typedef struct{
	double timestamp;
	int log_level;
	uint8_t  source_ID[20];
	double sensor_data;
}log_t;

typedef struct{
	bool log_temp_sensor_flag;
	bool log_light_sensor_flag;
}logger_flag_t;

/**************************************************************************************
*					GLOBAL VARIABLES
****************************************************************************************/

/**************************************************************************************
*					FUNCTION PROTOTYPE
***************************************************************************************/



#endif /* LOGGER_H_ */

