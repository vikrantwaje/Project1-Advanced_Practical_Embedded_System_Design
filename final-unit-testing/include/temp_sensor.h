#ifndef SRC_TEMP_H_
#define SRC_TEMP_H_
/********************************************************************************************
 *					FILENAME:temp_sensor.h
 **********************************************************************************************/
/* Title: temp_sensor.h
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
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c-dev.h>
#include<stdint.h>
#include<stdlib.h>
#include"i2c_status.h"
#include"logger.h"
#include"server.h"
#include"ipc.h"
/****************************************************************************************
 *					MACROS AND ENUMS
 *****************************************************************************************/
#define TEMP_SENSOR_I2C_ADDRESS (0x48)
#define TEMPERATURE_REG		(0x00)
#define CONFIGURATION_REG	 (0x01)
#define TLOW_REG		(0x02)
#define THIGH_REG		(0x03)

#define CONVERSION_RATE_0_25	((0x00))
#define CONVERSION_RATE_1	((0x01))
#define CONVERSION_RATE_4	((0x02))
#define CONVERSION_RATE_8	((0x03))
#define CONVERSION_RATE_MASK	(0x03)


#define SHUTDOWN_ON		((0x01))
#define SHUTDOWN_OFF		((0x00))

#define EM_ON			((0x01))
#define EM_OFF			((0x00))
#define EM_MASK			(0x01)


#define FAULT_1			((0x00)) 
#define FAULT_2			((0x01))
#define FAULT_3			((0x02))
#define FAULT_4			((0x03))
#define FAULT_MASK		(0x03)

#define RESOLUTION_MASK			(0x03)
#define SENSOR_RESOLUTION_12_BIT	(0x03)

typedef enum{
	REQUEST_CELSIUS, REQUEST_KELVIN, REQUEST_FAHRENHEIT
}request_cmd_t;


typedef enum{
	FAULT,EM,CONVERSION_RATE,SD_MODE,RESOLUTION,ALL
}reg_read_cmd_t;



/****************************************************************************************
 *				GLOBAL VARIABLE SECTION
 *****************************************************************************************/


/*************************************************************************************
 *				FUNCTION PROTOTYPE SECTION
 *****************************************************************************************/

/***********************************************************************************************  * @brief Get temperature
 *
 * Read the value from temperature register
 *
 * @param request: Temperature value in kelvin, celsius and farhenheit to be returned
 * @return double: Value of converted temperature
 *********************************************************************************************/
double get_temperature(request_cmd_t request, uint16_t raw_data);



#endif	//SRC_TEMP_H_
