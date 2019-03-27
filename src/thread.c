/********************************************************************************************
 *					FILENAME: thread.c
 **********************************************************************************************/
/* Title:thread.c
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

#include"main.h" 

/**************************************************************************************
 *					     MACROS
 ****************************************************************************************/

/**************************************************************************************
 *					     GLOBAL VARIABLES
 ****************************************************************************************/
/*bool client_get_temp_flag;
  bool client_get_system_stat_flag;
  bool client_get_lux_flag;
 */
mqd_t mqdes_server;
client_request_t client_request;
request_cmd_t client_temperature_type_request ;
client_data_t client_data;
logger_flag_t logger_flag;
log_t log_temp_data_src;
log_t log_light_data_src;
pthread_mutex_t logger_queue_mutex;
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

		temperature_data = get_temperature(client_temperature_type_request);
		//sleep(1);
		if(client_request.client_get_temp_flag == 1){
			//send message through queue to server task
			//printf("\n\rTemperature data called from client: %lf",temperature_data);
			strcpy(client_data.sensor_string,"Temperature value:");
			client_data.sensor_data = temperature_data;	
			if(mq_send(mqdes_server,(char *)&client_data,sizeof(client_data_t),0)==-1){
				perror("Sending temperature value to server unsuccessfull");
			}
			client_request.client_get_temp_flag =0;
		}
		if(logger_flag.log_temp_sensor_flag == 1){
			log_temp_data_src.timestamp = record_time(); 
			log_temp_data_src.log_level = 1;
			strcpy(log_temp_data_src.source_ID,"Temp value:");
			log_temp_data_src.sensor_data = temperature_data;	
			pthread_mutex_lock(&logger_queue_mutex);
			if(mq_send(mqdes_logger,(char *)&log_temp_data_src,sizeof(log_t),0)==-1){
				perror("Sending temperature value to logger unsuccessfull");
			}
			pthread_mutex_unlock(&logger_queue_mutex);

			logger_flag.log_temp_sensor_flag =0;
				

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

	
		lux_data = read_lux(); 

		//client_get_lux_flag = 1;
		if(client_request.client_get_lux_flag == 1){
			//send message through queue to server task

			//	printf("\n\rLight data called from client:%lf",lux_data);
			strcpy(client_data.sensor_string,"Lux value:");
			client_data.sensor_data = lux_data;	
			if(mq_send(mqdes_server,(char *)&client_data,sizeof(client_data_t),0)==-1){
				perror("Sending light value to server unsuccessfull");
			}


			client_request.client_get_lux_flag = 0;

		}
		if(logger_flag.log_light_sensor_flag == 1){
			log_light_data_src.timestamp = record_time(); 
			log_light_data_src.log_level = 2;
			strcpy(log_light_data_src.source_ID,"Light value:");
			log_light_data_src.sensor_data = lux_data;	
			pthread_mutex_lock(&logger_queue_mutex);
			if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
				perror("Sending light value to logger unsuccessfull");
			}
			logger_flag.log_light_sensor_flag =0;
			pthread_mutex_unlock(&logger_queue_mutex);


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
	log_t log_temp_data;
	FILE *log_file = NULL;
	while(1){
	//	pthread_mutex_lock(&logger_queue_mutex);
		if(mq_receive(mqdes_logger,(char *)&log_temp_data,sizeof(log_t),NULL) ==-1){
			perror("Reception of data from temp sensor thread unsuccessfull");	
		}
		log_file = fopen("log.txt","a+");
	//	printf("\n\r[%lf] [%d] [%s] [%lf]",log_temp_data.timestamp,log_temp_data.log_level,log_temp_data.source_ID,log_temp_data.sensor_data);
	//	pthread_mutex_unlock(&logger_queue_mutex);
			
	 LOG(log_file,log_temp_data.timestamp,log_temp_data.log_level,log_temp_data.source_ID,log_temp_data.sensor_data);
		fclose(log_file);
	
}
}






