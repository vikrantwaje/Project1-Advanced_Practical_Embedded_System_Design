/********************************************************************************************
*					FILENAME: timer.c
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
#include "timer.h"

/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/
int log_timer_flag;
logger_flag_t logger_flag;
heartbeat_flag_t heartbeat_flag;
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

	//log_timer_flag = 1;
	logger_flag.log_temp_sensor_flag =1;
	logger_flag.log_light_sensor_flag =1;
//	printf("\n\rlogger");
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

	heartbeat_flag.heartbeat_temp_sensor_flag = 1;
	heartbeat_flag.heartbeat_light_sensor_flag = 1;
	heartbeat_flag.heartbeat_logger_flag =1;
	heartbeat_flag.heartbeat_server_flag =1;

//	printf("\n\rHi heartbeat");
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
	timer_setting.it_interval.tv_sec = 5;
	timer_setting.it_interval.tv_nsec = 0;
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
	timer_setting.it_interval.tv_sec =3 ;
	timer_setting.it_interval.tv_nsec = 0;
	timer_settime(heartbeat_timer_id,0,&timer_setting,NULL);
	return 0;
}
/***********************************************************************************************
 * @brief Record the timestamp value
 *
 * Responsible for recording the timestamp value
 * @param null
 *
 * @return double: returns the recorded time value
 *********************************************************************************************/
double record_time(){
	struct timespec timestamp;
	 clock_gettime(CLOCK_MONOTONIC,&timestamp);
	return((timestamp.tv_sec * (SEC_TO_MILLISEC))+ (timestamp.tv_nsec/(NANOSEC_TO_MILLISEC)) );	//Convert into milliseconds


}

