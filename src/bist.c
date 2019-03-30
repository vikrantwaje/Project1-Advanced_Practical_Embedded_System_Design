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

/***************************************************************************************
 *				FUNCTION DEFINITION
 ***********************************************************************************************/
void built_in_self_test(){
	double return_data = 0.0;
	sensor_status_t sensor_stat;	
	uint8_t sensor_data = 0;
	uint8_t *data = malloc(sizeof(uint8_t));
	uint16_t *data_16 = malloc(sizeof(uint16_t));

	int ret_status =0;

	if(data == NULL || data_16 == NULL){
		printf("Malloc failed");
	}
	else{
		// Check whether temperature sensor is working properly

		ret_status = write_thigh(THIGH_VAL);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write  Thigh register");
		}


		return_data = get_Thigh(REQUEST_CELSIUS);
		if(return_data !=THIGH_VAL){
			printf("\n\rTemperature sensor initialisation failed.Incorrect Thigh value =%lf",return_data);
		}

		ret_status = write_tlow(TLOW_VAL);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write  Tlow register");
		}

		return_data = get_Tlow(REQUEST_CELSIUS);
		if(return_data != TLOW_VAL){
			printf("\n\rTemperature sensor initialisation failed.Incorrect Tlow value. Tlow temp =%lf",return_data);
		}

		ret_status = configure_temp_fault(FAULT_2);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write fault bits. ");
		}


		ret_status = read_temp_fault(data);
		if(((*(data) & 0x03) !=FAULT_2) && ret_status!=READ_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Incorrect fault bit values data = %x",*data);
		}

		ret_status = configure_temp_EMmode(EM_OFF);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write EM bits");
		}

		ret_status = read_temp_EM(data);
		if((*(data) & 0x01)!=0x00 && ret_status!=READ_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Incorrect EM bit value data =%x",*data);
		}

		ret_status = configure_temp_conversion_rate(CONVERSION_RATE_4);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Failed to write conversion rate bits");
		}

		ret_status = read_temp_conversion_rate(data);
		if((*(data) & 0x03)!=0x02 && ret_status!=READ_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Incorrect conversion rate bit value data =%x",*data);
		}		


		ret_status = read_temp_sensor_resolution(data);
		if((*(data) & 0x03)!=0x03 && ret_status!=READ_REG_SUCCESS){
			printf("\n\rTemperature sensor initialisation failed. Incorrect sensor resolution bit value data =%x",*data);
		}		
		// Check whether light sensor is working properly

		sensor_stat=light_sensor_power_on();
		if(sensor_stat != WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed");
		}

		sensor_stat =read_identification_reg(data);	
		if(*data != 0x05 && sensor_stat!=READ_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Incorrect identification read data = %d",*data);
		}

		ret_status = set_integration_time(INTEGRATION_402);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write Integration bits");
		}

		ret_status = get_integration_time(data);
		if((*(data) & 0x03)!=0x02 && ret_status!=READ_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Incorrect integration rate bit  data =%x",*data);
		}		

		ret_status = set_gain(HIGH_GAIN);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write gain bits");
		}

		ret_status = get_gain(data);
		if((*(data) & 0x01)!=0x01 && ret_status!=READ_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Incorrect gain bit  data =%x",*data);
		}

		ret_status = config_interrupt_ctrl_reg(INTERRUPT_ON);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write Interrupt control register bits");
		}
		ret_status = get_interrupt_ctrl_reg(data);
		if(*data!= INTERRUPT_ON && ret_status!= READ_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to read Interrupt control register bits");
		}	

		ret_status = set_high_threshold(THRESHOLD_HIGH);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write Interrupt high threshold register ");
		}
			
		ret_status = get_high_threshold(data_16);
		if( *data_16 !=THRESHOLD_HIGH && ret_status!= READ_REG_SUCCESS ){
			printf("\n\rLight sensor initialisation failed. Failed to read Interrupt high threshold,val =%ld",*(data_16));
		}

		ret_status = set_low_threshold(THRESHOLD_LOW);
		if(ret_status!= WRITE_REG_SUCCESS){
			printf("\n\rLight sensor initialisation failed. Failed to write Interrupt high threshold register ");
		}
			
		ret_status = get_low_threshold(data_16);
		if( *data_16 !=THRESHOLD_LOW && ret_status!= READ_REG_SUCCESS ){
			printf("\n\rLight sensor initialisation failed. Failed to read Interrupt high threshold,val =%ld",*(data_16));
		}

		printf("\n\rValue = %ld",*(data_16));
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

}
