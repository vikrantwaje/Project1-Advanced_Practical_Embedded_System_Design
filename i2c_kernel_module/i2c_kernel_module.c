/********************************************************************************************
*					FILENAME: i2c_kernel_module.c
**********************************************************************************************/
/* Title: i2c_kernel_module.c
 * Brief: Responsible for providing various kernel function needed to communicate with 
 * I2C-based sensor.
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 26, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: https://github.com/torvalds/linux/blob/master/include/linux/i2c.h
 * Reference[2]: https://gist.github.com/jnewc/f8b668c41d7d4a68f6e46f46e8c559c2
 * Reference[3]: https://stackoverflow.com/questions/23979129/i2c-device-linux-driver
 *
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/


#include "i2c_kernel_module.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tanmay Chaturvedi & Vikrant Waje");
MODULE_DESCRIPTION("A Kernel Module that works on I2C");
MODULE_VERSION("1.0");

/*Initialization Sequence*/

static int my_i2c_init(void)
{
	PRINTK(KERN_INFO,"Initialization I2C Driver");
	my_adapter = i2c_get_adapter(2);

	my_client = i2c_new_dummy(my_adapter, TEMP_SENSOR_I2C_ADDRESS);

	my_driver_setup();
	

	return 0;
}


static int my_driver_setup(void)
{

	static struct i2c_driver my_tmp102_driver = {
		.driver.name = I2C_DRIVER_NAME;
		.probe = my_tmp102_probe;
	}

	i2c_smbus_write_byte(my_client, 0xFF);
	int ret = i2c_smbus_read_byte(my_client);

	return ret;

}


static int my_tmp102_probe(void)
{

}

static int my_i2c_read();
{


}





static void my_i2c_exit(void)
{
 	//kfree();
}




module_init(my_i2c_init);
module_exit(my_i2c_exit);
