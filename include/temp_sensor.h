#ifndef SRC_TEMP_H_
#define SRC_TEMP_H_
/********************************************************************************************
*					FILENAME:temp_sensor.h
**********************************************************************************************/
/*
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: http://www.it.uom.gr/teaching/distrubutedSite/dsIdaLiu/labs/lab2_1/sockets.html
 * Reference[2]: Based on code from https://riptutorial.com/posix/example/16306/posix-timer-with-sigev-thread-notification
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

#define CONVERSION_RATE_0_25	((0x00)<<6U)
#define CONVERSION_RATE_1	((0x01)<<6U)
#define CONVERSION_RATE_4	((0x02)<<6U)
#define CONVERSION_RATE_8	((0x03)<<6U)

#define SHUTDOWN_ON		((0x01)<<8U)
#define SHUTDOWN_OFF		((0x00)<<8U)

#define EM_ON			((0x01)<<4U)
#define EM_OFF			((0x00)<<4U)

#define FAULT_1			((0x00)<<11U) 
#define FAULT_2			((0x01)<<11U)
#define FAULT_3			((0x02)<<11U)
#define FAULT_4			((0x03)<<11U)



typedef enum{
	REQUEST_CELSIUS, REQUEST_KELVIN, REQUEST_FARHENHEIT
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


#endif	//SRC_TEMP_H_
