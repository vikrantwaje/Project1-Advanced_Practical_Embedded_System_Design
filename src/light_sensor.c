


/********************************************************************************************
*					FILENAME: light_sensor.c
**********************************************************************************************/
/* Title Light sensor.c
 * Brief: Contains function that are used for communication with light sensor
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1
 * Reference[1]: http://www.sparkfun.com/products/14350
 * 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#include "light_sensor.h"
#include"synchronization.h"

/***************************************************************************************
*					GLOBAL VARIABLE
****************************************************************************************/
const char *light_i2c_path_name = "/dev/i2c-2";
pthread_mutex_t i2c_mutex;

/***************************************************************************************
*				FUNCTION DEFINITION
***********************************************************************************************/

/***********************************************************************************************  
 * @brief write register in light sensor 
 *
 *Responsible for writing into  register of light sensor
 *
 * @param address: address of  register  of light sensor
 * @param data: data to be written into register of light sensor
 *
 * @return status of I2C operation
 *********************************************************************************************/


sensor_status_t light_write_reg(uint8_t address, uint8_t data){
	int status =0;
	int fptr = 0;
	int n = 0;
	uint8_t *buffer = malloc(sizeof(uint8_t) *5);
	*(buffer + 0) = (address | COMMAND_BIT);
	*(buffer + 1) = ((data));

	fptr = open(light_i2c_path_name,O_RDWR);	
	if(fptr == -1){
		perror("Error in opening the file");
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,LIGHT_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		return WRITE_REG_FAIL;
	}
	n = write(fptr,buffer,2);
	if(n ==-1){
		perror("Write not successfull");
		return WRITE_REG_FAIL;
	}
	close(fptr);
	free(buffer);
	return WRITE_REG_SUCCESS;
}

/***********************************************************************************************  
 * @brief Read register in light sensor 
 *
 *Responsible for reading from register of light sensor
 *
 * @param address: address of  register  of light sensor
 * @param data: data to be read from register of light sensor
 * @param command: Bits to be read from particular register from light sensor
 * @return status of I2C operation
 *********************************************************************************************/


sensor_status_t light_read_reg(uint8_t address, uint8_t *data,read_cmd_t command){
	int status =0;
	int fptr = 0;
	int n = 0;
	address = address | COMMAND_BIT;
	fptr = open(light_i2c_path_name,O_RDWR);	
	if(fptr == -1){
		perror("Error in opening the file");
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,LIGHT_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		return WRITE_REG_FAIL;
	}
	n =write(fptr,&address,1);
	if(n==-1){
		perror("Write not successfull");
		return WRITE_REG_FAIL;
	}

	n = read(fptr,(data ),1);
	if(n ==-1){
		perror("Read not successfull");
		return READ_REG_FAIL;
	}

	if(command == INTEGRATION_TIME){
		*data = *data & 0x03;
	}
	else if(command == GAIN){
		*data = (*data & 0x10) >> 4;
	}
	else{
		*data = *data;
	}

	close(fptr);
	return READ_REG_SUCCESS;

}
/***********************************************************************************************
 * @brief Read two register in light sensor 
 *
 *Responsible for reading from two  register of light sensor
 *
 * @param address: address of  register  of light sensor
 * @param data: data to be read from register of light sensor
 * @param command: Bits to be read from particular register from light sensor
 * @return status of I2C operation
 *********************************************************************************************/


sensor_status_t read_two_reg(uint8_t address, uint8_t *data){
	int status =0;
	int fptr = 0;
	int n =0;
	address = address | COMMAND_BIT | WORD_OPERATION_BIT;
	fptr = open(light_i2c_path_name,O_RDWR);
	if(fptr ==-1){
		perror("Error in opening the file");
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,LIGHT_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		return WRITE_REG_FAIL;

	}
	n =write(fptr,&address,1);
	if(n==-1){
		perror("Write not successfull");
		return WRITE_REG_FAIL;

	}
	n = read(fptr,data,2);
	if(n == -1){
		perror("read not successfull");
		return READ_REG_FAIL;

	}
	close(fptr);
	return READ_REG_SUCCESS;
}

/***********************************************************************************************
 * @brief Read lux values 
 *
 *Responsible for reading lux value from light sensor
 *
 * @param null
 * @return double: Returns the lux values from light sensor
 *********************************************************************************************/


