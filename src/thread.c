/********************************************************************************************
 *					FILENAME: thread.c
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

#include"main.h" 

/**************************************************************************************
 *					     MACROS
 ****************************************************************************************/

/**************************************************************************************
 *					     GLOBAL VARIABLES
 ****************************************************************************************/
bool client_get_temp_flag;
bool client_get_system_stat_flag;
bool client_get_lux_flag;
//request_cmd_t client_request_temperature_type = REQUEST_CELSIUS;	//default reuqest celsius

/**************************************************************************************
 *					FUNCTION DEFINITION
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
void *socket_thread( void* arg){
	int ret_status = server_establish();
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

void *temperature_thread( void* arg){
	double temperature_data = 0; 
	while(1){
		temperature_data = get_temperature(REQUEST_CELSIUS);
		//sleep(1);
		if(client_get_temp_flag == 1){
	//send message through queue to server task
		printf("\n\rTemperature data called from client: %lf",temperature_data);	
		client_get_temp_flag =0;
		}
	}
}




/***********************************************************************************************
 * @brief light sensor thread
 *
 * Get the LUX values from light sensor attached using I2C interface and report it periodically t * o logger thread
 *
 * @param null
 *
 * @return null
 *********************************************************************************************/

void *light_sensor_thread( void* arg){
	double lux_data = 0;
	while(1){
		//client_get_lux_flag = 1;
		if(client_get_lux_flag == 1){
		//send message through queue to server task

		lux_data = read_lux(); 
		printf("\n\rLight data called from client:%lf",lux_data);
	

		client_get_lux_flag = 0;

}
	}

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

void *logger_thread( void* arg){
/*	while(1)
	printf("\n\rHi from logger thread");
*/}






