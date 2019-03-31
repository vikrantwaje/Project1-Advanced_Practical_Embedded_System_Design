/********************************************************************************************
*					FILENAME:temp_sensor.c
**********************************************************************************************/
/* Title: temp_sensor.c
 * Brief: Responsible for providing various helper function needed to communicate with temperature sensor
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: http://www.sparkfun.com/products/13314
 * 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include "temp_sensor.h"
#include"synchronization.h"

/**************************************************************************************
*					GLOBAL VARIABLE
*******************************************************************************************/
const char *temp_i2c_path_name = "/dev/i2c-2";
pthread_mutex_t i2c_mutex;


/**********************************************************************************
*				FUNCTION DEFINITION
***************************************************************************************/
/***********************************************************************************************
 * @brief write pointer register
 *
 *Responsible for writing into pointer registerof temperature sensor TMP102
 *
 * @param address: address of pointer register TMP102
 *
 * @return status of I2C operation
 *********************************************************************************************/

sensor_status_t write_ptr_reg(uint8_t address){
	int status = 0;
	int n =0;
	int fptr = open(temp_i2c_path_name,O_RDWR);	
	if(fptr == -1){
		perror("Error in opening the file");
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,TEMP_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		return WRITE_REG_FAIL;
	}
	n= write(fptr,&address,1);
	if(n == -1){
		perror("Write not successfull");
		return WRITE_REG_FAIL;
	}
	close(fptr);
	return WRITE_REG_SUCCESS;
}

/*********************************************************************************************** 
 * @brief write register in temperature register
 *
 *Responsible for writing into  register of temperature sensor TMP102
 *
 * @param address: address of  register  of TMP102
 * @param data: data to be written into register of TMP102
 *
 * @return status of I2C operation
 *********************************************************************************************/

sensor_status_t temperature_write_reg(uint8_t address, uint16_t data){
	int status =0;
	int fptr = 0;
	int n = 0;
	uint8_t *buffer = malloc(sizeof(uint8_t) *5);
	if( buffer == NULL )
	{
		return WRITE_REG_FAIL;
	}
	*(buffer + 0) = (address);
	*(buffer + 1) = ((data & 0xFF00)>>8);
	*(buffer + 2) = ((data) & 0x00FF);

	fptr = open(temp_i2c_path_name,O_RDWR);	
	if(fptr == -1){
		perror("Error in opening the file");
		free(buffer);
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,TEMP_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		free(buffer);
		return WRITE_REG_FAIL;
	}
	n = write(fptr,buffer,3);
	if(n ==-1){
		perror("Write not successfull");
		free(buffer);
		return WRITE_REG_FAIL;
	}
	close(fptr);
	free(buffer);
	return WRITE_REG_SUCCESS;
}

/***********************************************************************************************  
 * @brief Read register in temperature register
 *
 *Responsible for reading from  register of temperature sensor TMP102
 *
 * @param address: address of  register  of TMP102
 * @param data: data to be read from  register of TMP102
 * @param command: register bits which are to be read
 * @return status of I2C operation
 *********************************************************************************************/



sensor_status_t temperature_read_reg(uint8_t address, uint8_t *data,reg_read_cmd_t command){
	int status =0;
	int fptr = 0;
	int n = 0;
	fptr = open(temp_i2c_path_name,O_RDWR);	
	if(fptr == -1){
		perror("Error in opening the file");
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,TEMP_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		return WRITE_REG_FAIL;
	}
	n =write(fptr,&address,1);
	if(n==-1){
		perror("Write not successfull");
		return WRITE_REG_FAIL;
	}

	n = read(fptr,(data ),2);
	if(n ==-1){
		perror("Read not successfull");
		return READ_REG_FAIL;
	}

	//swap the values: Using XOR swap
	*(data + 0) = *(data +0) ^ *(data +1);
	*(data +1) = *(data +0) ^ *(data +1);
	*(data +0) = *(data +0) ^ *(data +1);
	if(command == SD_MODE){
		*(data + 0) =*(data + 1);
		*(data + 1) =0;
	}	
	else if(command == FAULT){
		*(data + 0) = *(data + 1)>>3;
		*(data + 1) = 0;
	}

	else if(command == EM){
		*(data + 0) = *(data +0)>>4;
		*(data + 1) = 0;
	}

	else if(command == CONVERSION_RATE){

		*(data +0) = *(data + 0)>>6;
		*(data +1) =0;
	}
	else if(command == RESOLUTION){
		*(data + 0) = *(data + 1)>>5;
		*(data + 1) =0;

	}
	else{
		*(data +0 )= *(data +0);
		*(data + 1) = *(data +1);
	}
	close(fptr);
	return READ_REG_SUCCESS;

}
/*********************************************************************************************** 
 * @brief Get temperature
 *
 * Read the value from temperature register
 *
 * @param request: Temperature value in kelvin, celsius and farhenheit to be returned
 * @return double: Value of converted temperature
 *********************************************************************************************/


