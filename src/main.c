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


/****************************************************************************************
*				GLOBAL VARIABLE SECTION
*****************************************************************************************/
mqd_t mqdes_server;
struct mq_attr attribute_server;
mqd_t mqdes_logger;
struct mq_attr attribute_logger;
mqd_t mqdes_heartbeat;
struct mq_attr attribute_heartbeat;

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
	heartbeat_data_t heartbeat_temp_data;
	sensor_status_t stat;
	stat=light_sensor_power_on();
	if(stat !=WRITE_REG_SUCCESS){
	perror("Power ON of light sensor failed");
	}
	create_log_timer();
	create_heartbeat_timer();
	led_init(RED_LED);
	led_init(BLUE_LED);
	led_init(GREEN_LED);
	led_init(YELLOW_LED);





	open_message_queue_server(&mqdes_server, &attribute_server);
	open_message_queue_logger(&mqdes_logger,&attribute_logger);
	open_message_queue_heartbeat(&mqdes_heartbeat,&attribute_heartbeat);

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
	
while(1){
		
		if(mq_receive(mqdes_heartbeat,(char *)&heartbeat_temp_data,sizeof(heartbeat_data_t),NULL) ==-1){
			perror("Reception of data from temp sensor thread unsuccessfull");	
		}

			printf("\n\r[%lf] [%d] [%s] [%lf]",heartbeat_temp_data.timestamp,heartbeat_temp_data.log_level,heartbeat_temp_data.source_ID,heartbeat_temp_data.sensor_data);
		

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
	printf("Main Thread Exited Successfully \n");

	close_message_queue_server(&mqdes_server);
	close_message_queue_logger(&mqdes_logger);
	close_message_queue_heartbeat(&mqdes_heartbeat);
	return 0;
}


