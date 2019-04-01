/********************************************************************************************
*					FILENAME: signal_handler.c
**********************************************************************************************/
/* Title: signal_handler.c
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

#include"signal_handler.h" 

/**************************************************************************************
*					    GLOBAL VARIABLES
****************************************************************************************/
struct sigaction user_defined;
bool system_shutdown_flag;
bool system_shutdown_main_flag;
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
void system_shutdown_handler(int num){
	if(num == SIGINT){
	printf("\n\rSystem shutdown activated. Cleaning up the resources............");
	system_shutdown_flag = 1;
	system_shutdown_main_flag =1;
}

}
/***********************************************************************************************
* @brief Initialise system shutdown handler
*
* Initialising parameter for system shutdown handler
* @param null
*
* @return null
*********************************************************************************************/

void signal_handler_init(){
	user_defined.sa_flags = 0;
	user_defined.sa_handler = system_shutdown_handler;
	sigemptyset(&user_defined.sa_mask);
	sigaction(SIGINT,&user_defined,NULL);


}

