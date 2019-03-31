/********************************************************************************************
 *					FILENAME: gpiointerrupt.c
 **********************************************************************************************/
/* Title bist.c
 * Brief: Contains function that are used for built in self test
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: Mastering in Embedded Linux Book
 * 
 * 
 * */
/****************************************************************************************
 *					HEADER FILE SECTION
 *****************************************************************************************/
#include "gpiointerrupt.h"

/****************************************************************************************
 *					GLOBAL SECTION
 *****************************************************************************************/

int file_gpio;
char val[4];
struct pollfd filedes[1];

/***********************************************************************************************
 * @brief IRQ handler
 *
 * Handler that returns state of GPIO pin 
 * @param null
 *
 * @return char
 *********************************************************************************************/

char IRQ_handler(void)
{
	int ret = 0;

	ret = poll( filedes , 1, 10);
	printf("Ret %d",ret);
	ret = read(file_gpio, val, sizeof(val));
	if( ret > 0)
	{
		printf(" Value = %c\n", val[0]);
		lseek(file_gpio, 0 , SEEK_SET);
	}



	/*if( ret > 0 )
	{
		ret = read(file_gpio, &val, sizeof(val));
		printf("Value = %c",val[0]);
		lseek(file_gpio,0,SEEK_SET);
	}*/		
	
	printf("returning = %c", val[0]);
	return val[0];
	
}

/***********************************************************************************************
 * @brief GPIO initilisation function
 *
 * Initialises GPIO pin
 * @param null
 *
 * @return int: error status
 *********************************************************************************************/
int GPIO_init(void)
{
	int ret = 0;
	FILE *export_file = NULL;
	char gpio_pin[] = "60";
	export_file = fopen("/sys/class/gpio/export","w");	//go to export directory
	fwrite(gpio_pin,1,sizeof(gpio_pin),export_file);
	fclose(export_file);
	
	file_gpio = open("/sys/class/gpio/gpio60/value", O_RDONLY);

	if( file_gpio == -1 )
	{
		perror("Failed in GPIO60");
		return 1;
	} 

	ret = read(file_gpio, val, sizeof(val));
	if( ret > 0)
	{
		printf("Initial Value = %c\n", val[0]);
		lseek(file_gpio, 0 , SEEK_SET);
	}

	filedes[0].fd = file_gpio;
	filedes[0].events = POLLPRI | POLLERR;
	return 0;	
}
