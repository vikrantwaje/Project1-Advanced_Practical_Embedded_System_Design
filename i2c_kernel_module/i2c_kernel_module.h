#ifndef SRC_I2C_H_
#define SRC_I2C_H_


/********************************************************************************************
*					FILENAME: i2c_kernel_module.h
**********************************************************************************************/
/* Title: i2c_kernel_module.h
 * Brief: Header file for  various kernel function needed to communicate with 
 * I2C-based sensor.
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 26, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
****************************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/types.h>
#include <linux/sort.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/hwmon.h>
#include <linux/hwmon-sysfs.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/jiffies.h>
#include <linux/regmap.h>
#include <linux/of.h>

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

#define I2C_DRIVER_NAME	("TMP102_DRIVER")


#define READ_TEMPERATURE_ERROR	(double)(-56.000000)

typedef enum{
	REQUEST_CELSIUS, REQUEST_KELVIN, REQUEST_FAHRENHEIT
}request_cmd_t;


typedef enum{
	FAULT,EM,CONVERSION_RATE,SD_MODE,RESOLUTION,ALL
}reg_read_cmd_t;


/****************************************************************************************
 *					FUNCTION PROTOTYPES
 *****************************************************************************************/
static void my_i2c_init(void)
static void my_i2c_exit(void);
static int my_driver_setup(void);
static int my_tmp102_probe(void);
static int my_i2c_read(void);




/****************************************************************************************
 *					GLOBAL
 *****************************************************************************************/
static struct i2c_client *my_client;
static struct i2c_adapter *my_adapter;


#endif