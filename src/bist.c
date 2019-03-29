/********************************************************************************************
 *					FILENAME: bist.c
 **********************************************************************************************/
/* Title bist.c
 * Brief: Contains function that are used for built in self test
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: http://www.
 * 
 * 
 * */
/****************************************************************************************
 *					HEADER FILE SECTION
 *****************************************************************************************/
#include "bist.h"

/***************************************************************************************
 *					GLOBAL VARIABLE
 ****************************************************************************************/
pthread_t thread1, thread2, thread3, thread4;

/***************************************************************************************
 *				FUNCTION DEFINITION
 ***********************************************************************************************/
void built_in_self_test(){
	double return_data = 0.0;
	sensor_status_t sensor_stat;	
	uint8_t sensor_data = 0;
	int ret_status =0;
	// Check whether temperature sensor is working properly
	return_data = get_Thigh(REQUEST_KELVIN);
	if(return_data !=80.0){
		printf("\n\rTemperature sensor initialisation failed");
	}	
	return_data = get_Tlow(REQUEST_KELVIN);
	if(return_data !=75.0){
		printf("\n\rTemperature sensor initialisation failed");
	}


	// Check whether light sensor is working properly

	sensor_stat=light_sensor_power_on();
	if(sensor_stat != WRITE_REG_SUCCESS){
		printf("\n\rLight sensor initialisation failed");
	}
	sensor_data =read_identification_reg();	
	if(sensor_data != 0x05){
		printf("\n\rLight sensor initialisation failed");
	}

	//Check whether threads have been created successfully or not

	/* Socket thread creation*/
	ret_status = pthread_create( &thread1, NULL, socket_thread,0);
	if( ret_status )
	{
		fprintf( stderr, "socket_thread not created, Error Code: %d\n", ret_status);
		
	}

	/*Temperature thread creation*/
	ret_status = pthread_create( &thread2, NULL, temperature_thread,0);
	if( ret_status )
	{
		fprintf( stderr, "temperature_thread not created, Error Code: %d\n", ret_status);
	}

	/*light sensor thread creation*/
	ret_status = pthread_create( &thread3, NULL, light_sensor_thread,0);
	if( ret_status )
	{
		fprintf( stderr, "light_sensor_thread not created, Error Code: %d\n", ret_status);
	}



	/*logger thread creation*/
	ret_status = pthread_create( &thread4, NULL, logger_thread,0);

	if( ret_status )
	{
		fprintf( stderr, "logger_thread not created, Error Code: %d\n", ret_status);
	}

	// Notify success/no success to logger


}