double read_lux(){
	pthread_mutex_lock(&i2c_mutex);

	uint8_t *data = malloc(sizeof(uint8_t)*2);
	int status = 0;
	status = read_two_reg(DATA1LOW_REG,data);
	if(status != READ_REG_SUCCESS){
		perror("Reading Channel 1 data register failed");
	}
	unsigned int ch1Int = (*(data +1)<<8) | *(data +0);
	status = read_two_reg(DATA0LOW_REG,data);
	if(status !=READ_REG_SUCCESS){
		perror("Reading Channel 0 data register failed");
	}
	unsigned int ch0Int =  (*(data +1)<<8) | *(data +0);

	status = read_two_reg(DATA0LOW_REG,data);
	if(status !=READ_REG_SUCCESS){
		perror("Reading channel 0 data register failed(floating values)");
	}
	float ch0 = (float)( (*(data +1)<<8) | *(data +0));

	status = read_two_reg(DATA1LOW_REG,data);
	if(status != READ_REG_SUCCESS){
		perror("Reading channel 1 data register failed(floating value)");
	}
	float ch1 = (float)( (*(data +1)<<8) | *(data +0));

	status = light_read_reg(TIMING_REG,data,INTEGRATION_TIME);
	if(status!= READ_REG_SUCCESS){
		perror("Reading integration time failed");

	}
	switch (*data)
	{
		case INTEGRATION_13_7:

			if ((ch1Int >= 5047) || (ch0Int >= 5047)) 
			{
				return 1.0/0.0;
			}
			break;
		case INTEGRATION_101:
			if ((ch1Int >= 37177) || (ch0Int >= 37177)) 
			{
				return 1.0/0.0;
			}
			break;
		case INTEGRATION_402:
			if ((ch1Int >= 65535) || (ch0Int >= 65535))
			{ 
				return 1.0/0.0;
			}
			break;
	}
	float ratio = ch1/ch0;
	status = light_read_reg(TIMING_REG,data,INTEGRATION_TIME);
	if(status!=READ_REG_SUCCESS){
		perror("Reading integration time failed");
	}
	switch (*data)
	{
		case INTEGRATION_13_7:
			ch0 *= 1/0.034;
			ch1 *= 1/0.034;
			break;
		case INTEGRATION_101:
			ch0 *= 1/0.252;
			ch1 *= 1/0.252;
			break;
		case INTEGRATION_402:
			ch0 *= 1;
			ch1 *= 1;
			break;

	}
	status = light_read_reg(TIMING_REG,data,GAIN);
	if (*data ==( (LOW_GAIN)>>4U)) 
	{
		ch0 *= 16;
		ch1 *= 16;
	}

	float luxVal = 0.0;
	if (ratio <= 0.5)
	{
		luxVal = (0.0304 * ch0) - ((0.062 * ch0) * (pow((ch1/ch0), 1.4)));
	}  
	else if (ratio <= 0.61)
	{
		luxVal = (0.0224 * ch0) - (0.031 * ch1);
	}
	else if (ratio <= 0.8)
	{
		luxVal = (0.0128 * ch0) - (0.0153 * ch1);
	}
	else if (ratio <= 1.3)
	{
		luxVal = (0.00146 * ch0) - (0.00112*ch1);
	}

	free(data);
	pthread_mutex_unlock(&i2c_mutex);

	return luxVal;
//	return 0;



}

/***********************************************************************************************  
 * @brief Power on light sensor 
 *
 *Responsible for turning On light sensor before reading any data
 *
 * @param  null
 *
 * @return null
 *********************************************************************************************/


sensor_status_t light_sensor_power_on(){
	pthread_mutex_lock(&i2c_mutex);

	sensor_status_t status;
	status = light_write_reg(CONTROL_REG,0x03);
	if(status!=WRITE_REG_SUCCESS){
	perror("Writing power on bit in Control register failed");
	return WRITE_REG_FAIL; 
	}
	
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;
}


/***********************************************************************************************  
 * @brief Set Integration Time 
 *
 *Responsible for setting up integration time based on INTEGRATION values
 *
 * @param INTEGRATION
 *
 * @return status of I2C operation
 *********************************************************************************************/
