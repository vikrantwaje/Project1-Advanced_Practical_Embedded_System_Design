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
 * */
/****************************************************************************************
 *					HEADER FILE SECTION
 *****************************************************************************************/
#include "main.h"


/****************************************************************************************
 *				GLOBAL VARIABLE SECTION
 *****************************************************************************************/
mqd_t mqdes_server;
struct mq_attr attribute_server;
mqd_t mqdes_logger;
struct mq_attr attribute_logger;
mqd_t mqdes_heartbeat;
struct mq_attr attribute_heartbeat;
pthread_t thread1, thread2, thread3, thread4;
bool system_shutdown_main_flag;
int socket_fd;
pthread_mutex_t logger_queue_mutex;
log_t log_main_data_src;
 bool logger_heartbeat_indicator;
 bool light_heartbeat_indicator ;
 bool temp_heartbeat_indicator ;

/*******************************************************************************************
 * @brief Main function
 *
 * Responsible for creating four threads for execution namely light sensor thread, temperature th * read, logger thread and socket thread
 *
 * @param null
 *
 * @return null
 ********************************************************************************************/
int main(int argc, char *argv[])
{
	int ret_status;
	char last_state = '0';
	char ret_interrupt_val;
	heartbeat_data_t heartbeat_temp_data;
	sensor_status_t stat;
	/*stat=light_sensor_power_on();
	  if(stat !=WRITE_REG_SUCCESS){
	  perror("Power ON of light sensor failed");
	  }*/

	signal_handler_init();
	 ret_status=GPIO_init();
	if(ret_status ==1){
	printf("Error in log file");
	}

	open_message_queue_server(&mqdes_server, &attribute_server);
	open_message_queue_logger(&mqdes_logger,&attribute_logger);
	open_message_queue_heartbeat(&mqdes_heartbeat,&attribute_heartbeat);


	built_in_self_test();
	create_log_timer();
	create_heartbeat_timer();
 	create_heartbeat_recovery_timer();
	system_shutdown_main_flag =0;
	system_shutdown_flag =0;
	while(1){


		if(system_shutdown_main_flag == 1){
		
				close_message_queue_server(&mqdes_server);
			close_message_queue_logger(&mqdes_logger);
			close_message_queue_heartbeat(&mqdes_heartbeat);
			close(socket_fd);
			pthread_cancel(thread1);
			pthread_cancel(thread4);
			printf("\n\rCLosing server and logger task");
			break;
		}


		 if(mq_receive(mqdes_heartbeat,(char *)&heartbeat_temp_data,sizeof(heartbeat_data_t),NULL) ==-1){
			perror("Reception of data from temp sensor thread unsuccessfull");	
		
		}
		else{
			printf("\n\r%s,[%lf]",heartbeat_temp_data.source_ID,heartbeat_temp_data.sensor_data);
				if(strcmp(heartbeat_temp_data.source_ID,"TEMP_TASK ALIVE")==0){
					temp_heartbeat_indicator = 1;
				}
				if(strcmp(heartbeat_temp_data.source_ID,"LIGHT_TASK ALIVE")==0){
					light_heartbeat_indicator = 1;
				}
				if(strcmp(heartbeat_temp_data.source_ID,"LOGGER_TASK ALIVE")==0){
					logger_heartbeat_indicator = 1;
				}
				pthread_mutex_lock(&logger_queue_mutex);
				strcpy(log_main_data_src.source_ID,heartbeat_temp_data.source_ID);
				log_main_data_src.timestamp = record_time();
				log_main_data_src.log_level = 1;

				if(mq_send(mqdes_logger,(char *)&log_main_data_src,sizeof(log_t),0)==-1){
					perror("Sending Heartbeat to logger unsuccessfull");
				}
				pthread_mutex_unlock(&logger_queue_mutex);

		}

		ret_interrupt_val = IRQ_handler();

		if( ret_interrupt_val == '1' && last_state!=ret_interrupt_val )
		{
			printf("\n\rInterrupt Received");
				pthread_mutex_lock(&logger_queue_mutex);
				strcpy(log_main_data_src.source_ID,"TMP_SWING_INTERRUPT");
				log_main_data_src.timestamp = record_time();
				log_main_data_src.log_level = 3;

				if(mq_send(mqdes_logger,(char *)&log_main_data_src,sizeof(log_t),0)==-1){
					perror("Sending temperature swing to logger unsuccessfull");
				}
				pthread_mutex_unlock(&logger_queue_mutex);
				last_state = ret_interrupt_val;

		}
		else if ( ret_interrupt_val == '0' )
		{
			printf("\n\r No Interrupt");
			last_state = ret_interrupt_val;
		}
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
	}
	printf("\n\rMain Thread Exited Successfully \n");

	/*close_message_queue_server(&mqdes_server);
	close_message_queue_logger(&mqdes_logger);
	close_message_queue_heartbeat(&mqdes_heartbeat);
*/
return 0;
}


