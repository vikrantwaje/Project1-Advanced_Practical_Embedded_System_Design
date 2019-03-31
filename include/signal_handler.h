#ifndef SIGNAL_HANDLER_H_
#define SIGNAL_HANDLER_H_
/********************************************************************************************
*					FILENAME: signal_handler.h
**********************************************************************************************/
/* Title: signal_handler.h
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

#include<stdio.h>
#include<signal.h>
#include<stdbool.h> 
#include<stdint.h>

/**************************************************************************************
*					    GLOBAL VARIABLES
****************************************************************************************/
struct sigaction user_defined;
extern bool system_shutdown_flag;
extern bool system_shutdown_main_flag;
/**************************************************************************************
*					FUNCTION DEFINITION
***************************************************************************************/
/***********************************************************************************************
 * @brief system shutdown handler
 *
 * Handler invoked when user presses CTRL + C
 * @param num: Checks type of signal
 *
 * @return null
 *********************************************************************************************/
void system_shutdown_handler(int num);
/***********************************************************************************************
* @brief Initialise system shutdown handler
*
* Initialising parameter for system shutdown handler
* @param null
*
* @return null
*********************************************************************************************/

void signal_handler_init();

#endif
