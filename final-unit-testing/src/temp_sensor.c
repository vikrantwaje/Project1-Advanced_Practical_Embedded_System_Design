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



/*********************************************************************************************** 
 * @brief Get temperature
 *
 * Read the value from temperature register
 *
 * @param request: Temperature value in kelvin, celsius and farhenheit to be returned
 * @return double: Value of converted temperature
 *********************************************************************************************/


double get_temperature(request_cmd_t request, uint16_t raw_data){
	//double result = 0;
	double multiplier =0;
	uint8_t *data = malloc(sizeof(uint8_t) * 2);
	if ( data == NULL )
	{
		return READ_REG_FAIL;
	}
   // multiplier = 0.0625;	


    *(data + 0) = (raw_data & 0x00FF);
    *(data + 1) = (raw_data & 0xFF00) >> 8;
	int32_t digitalTemp =0;

	// Bit 0 of second byte will always be 0 in 12-bit readings and 1 in 13-bit
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

//	printf("Digital = %ld\n", digitalTemp);
	if ( request == REQUEST_KELVIN )
	{
		return(digitalTemp + 273.15);		
	}
	else if ( request == REQUEST_FAHRENHEIT )
	{
		return ((digitalTemp * 9.0/5.0) + 32.0);
	}
	else
	{
	//	printf("return = %lf\n", digitalTemp);
		return(digitalTemp);
	}
}

