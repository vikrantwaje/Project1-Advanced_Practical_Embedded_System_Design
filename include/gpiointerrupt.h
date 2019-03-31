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
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
/****************************************************************************************
 *					GLOBAL VARIABLES
 *****************************************************************************************/
extern int file_gpio;
extern char val[4];
struct pollfd filedes[1];
/****************************************************************************************
 *					MACRO
 *****************************************************************************************/
#define	NUM_FD	(1)
#define	TIMEOUT_MSECS	(3)



/****************************************************************************************
 *					FUNCTION PROTOTYPE 
 *****************************************************************************************/
/***********************************************************************************************
 * @brief IRQ handler
 *
 * Handler that returns state of GPIO pin 
 * @param null
 *
 * @return char
 *********************************************************************************************/
char IRQ_handler(void);


/***********************************************************************************************
 * @brief GPIO initilisation function
 *
 * Initialises GPIO pin
 * @param null
 *
 * @return int: error status
 *********************************************************************************************/
int GPIO_init(void);
#endif
