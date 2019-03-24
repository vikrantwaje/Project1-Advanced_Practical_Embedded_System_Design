#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

/********************************************************************************************
*					FILENAME: light_sensor.h
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
#include<math.h>
#include"i2c_status.h"
#include"logger.h"
#include"server.h"
#include"ipc.h"
/***************************************************************************************
*					MACROS AND ENUMS
****************************************************************************************/


typedef enum{
	INTEGRATION_TIME, GAIN
}read_cmd_t;

#define LIGHT_SENSOR_I2C_ADDRESS (0x39)
#define CONTROL_REG	 	(0x00)
#define TIMING_REG		(0x01)
#define THRESHLOWLOW_REG	(0x02)
#define THRESHLOWHIGH_REG	(0x03)
#define THRESHHIGHLOW_REG	(0x04)
#define THRESHHIGHHIGH_REG	(0x05)
#define INTERRUPT_REG		(0x06)
#define CRC			(0x08)
#define ID_REG			(0x0A)
#define DATA0LOW_REG		(0x0C)
#define DATA0HIGH_REG		(0x0D)
#define DATA1LOW_REG		(0x0E)
#define DATA1HIGH_REG		(0x0F)

#define	INTEGRATION_13_7	((0x00))
#define INTEGRATION_101		((0x01))
#define INTEGRATION_402		((0x02))

#define LOW_GAIN		((0x00)<<4U)
#define HIGH_GAIN		((0x01)<<4U)


#define COMMAND_BIT		(0x80)
#define WORD_OPERATION_BIT	(0x20)

/***************************************************************************************
*				GLOBAL VARIABLE SECTION
****************************************************************************************/
/*************************************************************************************
*				FUNCTION PROTOTYPE
*****************************************************************************************/
/***********************************************************************************************  * @brief write register in light sensor 
 *
 *Responsible for writing into  register of light sensor
 *
 * @param address: address of  register  of light sensor
 * @param data: data to be written into register of light sensor
 *
 * @return status of I2C operation
 *********************************************************************************************/
sensor_status_t light_write_reg(uint8_t address, uint8_t data);

/***********************************************************************************************  * @brief Read register in light sensor 
 *
 *Responsible for reading from register of light sensor
 *
 * @param address: address of  register  of light sensor
 * @param data: data to be read from register of light sensor
 * @param command: Bits to be read from particular register from light sensor
 * @return status of I2C operation
 *********************************************************************************************/
sensor_status_t light_read_reg(uint8_t address, uint8_t *data,read_cmd_t command);

/***********************************************************************************************  * @brief Read two register in light sensor 
 *
 *Responsible for reading from two  register of light sensor
 *
 * @param address: address of  register  of light sensor
 * @param data: data to be read from register of light sensor
 * @param command: Bits to be read from particular register from light sensor
 * @return status of I2C operation
 *********************************************************************************************/

sensor_status_t read_two_reg(uint8_t address, uint8_t *data);
/***********************************************************************************************  * @brief Read lux values 
 *
 *Responsible for reading lux value from light sensor
 *
 * @param null
 * @return double: Returns the lux values from light sensor
 *********************************************************************************************/
double read_lux();

/***********************************************************************************************  
 * @brief Power on light sensor 
 *
 *Responsible for turning On light sensor before reading any data
 *
 * @param  null
 *
 * @return null
 *********************************************************************************************/

sensor_status_t light_sensor_power_on();



#endif	//SRC_LIGHT_H_