sensor_status_t set_integration_time(uint8_t INTEGRATION)
{
	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t));
	sensor_status_t status = light_read_reg(TIMING_REG,data,NONE); // check data arg
	*data &= ~0x03;	//check if required
	if(status != READ_REG_SUCCESS){
		perror("Reading register for time integration failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
		//Should set a flag and return as required: error/success, to avoid deadlock
	}

	if( INTEGRATION == INTEGRATION_13_7 )
	{
		*data |= 0x00;
	}
	else if( INTEGRATION == INTEGRATION_101 )
	{
		*data |= 0x01;
	}
	else if( INTEGRATION == INTEGRATION_402 )
	{
		*data |= 0x02;
	}

	status = light_write_reg(TIMING_REG, *data); //check data arg
	if(status != WRITE_REG_SUCCESS){
		perror("Writing register for integration time failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}

	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;
}

/***********************************************************************************************  
 * @brief Read identification register 
 *
 *Responsible for reading identification register 
 *
 * @param null
 *
 * @return uint8_t returns the identification value
 *********************************************************************************************/
sensor_status_t read_identification_reg(uint8_t *data){
	sensor_status_t status = 0;
	pthread_mutex_lock(&i2c_mutex);
	
	//uint8_t *data = malloc(sizeof(uint8_t));
	status = light_read_reg(ID_REG,data,ALL);
	if(status != READ_REG_SUCCESS)
	{
		perror("Reading register for identification failed");
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
		//Should set a flag and return as required: error/success, to avoid deadlock
	}
	*data = *data >>4;
	pthread_mutex_unlock(&i2c_mutex);
	return READ_REG_SUCCESS;



}

/***********************************************************************************************  
 * @brief Get Integration Time 
 *
 *Responsible for retrieivng set integration 
 *
 * @param null
 *
 * @return status of I2C operation
 *********************************************************************************************/

// i think this function is not required
sensor_status_t get_integration_time(uint8_t *data)
{
	pthread_mutex_lock(&i2c_mutex);
	//uint8_t *data = malloc(sizeof(uint8_t));
	sensor_status_t status = light_read_reg(TIMING_REG,data,INTEGRATION_TIME); // check data arg
	if(status != READ_REG_SUCCESS){
		perror("Reading register for time integration failed");
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	// check if printing is OK!
	/*if( *data == 0x00 )
		printf("\nIntegration time = 13.7ms");
	else if( *data == 0x01 )
		printf("\nIntegration time = 101ms");
	else if( *data == 0x02 )
		printf("\nIntegration time = 402ms");
*/
	pthread_mutex_unlock(&i2c_mutex);
	return READ_REG_SUCCESS;

}


/***********************************************************************************************  
 * @brief Set gain 
 *
 * Responsible for setting gain values. Switches gain between low gain and high gain modes. 
 * Writing a 0 selects low gain (1x); writing a 1 selects high gain (16x). 
 *
 * @param gainlevel
 *
 * @return status of I2C operation
 *********************************************************************************************/
sensor_status_t set_gain( int gainlevel )
{
	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t));
	sensor_status_t status = light_read_reg(TIMING_REG,data,NONE); // check data arg
	if(status != READ_REG_SUCCESS){
		perror("Reading register for Setting gain failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	if( gainlevel == LOW_GAIN )
		*data &= ~0x10;
	else if( gainlevel == HIGH_GAIN )
		*data |= 0x10;

	status = light_write_reg(TIMING_REG, *data); //check data arg
	if(status != WRITE_REG_SUCCESS){
		perror("Writing register for Setting gain failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}
	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;
}
/***********************************************************************************************  
 * @brief Get gain 
 *
 *Responsible for retrieivng gain
 *
 * @param null
 *
 * @return status of I2C operation
 *********************************************************************************************/

// i think this function is not required
sensor_status_t get_gain(uint8_t *data)
{
	pthread_mutex_lock(&i2c_mutex);
	//uint8_t *data = malloc(sizeof(uint8_t));
	sensor_status_t status = light_read_reg(TIMING_REG,data,GAIN); // check data arg
	if(status != READ_REG_SUCCESS){
		perror("Reading register for gain failed");
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	// check if printing is OK!
	/*if( *data == 0x00 )
		printf("\nIntegration time = 13.7ms");
	else if( *data == 0x01 )
		printf("\nIntegration time = 101ms");
	else if( *data == 0x02 )
		printf("\nIntegration time = 402ms");
*/
	pthread_mutex_unlock(&i2c_mutex);
	return READ_REG_SUCCESS;

}


/***********************************************************************************************  
 * @brief Configure Interrupt Controller Register
 *
 * Enables/Disables Interrupt through Interrupt Controller Register
 *
 * @param interrupt_cmd_t command
 *
 * @return status of I2C operation
 *********************************************************************************************/
sensor_status_t config_interrupt_ctrl_reg( uint8_t command )
{
	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data = malloc(sizeof(uint8_t));
	sensor_status_t status = light_read_reg(INTERRUPT_REG,data,NONE);	
	if(status != READ_REG_SUCCESS){
		perror("Reading register for Configuring Interrupt failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

	if (command == INTERRUPT_OFF )
		*data &= ~0x30;
	else if (command == INTERRUPT_ON )
		*data |= 0x10;

	status = light_write_reg(INTERRUPT_REG, *data); //check data arg
	if(status != WRITE_REG_SUCCESS){
		perror("Writing register for Configuring Interrupt failed");
		free(data);
		pthread_mutex_unlock(&i2c_mutex);
		return WRITE_REG_FAIL;
	}
	free(data);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;
}

/***********************************************************************************************  
 * @brief Get value of Interrupt control Register 
 *
 *Responsible for retrieving value of Interrupt Control Register
 *
 * @param null
 *
 * @return status of I2C operation
 *********************************************************************************************/

// i think this function is not required
sensor_status_t get_interrupt_ctrl_reg(uint8_t *data)
{
	pthread_mutex_lock(&i2c_mutex);
	//uint8_t *data = malloc(sizeof(uint8_t));
	sensor_status_t status = light_read_reg(INTERRUPT_REG,data,NONE); // check data arg
	if(status != READ_REG_SUCCESS){
		perror("Reading register for gain failed");
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}

	// check if printing is OK!
	/*if( *data == 0x00 )
		printf("\nIntegration time = 13.7ms");
	else if( *data == 0x01 )
		printf("\nIntegration time = 101ms");
	else if( *data == 0x02 )
		printf("\nIntegration time = 402ms");
*/
	pthread_mutex_unlock(&i2c_mutex);
	return READ_REG_SUCCESS;

}

/***********************************************************************************************  
 * @brief Read low threshold
 *
 * Registers THRESHLOWLOW and THRESHLOWHIGH provide the low byte and
 * high byte, respectively, of the lower interrupt threshold
 *
 * @param uint16_t *data
 *
 * @return status of I2C operation
 *********************************************************************************************/
sensor_status_t get_low_threshold(uint16_t *data)
{
	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data_low = malloc(sizeof(uint8_t));
	sensor_status_t status = light_read_reg(THRESHLOWLOW_REG, data_low, NONE);	
	if(status != READ_REG_SUCCESS){
		perror("Reading register for getting low threshold value failed");
		free(data_low);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	//*data <<= 8;

	uint8_t *data_high = malloc(sizeof(uint8_t));
	status = light_read_reg(THRESHLOWHIGH_REG,data_high, NONE);
	if(status != READ_REG_SUCCESS){
		perror("Reading register for getting low threshold value failed");
		free(data_low);
		free(data_high);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	*data = *data_high << 8 | *data_low ;
	free(data_low);
	free(data_high);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;
}


/***********************************************************************************************  
 * @brief Read high threshold
 *
 * Registers THRESHIGHLOW and THRESHHIGHHIGH provide the low byte and
 * high byte, respectively, of the lower interrupt threshold
 *
* @param uint16_t *data
 *
 * @return status of I2C operation
 *********************************************************************************************/
sensor_status_t get_high_threshold(uint16_t *data)
{
	pthread_mutex_lock(&i2c_mutex);
	uint8_t *data_low = malloc(sizeof(uint8_t));
	sensor_status_t status = light_read_reg(THRESHHIGHLOW_REG, data_low, NONE);	
	if(status != READ_REG_SUCCESS){
		perror("Reading register for getting high threshold value failed");
		free(data_low);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	//*data <<= 8;

	uint8_t *data_high = malloc(sizeof(uint8_t));
	status = light_read_reg(THRESHHIGHHIGH_REG,data_high, NONE);
	if(status != READ_REG_SUCCESS){
		perror("Reading register for getting high threshold value failed");
		free(data_low);
		free(data_high);
		pthread_mutex_unlock(&i2c_mutex);
		return READ_REG_FAIL;
	}
	*data = *data_high << 8 | *data_low ;
	free(data_low);
	free(data_high);
	pthread_mutex_unlock(&i2c_mutex);
	return WRITE_REG_SUCCESS;
}


