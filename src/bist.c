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
 *					MACROS AND ENUMS
 ****************************************************************************************/

/***************************************************************************************
 *					GLOBAL VARIABLE
 ****************************************************************************************/
pthread_t thread1, thread2, thread3, thread4;
mqd_t mqdes_logger;
log_t log_temp_data_src;
log_t log_light_data_src;
pthread_mutex_t logger_queue_mutex;


/***************************************************************************************
 *				FUNCTION DEFINITION
 ***********************************************************************************************/
void built_in_self_test(){
	double return_data = 0.0;
	sensor_status_t sensor_stat;	
	uint8_t sensor_data = 0;
	uint8_t *data = malloc(sizeof(uint8_t));
	uint16_t *data_16 = malloc(sizeof(uint16_t));
	bool flag_temp = 0;	//To check whether there is any error in temperature sensor initialisation
	bool flag_light = 0;	// To check whether there is any error in light sensor initialisation
	bool flag_thread = 0;	//To check whether there is any error in pthread creation
	int ret_status =0;
	led_init(RED_LED);
	led_init(BLUE_LED);
	led_init(GREEN_LED);
	led_init(YELLOW_LED);

	if(data == NULL || data_16 == NULL){
		printf("Malloc failed");
	}
	else{

		/* Socket thread creation*/
		
		// Check whether temperature sensor is working properly

		ret_status = write_thigh(THIGH_VAL);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write  Thigh register");
			flag_temp = 1;
		}


		return_data = get_Thigh(REQUEST_CELSIUS);
		if(return_data !=THIGH_VAL){
			printf("\n\rTemperature sensor initialisation failed.Incorrect Thigh value =%lf",return_data);
			flag_temp =1;
		}

		ret_status = write_tlow(TLOW_VAL);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write  Tlow register");
			flag_temp =1;
		}

		return_data = get_Tlow(REQUEST_CELSIUS);
		if(return_data != TLOW_VAL){
			printf("\n\rTemperature sensor initialisation failed.Incorrect Tlow value. Tlow temp =%lf",return_data);
			flag_temp =1;
		}

		ret_status = configure_temp_fault(FAULT_1);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write fault bits. ");
			flag_temp =1;
		}


		ret_status = read_temp_fault(data);
		if(((*(data) & FAULT_MASK) !=FAULT_1) && ret_status!=READ_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Incorrect fault bit values data = %x",*data);
			flag_temp = 1;
		}

		ret_status = configure_temp_EMmode(EM_OFF);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write EM bits");
			flag_temp =1;
		}

		ret_status = read_temp_EM(data);
		if((*(data) & EM_MASK)!=EM_OFF && ret_status!=READ_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Incorrect EM bit value data =%x",*data);
			flag_temp = 1;
		}

		ret_status = configure_temp_conversion_rate(CONVERSION_RATE_4);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write conversion rate bits");
			flag_temp = 1;
		}

		ret_status = read_temp_conversion_rate(data);
		if((*(data) & CONVERSION_RATE_MASK)!=CONVERSION_RATE_4 && ret_status!=READ_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Incorrect conversion rate bit value data =%x",*data);
			flag_temp = 1;
		}		


		ret_status = read_temp_sensor_resolution(data);
		if((*(data) & RESOLUTION_MASK)!=SENSOR_RESOLUTION_12_BIT && ret_status!=READ_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Incorrect sensor resolution bit value data =%x",*data);
			flag_temp =1;
		}		


		

		// Check whether light sensor is working properly

		sensor_stat=light_sensor_power_on();
		if(sensor_stat != WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed");
			flag_light =1;
		}
	

		sensor_stat =read_identification_reg(data);	
		if(*data != IDENTIFICATION_MASK && sensor_stat!=READ_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Incorrect identification read data = %d",*data);
			flag_light = 1;
		}

		ret_status = set_integration_time(INTEGRATION_402);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write Integration bits");
			flag_light = 1;
		}

		ret_status = get_integration_time(data);
		if((*(data) & INTEGRATION_MASK)!=INTEGRATION_402 && ret_status!=READ_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Incorrect integration rate bit  data =%x",*data);
			flag_light =1;
		}		
	
		led_on(YELLOW_LED);

		ret_status = set_gain(HIGH_GAIN);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write gain bits");
			flag_light =1;
		}
	

		ret_status = get_gain(data);
		if((*(data) & GAIN_MASK)!=HIGH_GAIN && ret_status!=READ_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Incorrect gain bit  data =%x",*data);
			flag_light =1;
		}
	

		ret_status = config_interrupt_ctrl_reg(INTERRUPT_ON);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write Interrupt control register bits");
			flag_light =1;
		}
		ret_status = get_interrupt_ctrl_reg(data);
		if(*data!= INTERRUPT_ON && ret_status!= READ_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to read Interrupt control register bits");
			flag_light =1;
		}	

		ret_status = set_high_threshold(THRESHOLD_HIGH);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write Interrupt high threshold register ");
			flag_light =1;
		}

		ret_status = get_high_threshold(data_16);
		if( *data_16 !=THRESHOLD_HIGH && ret_status!= READ_REG_SUCCESS ){
			printf("\n\rLight sensor initialisation failed. Failed to read Interrupt high threshold,val =%ld",*(data_16));
			flag_light =1;
		}

		ret_status = set_low_threshold(THRESHOLD_LOW);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write Interrupt high threshold register ");
			flag_light = 1;
		}

		ret_status = get_low_threshold(data_16);
		if( *data_16 !=THRESHOLD_LOW && ret_status!= READ_REG_SUCCESS ){
			printf("\n\rLight sensor initialisation failed. Failed to read Interrupt high threshold,val =%ld",*(data_16));
			flag_light =1;
		}
	

		//	printf("\n\rValue = %ld",*(data_16));
		//Check whether threads have been created successfully or not
	
	

			// Notify success/no success to logger
	

		ret_status = pthread_create( &thread1, NULL, socket_thread,0);
		if( ret_status )
		{
			fprintf( stderr, "socket_thread not created, Error Code: %d\n", ret_status);
			flag_thread =1;
		}

			/*Temperature thread creation*/
		ret_status = pthread_create( &thread2, NULL, temperature_thread,0);
		if( ret_status )
		{
			fprintf( stderr, "temperature_thread not created, Error Code: %d\n", ret_status);
			flag_thread =1;
		}
	
		/*light sensor thread creation*/
		ret_status = pthread_create( &thread3, NULL, light_sensor_thread,0);
		if( ret_status )
		{
			fprintf( stderr, "light_sensor_thread not created, Error Code: %d\n", ret_status);
			flag_thread =1;
		}


		/*logger thread creation*/
		ret_status = pthread_create( &thread4, NULL, logger_thread,0);

		if( ret_status )
		{
			fprintf( stderr, "logger_thread not created, Error Code: %d\n", ret_status);
			flag_thread =1;
		}
	

	
		

		if(flag_thread == 1){
			pthread_mutex_lock(&logger_queue_mutex);

			log_light_data_src.timestamp = record_time();
			log_light_data_src.log_level = 4;
			log_light_data_src.sensor_data = 0;
			strcpy(log_light_data_src.source_ID,"THREAD INIT FAILED");

			if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
				perror("PTHREAD INITIALISATION FAILED");
			}
			pthread_mutex_unlock(&logger_queue_mutex);



		}

		if(flag_temp == 1){
			pthread_mutex_lock(&logger_queue_mutex);

			log_temp_data_src.timestamp = record_time();
			log_temp_data_src.log_level = 4;
			log_temp_data_src.sensor_data = 0;
			strcpy(log_temp_data_src.source_ID,"TEMP INIT FAILED");

			if(mq_send(mqdes_logger,(char *)&log_temp_data_src,sizeof(log_t),0)==-1){
				perror("TEMPERATURE SENSOR INITIALISATION FAILED");
			}
			pthread_mutex_unlock(&logger_queue_mutex);



		}
		if(flag_light == 1){
			pthread_mutex_lock(&logger_queue_mutex);

			log_light_data_src.timestamp = record_time();
			log_light_data_src.log_level = 4;
			log_light_data_src.sensor_data = 0;
			strcpy(log_light_data_src.source_ID,"LIGHT INIT FAILED");

			if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
				perror("LIGHT SENSOR INITIALISATION FAILED");
			}
			pthread_mutex_unlock(&logger_queue_mutex);



		}

	else{
		led_on(BLUE_LED);
		pthread_mutex_lock(&logger_queue_mutex);
		log_light_data_src.timestamp = record_time();
		log_light_data_src.log_level = 4;
		log_light_data_src.sensor_data = 0;
		strcpy(log_light_data_src.source_ID,"BIST SUCCESS");

		if(mq_send(mqdes_logger,(char *)&log_light_data_src,sizeof(log_t),0)==-1){
			perror("BIST INITIALISATION FAILED");
		}
		pthread_mutex_unlock(&logger_queue_mutex);


}	
}
}
