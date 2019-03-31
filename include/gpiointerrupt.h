#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_
/********************************************************************************************
 *					FILENAME: gpiointerrupt.h
 **********************************************************************************************/
/* Title: temp_sensor.h
 * Brief: Responsible for providing various helper function needed to communicate with temperature sensor
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 26, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: 
 * 
 * 
 * */
/****************************************************************************************
 *					HEADER FILE SECTION
 *****************************************************************************************/
#include <poll.h>
#include <fcntl.h>


/****************************************************************************************
 *					MACRO
 *****************************************************************************************/
#define	NUM_FD	(1)
#define	TIMEOUT_MSECS	(-1)
/****************************************************************************************
 *					FUNCTION PROTOTYPE 
 *****************************************************************************************/
int IRQ_handler(void);

#endif