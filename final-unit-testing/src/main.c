/********************************************************************************************
 *					FILENAME: main.c
 **********************************************************************************************/
/* Title: main.c
 * Brief: Responsible for creating threads, joining them and initiating built in self test
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
#include "main.h"
#include "thread.h"


/*******************************************************************************************
 * @brief Main function
 *
 * Responsible for creating four threads for execution namely light sensor thread, temperature th * read, logger thread and socket thread
 *
 * @param null
 *
 * @return null
 ********************************************************************************************/
return_type_t main_func()
{
	int ret_status;
	/*Socket thread join*/
	//pthread_t thread1, thread2, thread3, thread4;

	ret_status = pthread_create( &thread1, NULL, socket_thread,0);
	if( ret_status )
	{
	return PTHREAD_FAIL;
	}

	/*Temperature thread creation*/
	ret_status = pthread_create( &thread2, NULL, temperature_thread,0);
	if( ret_status )
	{
		return PTHREAD_FAIL;
	}

	/*light sensor thread creation*/
	ret_status = pthread_create( &thread3, NULL, light_sensor_thread,0);
	if( ret_status )
	{
		return PTHREAD_FAIL;
	}



	/*logger thread creation*/
	ret_status = pthread_create( &thread4, NULL, logger_thread,0);

	if( ret_status )
	{
	return PTHREAD_FAIL;
	}


	ret_status = pthread_join( thread1, NULL);
	if(ret_status){
		//fprintf( stderr, "socket thread not joined successfully, Error Code: %d\n", ret_status);
	//	printf("Failed here");
		return PTHREAD_FAIL;
	}
	/*Temperature thread join*/
	ret_status =	pthread_join( thread2, NULL);
	if(ret_status){
		//fprintf( stderr, "temperature_thread not joined successfully, Error Code: %d\n", ret_status);
		return PTHREAD_FAIL;	
	}

//	Light sensor thread join
	ret_status =	pthread_join( thread3, NULL);
	if(ret_status){
		//fprintf( stderr, "light_sensor thread not joined successfully, Error Code: %d\n", ret_status);
		return PTHREAD_FAIL;
	}

	/*Logger thread join*/
	ret_status =	pthread_join( thread4, NULL);
	if(ret_status){
		//fprintf( stderr, "logger thread not joined successfully, Error Code: %d\n", ret_status);
		return PTHREAD_FAIL;
	}
	//printf("Main Thread Exited Successfully \n");


	return PTHREAD_SUCCESS;
}


void *socket_thread( void* arg){
	//mock thread
}

void *temperature_thread( void* arg)
{
	//mock thread	
}
void *light_sensor_thread( void* arg)
{
	//mocj thread	
}

void *logger_thread( void* arg)
{
	//mock thread
}