double get_temperature(request_cmd_t request){


	pthread_mutex_lock(&i2c_mutex);

	//double result = 0;
	double multiplier =0;
	uint8_t *data = malloc(sizeof(uint8_t) * 2);
	if ( data == NULL )
	{
		return READ_REG_FAIL;
	}
    multiplier = 0.0625;	
	int status = temperature_read_reg(TEMPERATURE_REG,data,ALL);
	if(status !=READ_REG_SUCCESS){

		perror("Reading configuration register failed");
		free( data );
		pthread_mutex_unlock(&i2c_mutex);
		return READ_TEMPERATURE_ERROR;
	}
	//printf("%x %x",*(data + 0),*(data +1));

	int32_t digitalTemp =0;

	// Bit 0 of second byte will always be 0 in 12-bit readings and 1 in 13-bit
	if(*(data + 0)&0x01)	// 13 bit mode
	{
		// Combine bytes to create a signed int
		digitalTemp = (*(data + 1) << 5) | (*(data + 0) >> 3);
		// Temperature data can be + or -, if it should be negative,
		// convert 13 bit to 16 bit and use the 2s compliment.
		if(digitalTemp > 0xFFF)
		{
			digitalTemp |= 0xE000;
		}
	}
	else	// 12 bit mode
	{
		// Combine bytes to create a signed int 
		digitalTemp = (*(data + 1) << 4) | (*(data + 0) >> 4);
		// Temperature data can be + or -, if it should be negative,
		// convert 12 bit to 16 bit and use the 2s compliment.
		if(digitalTemp > 0x7FF)
		{
			digitalTemp |= 0xF000;
		}
	}
	// Convert digital reading to analog temperature (1-bit is equal to 0.0625 C)

	free(data);

	pthread_mutex_unlock(&i2c_mutex);

	if ( request == REQUEST_KELVIN )
	{
		return(digitalTemp*multiplier + 273.15);		
	}
	else if ( request == REQUEST_FAHRENHEIT )
	{
		return ((digitalTemp*multiplier * 9.0/5.0) + 32.0);
	}
	else
		return(digitalTemp*multiplier);
}

/*********************************************************************************************** 
 * @brief Write tlow
 *
 * Write the value of tlow 
 *
 * @param :null
 * @return sensor_stat_t: Status of I2C operation
 *********************************************************************************************/
