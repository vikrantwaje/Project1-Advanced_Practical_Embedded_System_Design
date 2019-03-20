/********************************************************************************************
*					FILENAME: timer.c
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
#include "timer.h"

/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/
int log_timer_flag;
int heartbeat_timer_flag;

/***************************************************************************************
*				FUNCTION DEFINITION
*****************************************************************************************/
/***********************************************************************************************
 * @brief logger  timer handler
 *
 * Handler that executes periodically to generate logging interval
 * @param null
 *
 * @return null
 *********************************************************************************************/
void log_timer_handler(int num){

	log_timer_flag = 1;
	printf("\n\rHi logger");
}
/***********************************************************************************************
 * @brief heartbeat timer handler
 *
 * Handler that executes periodically to generate heartbeat interval
 * @param null
 *
 * @return null
 *********************************************************************************************/
void heartbeat_timer_handler(int num){

	heartbeat_timer_flag = 1;
	printf("\n\rHi heartbeat");
}
/***********************************************************************************************
 * @brief Create log timer
 *
 * Responsible for creating log timer which expires periodically to collect sensor information an
 * nd socket status that is logged into log file
 * @param null
 *
 * @return bool: Indicates whether intiialisation was successfull or novoidt
 *********************************************************************************************/
bool create_log_timer(){
	signal_specification.sigev_notify = SIGEV_THREAD;
	signal_specification.sigev_notify_function = &log_timer_handler;
	signal_specification.sigev_value.sival_ptr = "State collection timer";
	timer_create(CLOCK_REALTIME,&signal_specification,&log_timer_id);
	timer_setting.it_value.tv_sec =1;
	timer_setting.it_value.tv_nsec = 0;
	timer_setting.it_interval.tv_sec = 0;
	timer_setting.it_interval.tv_nsec = 100000000;
	timer_settime(log_timer_id,0,&timer_setting,NULL);
	return 0;
}

/***********************************************************************************************
 * @brief Create heartbeat timer
 *
 * Responsible for generating heartbeat for each of the four thread
 * @param null
 *
 * @return bool: Indicates whether intiialisation was successfull or not
 *********************************************************************************************/
bool create_heartbeat_timer(){

	signal_specification.sigev_notify = SIGEV_THREAD;
	signal_specification.sigev_notify_function = &heartbeat_timer_handler;
	signal_specification.sigev_value.sival_ptr = "Heartbeat timer";
	timer_create(CLOCK_REALTIME,&signal_specification,&heartbeat_timer_id);
	timer_setting.it_value.tv_sec =1;
	timer_setting.it_value.tv_nsec = 0;
	timer_setting.it_interval.tv_sec = 0;
	timer_setting.it_interval.tv_nsec = 50000000;
	timer_settime(heartbeat_timer_id,0,&timer_setting,NULL);
	return 0;
}


