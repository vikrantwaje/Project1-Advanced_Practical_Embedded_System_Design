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

pthread_t thread1,thread2,thread3,thread4;
mqd_t mqdes_server;
client_request_t client_request;
request_cmd_t client_temperature_type_request ;
client_data_t client_data;

mqd_t mqdes_logger;
logger_flag_t logger_flag;
log_t log_temp_data_src;
log_t log_light_data_src;
pthread_mutex_t logger_queue_mutex;

mqd_t mqdes_heartbeat;
heartbeat_flag_t heartbeat_flag;
heartbeat_data_t heartbeat_temp_data_src;
heartbeat_data_t heartbeat_light_data_src;
heartbeat_data_t heartbeat_logger_data_src;
pthread_mutex_t heartbeat_queue_mutex;

bool system_shutdown_flag;
bool temperature_shutdown_flag ;
bool light_shutdown_flag;
bool system_shutdown_main_flag;
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
	temperature_data = get_temperature(client_temperature_type_request); 
	while(1){
		if(system_shutdown_flag ==1){
			printf("\n\rClosing temperature thread");
			pthread_mutex_unlock(&logger_queue_mutex);
			pthread_mutex_unlock(&heartbeat_queue_mutex);
			pthread_exit(NULL);
		}
		else{
			//printf("\n\rTlow = %lf , Thigh =%lf",get_Tlow(client_temperature_type_request),get_Thigh(client_temperature_type_request));
			//sleep(1);
			if(client_request.client_get_temp_flag == 1){



				//send message through queue to server task
				//printf("\n\rTemperature data called from client: %lf",temperature_data);


				if(client_temperature_type_request == REQUEST_CELSIUS){	

					temperature_data = get_temperature(client_temperature_type_request);

					strcpy(client_data.sensor_string,"Temperature value in celsius:");

					strcpy(log_temp_data_src.source_ID,"EXT REQ(TEMP IN C)");	

					client_data.sensor_data = temperature_data;
					log_temp_data_src.sensor_data = temperature_data;

				}
				else if(client_temperature_type_request == REQUEST_KELVIN){	
					temperature_data = get_temperature(client_temperature_type_request);
					log_temp_data_src.sensor_data = temperature_data;
					client_data.sensor_data = temperature_data;
					strcpy(log_temp_data_src.source_ID,"EXT REQ(TEMP IN K)");	

					strcpy(client_data.sensor_string,"Temperature value in Kelvin:");
				}
				else /*(client_temperature_type_request == REQUEST_FAHRENHEIT)*/{	
					temperature_data = get_temperature(client_temperature_type_request);
					log_temp_data_src.sensor_data = temperature_data;
					client_data.sensor_data = temperature_data;

					strcpy(log_temp_data_src.source_ID,"EXT REQ(TEMP IN F)");

					strcpy(client_data.sensor_string,"Temperature value in Fahrenheit:");
				}


				if(mq_send(mqdes_server,(char *)&client_data,sizeof(client_data_t),0)==-1){
					perror("Sending temperature value to server unsuccessfull");
				}
				client_request.client_get_temp_flag =0;



				pthread_mutex_lock(&logger_queue_mutex);

				log_temp_data_src.timestamp = record_time();
				log_temp_data_src.log_level = 3;

				if(mq_send(mqdes_logger,(char *)&log_temp_data_src,sizeof(log_t),0)==-1){
					perror("Sending temperature value to logger unsuccessfull");
				}
				pthread_mutex_unlock(&logger_queue_mutex);




			}
			if(logger_flag.log_temp_sensor_flag == 1){
				temperature_data = get_temperature(client_temperature_type_request); 
				if(temperature_data == READ_TEMPERATURE_ERROR){	
					strcpy(log_temp_data_src.source_ID,"TEMPSENSOR_REMOVED");
					log_temp_data_src.timestamp = record_time(); 
					log_temp_data_src.log_level = 4;
					pthread_mutex_lock(&logger_queue_mutex);
					if(mq_send(mqdes_logger,(char *)&log_temp_data_src,sizeof(log_t),0)==-1){
						perror("Temperature sensor removed");
					}
					pthread_mutex_unlock(&logger_queue_mutex);



				}
				if(client_temperature_type_request == REQUEST_CELSIUS){
					strcpy(log_temp_data_src.source_ID,"TEMPERATURE(C)");

				}
				else if(client_temperature_type_request == REQUEST_FAHRENHEIT){
					strcpy(log_temp_data_src.source_ID,"TEMPERATURE(F)");
				}
				else if(client_temperature_type_request == REQUEST_KELVIN){
					strcpy(log_temp_data_src.source_ID,"TEMPERATURE(K)");
				}
				log_temp_data_src.sensor_data = temperature_data;	

				log_temp_data_src.timestamp = record_time(); 
				log_temp_data_src.log_level = 2;	
				pthread_mutex_lock(&logger_queue_mutex);
				if(mq_send(mqdes_logger,(char *)&log_temp_data_src,sizeof(log_t),0)==-1){
					perror("Sending temperature value to logger unsuccessfull");
				}
				pthread_mutex_unlock(&logger_queue_mutex);

				logger_flag.log_temp_sensor_flag =0;


			}

			if(heartbeat_flag.heartbeat_temp_sensor_flag == 1){
				temperature_data = get_temperature(client_temperature_type_request);
				heartbeat_temp_data_src.timestamp = record_time(); 
				heartbeat_temp_data_src.log_level = 1;
				strcpy(heartbeat_temp_data_src.source_ID,"TEMP_TASK ALIVE");
				heartbeat_temp_data_src.sensor_data = temperature_data;	
				pthread_mutex_lock(&heartbeat_queue_mutex);
				if(mq_send(mqdes_heartbeat,(char *)&heartbeat_temp_data_src,sizeof(heartbeat_data_t),0)==-1){
					perror("Sending temperature value to main unsuccessfull");
				}
				pthread_mutex_unlock(&heartbeat_queue_mutex);

				heartbeat_flag.heartbeat_temp_sensor_flag =0;


			}

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
	double force_lux_data = 0;
	last_state_t last_state = INITIAL;
	while(1){
		if(system_shutdown_flag ==1){
			printf("\n\rClosing light sensor thread");
			pthread_mutex_unlock(&logger_queue_mutex);
			pthread_mutex_unlock(&heartbeat_queue_mutex);
			pthread_exit(NULL);
		}
		else{
			if(lux_data !=READ_LIGHT_ERROR){

				lux_data = read_lux();

				if(lux_data >=75 && last_state ==DARK){
					log_light_data_src.sensor_data = lux_data;
					strcpy(log_light_data_src.source_ID,"DARK_TO_LIGHTCHANGE");
					log_light_data_src.timestamp = record_time();
					log_light_data_src.log_level = 3;

					pthread_mutex_lock(&logger_queue_mutex);

					if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
						perror("Sending light value to logger unsuccessfull");
					}
					last_state = LIGHT;
					pthread_mutex_unlock(&logger_queue_mutex);

				}
				else if(lux_data<75 && last_state == LIGHT){
					//strcpy(log_light_data_src.source_ID,"DARK_TO_LIGHTCHANGE");

					strcpy(log_light_data_src.source_ID,"LIGHT_TO_DARKCHANGE");
					log_light_data_src.sensor_data = lux_data;
					log_light_data_src.timestamp = record_time();
					log_light_data_src.log_level = 3;

					pthread_mutex_lock(&logger_queue_mutex);

					if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
						perror("Sending light value to logger unsuccessfull");
					}
					last_state =DARK;
					pthread_mutex_unlock(&logger_queue_mutex);

				}
				else{
					if(lux_data>=75){
						last_state = LIGHT;
					}
					else if(lux_data<75){
						last_state = DARK;
					}
					//	printf("\n\rNo change");
				}

			}
			//client_get_lux_flag = 1;
			if(client_request.client_get_lux_flag == 1){
				//send message through queue to server task
				lux_data = read_lux(); 

				if ( lux_data >= 75 )
				{
					strcpy(client_data.sensor_string,"Lux value in lumens(STATE=LIGHT):"); 	
					strcpy(log_light_data_src.source_ID,"EXT REQ(LIGHT STATE)");

				}
				else if ( lux_data < 75 ) 
				{
					strcpy(client_data.sensor_string,"Lux value in lumens(STATE=DARK):"); 	
					strcpy(log_light_data_src.source_ID,"EXT REQ(DARK STATE)");

				}
				//	printf("\n\rLight data called from client:%lf",lux_data);
				client_data.sensor_data = lux_data;	
				if(mq_send(mqdes_server,(char *)&client_data,sizeof(client_data_t),0)==-1){
					perror("Sending light value to server unsuccessfull");
				}

				pthread_mutex_lock(&logger_queue_mutex);

				log_light_data_src.timestamp = record_time();
				log_light_data_src.log_level = 3;

				if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
					perror("Sending light value to logger unsuccessfull");
				}
				pthread_mutex_unlock(&logger_queue_mutex);





				client_request.client_get_lux_flag = 0;

			}
			if(logger_flag.log_light_sensor_flag == 1){
				lux_data = read_lux(); 


				if(lux_data == READ_LIGHT_ERROR){
					log_light_data_src.timestamp = record_time();
					log_light_data_src.log_level = 4;
					strcpy(log_light_data_src.source_ID,"LIGHTSENSOR_REMOVED");
					pthread_mutex_lock(&logger_queue_mutex);
					if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
						perror("Light sensor removed");
					}
					logger_flag.log_light_sensor_flag =0;
					pthread_mutex_unlock(&logger_queue_mutex);


				}

				if( lux_data <75){
					strcpy(log_light_data_src.source_ID,"LIGHT(DARK STATE)");
				}
				else if(lux_data >=75){
					strcpy(log_light_data_src.source_ID,"LIGHT(LIGHT STATE)");

				}
				log_light_data_src.timestamp = record_time(); 
				log_light_data_src.log_level = 2;

				log_light_data_src.sensor_data = lux_data;	
				pthread_mutex_lock(&logger_queue_mutex);
				if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
					perror("Sending light value to logger unsuccessfull");
				}
				logger_flag.log_light_sensor_flag =0;
				pthread_mutex_unlock(&logger_queue_mutex);


			}

			if(heartbeat_flag.heartbeat_light_sensor_flag == 1){
				lux_data = read_lux(); 
				heartbeat_light_data_src.timestamp = record_time(); 
				heartbeat_light_data_src.log_level = 2;
				strcpy(heartbeat_light_data_src.source_ID,"LIGHT_TASK ALIVE");
				heartbeat_light_data_src.sensor_data = lux_data;	
				pthread_mutex_lock(&heartbeat_queue_mutex);
				if(mq_send(mqdes_heartbeat,(char *)&heartbeat_light_data_src,sizeof(heartbeat_data_t),0)==-1){
					perror("Sending light value to main unsuccessfull");
				}
				pthread_mutex_unlock(&heartbeat_queue_mutex);

				heartbeat_flag.heartbeat_light_sensor_flag =0;


			}


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
		//	printf("\n\rClosed log files");


		if(system_shutdown_flag ==1){

			printf("\n\rClosed log files");

			fclose(log_file);

			pthread_mutex_unlock(&logger_queue_mutex);
			pthread_mutex_unlock(&heartbeat_queue_mutex);
			pthread_exit(NULL);
		}

		else{
			if(heartbeat_flag.heartbeat_logger_flag == 1){
				heartbeat_logger_data_src.timestamp = record_time(); 
				heartbeat_logger_data_src.log_level = 2;
				strcpy(heartbeat_logger_data_src.source_ID,"LOGGER_TASK ALIVE");	
				pthread_mutex_lock(&heartbeat_queue_mutex);
				if(mq_send(mqdes_heartbeat,(char *)&heartbeat_logger_data_src,sizeof(heartbeat_data_t),0)==-1){
					perror("Sending logger value to main unsuccessfull");
				}
				pthread_mutex_unlock(&heartbeat_queue_mutex);

				heartbeat_flag.heartbeat_logger_flag =0;


			}

			if(mq_receive(mqdes_logger,(char *)&log_temp_data,sizeof(log_t),NULL) ==-1){
				perror("Reception of data from temp sensor thread unsuccessfull");	
			}



			log_file = fopen(arg,"a+");
			if(strcmp(log_temp_data.source_ID,"BIST SUCCESS")==0 ||strcmp(log_temp_data.source_ID,"TEMPSENSOR_REMOVED")==0 ||strcmp(log_temp_data.source_ID,"LIGHTSENSOR_REMOVED")==0 || \
			strcmp(log_temp_data.source_ID,"LIGHT_TASK ALIVE")==0 ||strcmp(log_temp_data.source_ID,"TEMP_TASK ALIVE")==0 ||strcmp(log_temp_data.source_ID,"LOGGER_TASK ALIVE")==0 || \
			strcmp(log_temp_data.source_ID,"TMP_SWING_INTERRUPT")==0){
				LOG_GENERAL(log_file,log_temp_data.timestamp,log_temp_data.log_level,log_temp_data.source_ID);

			}
			else if(strcmp(log_temp_data.source_ID,"BIST SUCCESS")!=0){
				LOG(log_file,log_temp_data.timestamp,log_temp_data.log_level,log_temp_data.source_ID,log_temp_data.sensor_data);
			}
			fclose(log_file);


		}

	}

}






