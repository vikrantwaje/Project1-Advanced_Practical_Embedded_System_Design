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

#define SHUTDOWN_ON		((0x01))
#define SHUTDOWN_OFF		((0x00))

#define EM_ON			((0x01))
#define EM_OFF			((0x00))

#define FAULT_1			((0x00)) 
#define FAULT_2			((0x01))
#define FAULT_3			((0x02))
#define FAULT_4			((0x03))



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
/***********************************************************************************************
 * @brief write pointer register
 *
 *Responsible for writing into pointer registerof temperature sensor TMP102
 *
 * @param address: address of pointer register TMP102
 *
 * @return status of I2C operation
 *********************************************************************************************/


sensor_status_t write_ptr_reg(uint8_t address);

/***********************************************************************************************  * @brief write register in temperature register
 *
 *Responsible for writing into  register of temperature sensor TMP102
 *
 * @param address: address of  register  of TMP102
 * @param data: data to be written into register of TMP102
 *
 * @return status of I2C operation
 *********************************************************************************************/

sensor_status_t temperature_write_reg(uint8_t address, uint16_t data);

/***********************************************************************************************  * @brief Read register in temperature register
 *
 *Responsible for reading from  register of temperature sensor TMP102
 *
 * @param address: address of  register  of TMP102
 * @param data: data to be read from  register of TMP102
 * @param command: register bits which are to be read
 * @return status of I2C operation
 *********************************************************************************************/


sensor_status_t temperature_read_reg(uint8_t address, uint8_t *data,reg_read_cmd_t command);
/***********************************************************************************************  * @brief Get temperature
 *
 * Read the value from temperature register
 *
 * @param request: Temperature value in kelvin, celsius and farhenheit to be returned
 * @return double: Value of converted temperature
 *********************************************************************************************/


double get_temperature(request_cmd_t request);

/***********************************************************************************************  
* @brief Get Tlow register
 *
 * Read the value from tlow register
 *
 * @param request: Temperature value in kelvin, celsius and farhenheit to be returned
 * @return double: Value of converted temperature
 *********************************************************************************************/


double get_Tlow(request_cmd_t request);



/***********************************************************************************************  
* @brief Get Thigh register
 *
 * Read the value from thigh register
 *
 * @param request: Temperature value in kelvin, celsius and farhenheit to be returned
 * @return double: Value of converted temperature
 *********************************************************************************************/


double get_Thigh(request_cmd_t request);


/*********************************************************************************************** 
 * @brief set sensor in shutdown mode
 *
 * set the configuration register in shutdown mode
 *
 * @param :null
 * @return :status of I2C operation
 *********************************************************************************************/

sensor_status_t configure_temp_shutdown(void);


/*********************************************************************************************** 
 * @brief Read fault bits from configuration register
 *
 *  Read fault bits
 *
 * @param :uint8_t* data
 * @return :status of I2C operation
 *********************************************************************************************/


sensor_status_t read_temp_fault(uint8_t *data);


/*********************************************************************************************** 
 * @brief set sensor in EM mode
 *
 * set the configuration register in EM mode
 *
 * @param :mode
 * @return :status of I2C operation
 *********************************************************************************************/

sensor_status_t configure_temp_EMmode(uint8_t mode);


/*********************************************************************************************** 
 * @brief Read EM mode from configuration register
 *
 *  Read Em mode bits
 *
 * @param :uint8_t *data
 * @return :status of I2C operation
 *********************************************************************************************/


sensor_status_t read_temp_EM(uint8_t *data);


/*********************************************************************************************** 
 * @brief set sensor conversion rate
 *
 * set the conversion rate of temperature sensor
 *
 * @param :data: To Set the conversion rate
 * @return :status of I2C operation
 *********************************************************************************************/


sensor_status_t configure_temp_conversion_rate(uint8_t rate);


/*********************************************************************************************** 
 * @brief Read conversion rate from configuration register
 *
 *  Read Conversion rate
 *
 * @param :uint8_t *data
 * @return :status of I2C operations
 *********************************************************************************************/

sensor_status_t read_temp_conversion_rate(uint8_t *data);



#endif	//SRC_TEMP_H_