sensor_status_t write_tlow(float temperature){

	sensor_status_t sensor_stat = 0;	
	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t)*2);
	if(temperature > 150.0){
		temperature = 150.0;
	}
	if(temperature <-55){
		temperature = -55.0;
	}
  	
	temperature = temperature/0.0625;
	*(data + 1) =(int)(temperature) >> 4;
	*(data +0)= (int)(temperature) << 4;
	sensor_stat = temperature_write_reg(TLOW_REG,(*(data + 0) | *(data + 1) << 8));
	if( sensor_stat != WRITE_REG_SUCCESS )
	{
		perror("Configuring Temp low registerfailed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}
	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;


}

/*********************************************************************************************** 
 * @brief Read tlow
 *
 * Read the value from tlow 
 *
 * @param :null
 * @return double: tempearture register low value
 *********************************************************************************************/


double get_Tlow(request_cmd_t request){

	pthread_mutex_lock(&i2c_mutex);
	double multiplier =0;
	multiplier = 0.0625;
	uint8_t *data = malloc(sizeof(uint8_t) * 2);
	int status = temperature_read_reg(TLOW_REG,data,ALL);
	if(status !=READ_REG_SUCCESS){

		perror("Reading configuration register failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
	}

	//printf("%x %x",*(data + 0),*(data +1));

	int32_t digitalTemp =0;

	
	// Combine bytes to create a signed int 
	digitalTemp = (*(data + 1) << 4) | (*(data + 0) >> 4);
	// Temperature data can be + or -, if it should be negative,
	// convert 12 bit to 16 bit and use the 2s compliment.
	if(digitalTemp > 0x7FF)
	{
	digitalTemp |= 0xF000;
	}
	
	// Convert digital reading to analog temperature (1-bit is equal to 0.0625 C)

	free(data);

	pthread_mutex_unlock(&i2c_mutex);

	if ( request == REQUEST_KELVIN )
	{
		return(digitalTemp*multiplier + 273.15);		
	}
	else if ( request == REQUEST_FAHRENHEIT )
	{
		return ((digitalTemp*multiplier * 9.0/5.0) + 32.0);
	}
	else
		return(digitalTemp*multiplier);
}
/*********************************************************************************************** 
 * @brief Write thigh
 *
 * Write the value of thigh 
 *
 * @param :null
 * @return sensor_stat_t: Status of I2C operation
 *********************************************************************************************/
sensor_status_t write_thigh(float temperature){

	sensor_status_t sensor_stat = 0;	
	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t)*2);
	if(temperature > 150.0){
		temperature = 150.0;
	}
	if(temperature <-55){
		temperature = -55.0;
	}
  	
	temperature = temperature/0.0625;
	*(data + 1) =(int)(temperature) >> 4;
	*(data +0)= (int)(temperature) << 4;
	sensor_stat = temperature_write_reg(THIGH_REG,(*(data + 0) | *(data + 1) << 8));
	if( sensor_stat != WRITE_REG_SUCCESS )
	{
		perror("Configuring Temp low registerfailed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}
	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;


}

/*********************************************************************************************** 
 * @brief Read thigh
 *
 * Read the value from thigh 
 *
 * @param :null
 * @return double: tempearture register high value
 *********************************************************************************************/


double get_Thigh(request_cmd_t request){

	pthread_mutex_lock(&i2c_mutex);
	double multiplier =0;
	uint8_t *data = malloc(sizeof(uint8_t) * 2);
	multiplier = 0.0625;
	int status = temperature_read_reg(THIGH_REG,data,ALL);
	if(status !=READ_REG_SUCCESS){

		perror("Reading THIGH register failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
	}

	//printf("%x %x",*(data + 0),*(data +1));

	int32_t digitalTemp =0;

	
	// Combine bytes to create a signed int 
	digitalTemp = (*(data + 1) << 4) | (*(data + 0) >> 4);
	// Temperature data can be + or -, if it should be negative,
	// convert 12 bit to 16 bit and use the 2s compliment.
	if(digitalTemp > 0x7FF)
	{
	digitalTemp |= 0xF000;
	}
	
	// Convert digital reading to analog temperature (1-bit is equal to 0.0625 C)

	free(data);

	pthread_mutex_unlock(&i2c_mutex);

	if ( request == REQUEST_KELVIN )
	{
		return(digitalTemp*multiplier + 273.15);		
	}
	else if ( request == REQUEST_FAHRENHEIT )
	{
		return ((digitalTemp*multiplier * 9.0/5.0) + 32.0);
	}
	else
		return(digitalTemp*multiplier);

}

/*********************************************************************************************** 
 * @brief set sensor in shutdown mode
 *
 * set the configuration register in shutdown mode
 *
 * @param :null
 * @return :status of I2C operation
 *********************************************************************************************/


sensor_status_t configure_temp_shutdown(void){

	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t)*2);
	sensor_status_t sensor_stat = temperature_read_reg(CONFIGURATION_REG,data, ALL);
	if( sensor_stat != READ_REG_SUCCESS )
	{
		perror("Configuring Shutdown mode failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	*(data + 1) |= SHUTDOWN_ON;
	sensor_stat = temperature_write_reg(CONFIGURATION_REG,(*(data + 0) | *(data + 1) << 8));
	if( sensor_stat != WRITE_REG_SUCCESS )
	{
		perror("Configuring Shutdown mode failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}
	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;
}

/*********************************************************************************************** 
 * @brief Write fault bits
 *
 * Write the fault bits in configuration register 
 *
 * @param :null
 * @return sensor_stat_t: Status of I2C operation
 *********************************************************************************************/
sensor_status_t configure_temp_fault(uint8_t mode){

	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t)*2);
	sensor_status_t sensor_stat = temperature_read_reg(CONFIGURATION_REG,data, ALL);
	if( sensor_stat != READ_REG_SUCCESS )
	{
		perror("Reading fault bits failed failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

	*(data + 1) &= 0xE7;	
   	*(data + 1) |= mode << 3;	


	sensor_stat = temperature_write_reg(CONFIGURATION_REG,(*(data + 0) | *(data + 1) << 8));
	if( sensor_stat != WRITE_REG_SUCCESS )
	{
		perror("Configuring fault bits failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}
	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;

}


/*********************************************************************************************** 
 * @brief Read fault bits from configuration register
 *
 *  Read fault bits
 *
 * @param :uint8_t* data
 * @return :status of I2C operation
 *********************************************************************************************/


sensor_status_t read_temp_fault(uint8_t *data){

	pthread_mutex_lock(&i2c_mutex);
	uint8_t *temp_data = malloc(sizeof(uint8_t)*2);
	if (temp_data == NULL)
	{
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

	sensor_status_t sensor_stat = temperature_read_reg(CONFIGURATION_REG,temp_data,ALL);
	if(sensor_stat != READ_REG_SUCCESS)
	{
		perror("read temp fault failed");
		free(temp_data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	*(data + 0) = *(temp_data + 1)>>3;
	free(temp_data);
	pthread_mutex_unlock(&i2c_mutex);
	return READ_REG_SUCCESS;
}

/*********************************************************************************************** 
 * @brief set sensor in EM mode
 *
 * set the configuration register in EM mode
 *
 * @param :mode
 * @return :status of I2C operation
 *********************************************************************************************/

sensor_status_t configure_temp_EMmode(uint8_t mode){

	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t)*2);
	sensor_status_t sensor_stat = temperature_read_reg(CONFIGURATION_REG,data, ALL);
	if( sensor_stat != READ_REG_SUCCESS )
	{
		perror("Configuring Extended mode failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

	*(data + 0) &= 0xEF;		// Clear EM (bit 4 of second byte)
   	*(data + 0) |= mode<<4;	// Shift in new exentended mode bit


	sensor_stat = temperature_write_reg(CONFIGURATION_REG,(*(data + 0) | *(data + 1) << 8));
	if( sensor_stat != WRITE_REG_SUCCESS )
	{
		perror("Configuring Extended mode failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}
	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;
}



/*********************************************************************************************** 
 * @brief Read EM mode from configuration register
 *
 *  Read Em mode bits
 *
 * @param :uint8_t *data
 * @return :status of I2C operation
 *********************************************************************************************/


sensor_status_t read_temp_EM(uint8_t *data){

	pthread_mutex_lock(&i2c_mutex);
	uint8_t *temp_data = malloc(sizeof(uint8_t)*2);
	if (temp_data == NULL)
	{
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

	sensor_status_t sensor_stat = temperature_read_reg(CONFIGURATION_REG,temp_data,ALL);
	if(sensor_stat != READ_REG_SUCCESS)
	{
		perror("read temp EM failed");
		free(temp_data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	*(data + 0) = *(temp_data + 0)>>4;
	free(temp_data);
	pthread_mutex_unlock(&i2c_mutex);
	return READ_REG_SUCCESS;
}

/*********************************************************************************************** 
 * @brief set sensor conversion rate
 *
 * set the conversion rate of temperature sensor
 *
 * @param :data: To Set the conversion rate
 * @return :status of I2C operation
 *********************************************************************************************/


sensor_status_t configure_temp_conversion_rate(uint8_t rate){


	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t)*2);
	sensor_status_t sensor_stat = temperature_read_reg(CONFIGURATION_REG,data, ALL);
	if( sensor_stat != READ_REG_SUCCESS )
	{
		perror("Configuring Temp conversion rate failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

  	*(data + 0) &= 0x3F;  // Clear CR0/1 (bit 6 and 7 of second byte)
  	*(data + 0) |= rate<<6;	// Shift in new conversion rate


	sensor_stat = temperature_write_reg(CONFIGURATION_REG,(*(data + 0) | *(data + 1) << 8));
	if( sensor_stat != WRITE_REG_SUCCESS )
	{
		perror("Configuring Temp conversion ratefailed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}
	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;




}
/*********************************************************************************************** 
 * @brief Read conversion rate from configuration register
 *
 *  Read Conversion rate
 *
 * @param :uint8_t *data
 * @return :status of I2C operations
 *********************************************************************************************/

sensor_status_t read_temp_conversion_rate(uint8_t *data){

	pthread_mutex_lock(&i2c_mutex);
	uint8_t *temp_data = malloc(sizeof(uint8_t)*2);
	if (temp_data == NULL)
	{
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

	sensor_status_t sensor_stat = temperature_read_reg(CONFIGURATION_REG,temp_data,ALL);
	if(sensor_stat != READ_REG_SUCCESS)
	{
		perror("read temp conversion failed");
		free(temp_data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	*(data + 0) = *(temp_data + 0)>>6;
	free(temp_data);
	pthread_mutex_unlock(&i2c_mutex);
	return READ_REG_SUCCESS;

}


/*********************************************************************************************** 
 * @brief Read sensor resolution from configuration register
 *
 *  Read sensor resolution
 *
 * @param :uint8_t *data
 * @return :status of I2C operations
 *********************************************************************************************/

sensor_status_t read_temp_sensor_resolution(uint8_t *data){

	pthread_mutex_lock(&i2c_mutex);
	uint8_t *temp_data = malloc(sizeof(uint8_t)*2);
	if (temp_data == NULL)
	{
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

	sensor_status_t sensor_stat = temperature_read_reg(CONFIGURATION_REG,temp_data,ALL);
	if(sensor_stat != READ_REG_SUCCESS)
	{
		perror("read temp conversion failed");
		free(temp_data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	*(data + 0) = *(temp_data + 1)>>5;
	free(temp_data);
	pthread_mutex_unlock(&i2c_mutex);
	return READ_REG_SUCCESS;

}
