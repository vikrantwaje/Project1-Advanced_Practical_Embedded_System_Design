/********************************************************************************************
*					FILENAME: main.c
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
#include "main.h"


/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/
//Flag to be set in log handler
int log_timer_flag;
//Flag to be set in heartbeat handler
int heartbeat_timer_flag;


/***********************************************************************************************
 * @brief light sensor thread
 *
 * Get the LUX values from light sensor attached using I2C interface and report it periodically t * o logger thread
 *
 * @param null
 *
 * @return null
 *********************************************************************************************/
void *light_sensor_thread(){

	printf("\n\rlight sensor thread");
	while(1);
}

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
void *logger_thread(){

	printf("\n\rLogger thread");
	while(1);
}
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

void *temperature_thread(){

	printf("\n\rTemperature thread");
	while(1);

}
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
void *socket_thread()
{
	printf("\n\rServer thread");
}

/*******************************************************************************************
 * @brief Main function
 *
 * Responsible for creating four threads for execution namely light sensor thread, temperature th * read, logger thread and socket thread
 *
 * @param null
 *
 * @return null
 ********************************************************************************************/
 int main()
{
	pthread_t thread1, thread2, thread3, thread4;

	int ret_status;

	/*Initialising timer for logger task*/
	ret_status =create_log_timer();
	if(ret_status !=0){
	fprintf( stderr, "log timer not created , Error Code: %d\n", ret_status);
	}

	/*Initialise timer for heartbeat task*/
	ret_status =create_heartbeat_timer();
	if(ret_status !=0){
	fprintf( stderr, "heartbeat timer not created , Error Code: %d\n", ret_status);
	}

	/* Socket thread creation*/
	ret_status = pthread_create( &thread1, NULL, socket_thread,0);
	if( ret_status )
	{
		fprintf( stderr, "socket_thread not created, Error Code: %d\n", ret_status);
		return 0;
	}
	
	/*Temperature thread creation*/
	ret_status = pthread_create( &thread2, NULL, temperature_thread,0);
	if( ret_status )
	{
		fprintf( stderr, "temperature_thread not created, Error Code: %d\n", ret_status);
		return 0;
	}

	/*light sensor thread creation*/
	ret_status = pthread_create( &thread3, NULL, light_sensor_thread,0);
	if( ret_status )
	{
		fprintf( stderr, "light_sensor_thread not created, Error Code: %d\n", ret_status);
		return 0;
	}
	
	/*logger thread creation*/
	ret_status = pthread_create( &thread4, NULL, logger_thread,0);

	if( ret_status )
	{
		fprintf( stderr, "logger_thread not created, Error Code: %d\n", ret_status);
		return 0;
	}

	/*Socket thread join*/
	ret_status = pthread_join( thread1, NULL);
	if(ret_status){
		fprintf( stderr, "socket thread not joined successfully, Error Code: %d\n", ret_status);
	}
	/*Temperature thread join*/
	ret_status =	pthread_join( thread2, NULL);
	if(ret_status){
		fprintf( stderr, "temperature_thread not joined successfully, Error Code: %d\n", ret_status);
	}

	/*Light sensor thread join*/
	ret_status =	pthread_join( thread3, NULL);
	if(ret_status){
		fprintf( stderr, "light_sensor thread not joined successfully, Error Code: %d\n", ret_status);
	}

	/*Logger thread join*/
	ret_status =	pthread_join( thread4, NULL);
	if(ret_status){
		fprintf( stderr, "logger thread not joined successfully, Error Code: %d\n", ret_status);
	}	printf("Main Thread Exited Successfully \n");

	return 1;
}


