#ifndef TIMER_H_
#define TIMER_H_
/********************************************************************************************
*					FILENAME: timer.h
**********************************************************************************************/
/* Title: timer.c
 * Brief: Responsible for providing various helper function needed for logger and heartbeat
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: Professor's slides and notes 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/

#include <signal.h>
#include <time.h>
#include <stdio.h>
#include<stdbool.h>

/****************************************************************************************
*				     MACROS AND ENUMS
*****************************************************************************************/
#define SEC_TO_MILLISEC		(1000.0)
#define NANOSEC_TO_MILLISEC	(1000000.0)

/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/
//Flag variables
extern int log_timer_flag;
extern int heartbeat_timer_flag;
// Logger timer id
timer_t log_timer_id;
//Heartbeat timer id
timer_t heartbeat_timer_id;
//timespec struct for giving interval values
struct itimerspec timer_setting;
struct sigevent signal_specification;
/***************************************************************************************
*				FUNCTION PROTOTYPE
*****************************************************************************************/
/***********************************************************************************************
 * @brief logger  timer handler
 *
 * Handler that executes periodically to generate logging interval
 * @param null
 *
 * @return null
 *********************************************************************************************/
void log_timer_handler(int num);
/***********************************************************************************************
 * @brief heartbeat timer handler
 *
 * Handler that executes periodically to generate heartbeat interval
 * @param null
 *
 * @return null
 *********************************************************************************************/
void heartbeat_timer_handler(int num);
/***********************************************************************************************
 * @brief Create log timer
 *
 * Responsible for creating log timer which expires periodically to collect sensor information an
 * nd socket status that is logged into log file
 * @param null
 *
 * @return bool: Indicates whether intiialisation was successfull or not
 *********************************************************************************************/
bool create_log_timer();

/***********************************************************************************************
 * @brief Create heartbeat timer
 *
 * Responsible for generating heartbeat for each of the four thread
 * @param null
 *
 * @return bool: Indicates whether intiialisation was successfull or not
 *********************************************************************************************/
bool create_heartbeat_timer();
/***********************************************************************************************
 * @brief Record the timestamp value
 *
 * Record the timestamp value using clock_get_time function
 * @param null
 *
 * @return double: timestamp value
 *********************************************************************************************/
double record_time();

#endif //TIMER_H_
