/********************************************************************************************
*					FILENAME: thread.h
**********************************************************************************************/
/* Title:thread.h
 * Brief: Responsible for providing callback function for the four threads created in main function
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
#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

/**************************************************************************************
*					     MACROS
****************************************************************************************/

/**************************************************************************************
*					GLOBAL VARIABLES
****************************************************************************************/
extern pthread_t thread1, thread2, thread3, thread4;
/**************************************************************************************
*					FUNCTION PROTOTYPE
***************************************************************************************/

/*******************************************************************************************
 * @brief Socket thread
 *
 * Waits for a connection initiated by an external client.
 * Once connected, accepts commands from client and acts accordingly.
 * If clients commands the connection to "close", server thread disconnects,
 * closes the socket connection and waits for a new connection.
 *
 * @param null
 *
 * @return null
 ********************************************************************************************/
void *socket_thread( void*);


/***********************************************************************************************
 * @brief Temperature thread
 *
 * Get the temperature value periodically from temperature sensor and logs 
 * into file opened by logger thread
 *
 * @param null
 *
 * @return null
 *********************************************************************************************/

void *temperature_thread( void*);



/***********************************************************************************************
 * @brief light sensor thread
 *
 * Get the LUX values from light sensor attached using I2C interface and report it periodically t * o logger thread
 *
 * @param null
 *
 * @return null
 *********************************************************************************************/

void *light_sensor_thread( void*);



/***********************************************************************************************
 * @brief logger thread
 *
 * Log the values of temperature, light sensor and socket status in log file created by logger task 
 * into file opened by logger thread
 *
 * @param null
 *
 * @return null
 *********************************************************************************************/

 void *logger_thread( void*);





#endif /* THREAD_H_ */

