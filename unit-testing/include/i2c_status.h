#ifndef I2C_STATUS_H_
#define I2C_STATUS_H_

/********************************************************************************************
*					FILENAME: i2c_status.h
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

#include<stdint.h>

/***************************************************************************************
*					MACROS AND ENUMS
****************************************************************************************/
typedef enum{
	WRITE_REG_SUCCESS = 1, READ_REG_SUCCESS =2, WRITE_REG_FAIL=-1, READ_REG_FAIL=-2

}sensor_status_t;


/**************************************************************************************
*				GLOBAL VARIABLES
****************************************************************************************/

#endif //I2C_STATUS_H
