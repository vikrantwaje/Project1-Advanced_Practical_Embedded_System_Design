/********************************************************************************************
 *					FILENAME: led.c
 **********************************************************************************************/
/* Title: led.c
 * Brief: Responsible for providing various helper function needed for initializing and blinking the led
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: http://www.teachmemicro.com/beaglebone-black-blink-led-using-c/#
 * 
 * 
 * */
/****************************************************************************************
 *					HEADER FILE SECTION
 *****************************************************************************************/
#include"led.h"

/**************************************************************************************
 *					     MACROS
 ****************************************************************************************/

/**************************************************************************************
 *					     GLOBAL VARIABLES
 ****************************************************************************************/


/**************************************************************************************
 *					FUNCTION DEFINITION
 ***************************************************************************************/
/*******************************************************************************************
 * @brief Initialise LED gpio pins
 *
 * Initialise GPIO pins as output
 *
 * @param gpio_pin: GPIO pin whose direction is to be set
 *
 * @return null
 ********************************************************************************************/

void led_init(uint8_t gpio_pin[]){
	FILE *export_file = NULL;
	FILE *IO_direction = NULL;
	
	export_file = fopen("/sys/class/gpio/export","w");	//go to export directory
	fwrite(gpio_pin,1,sizeof(*gpio_pin),export_file);
	fclose(export_file);
	
	if(strcmp(gpio_pin,"49")==0){
	IO_direction = fopen("/sys/class/gpio/gpio49/direction","w");
}

	if(strcmp(gpio_pin,"117")==0){
	IO_direction = fopen("/sys/class/gpio/gpio117/direction","w");
}
	if(strcmp(gpio_pin,"115")==0){
	IO_direction = fopen("/sys/class/gpio/gpio115/direction","w");
}
	if(strcmp(gpio_pin,"44")==0){
	IO_direction = fopen("/sys/class/gpio/gpio44/direction","w");
}
	uint8_t *str = "out";
	fwrite(str,1,sizeof(str),IO_direction);
	fclose(IO_direction);
	
}


/*******************************************************************************************
 * @brief Turn ON the led
 *
 * Turn the given LED ON, i.e output logic 1
 *
 * @param gpio_pin: GPIO pin which is to be turned ON
 *
 * @return null
 ********************************************************************************************/

void led_on(uint8_t gpio_pin[]){
	uint8_t value[] ="1";
	FILE *IO_value = NULL;
	if(strcmp(gpio_pin,"49") == 0){
	IO_value = fopen("/sys/class/gpio/gpio49/value","w");
}
	else if(strcmp(gpio_pin,"117")==0){
	IO_value = fopen("/sys/class/gpio/gpio117/value","w");

}
	else if(strcmp(gpio_pin,"115")==0){
	IO_value = fopen("/sys/class/gpio/gpio115/value","w");

}
	else if(strcmp(gpio_pin,"44")==0){
	IO_value = fopen("/sys/class/gpio/gpio44/value","w");

}	
else{
	perror("The gpio pin does not exist");
}
	fwrite(value,1,sizeof(value),IO_value);
	fclose(IO_value);


}


/*******************************************************************************************
 * @brief Turn OFF the led
 *
 * Turn the given LED OFF, i.e output logic 0
 *
 * @param gpio_pin: GPIO pin which is to be turned OFF
 *
 * @return null
 ********************************************************************************************/
void led_off(uint8_t gpio_pin[]){
	uint8_t *value ="0";
	FILE *IO_value = NULL;
	if(strcmp(gpio_pin,"49") == 0){
	IO_value = fopen("/sys/class/gpio/gpio49/value","w");
}
	else if(strcmp(gpio_pin,"117")==0){
	IO_value = fopen("/sys/class/gpio/gpio117/value","w");

}
	else if(strcmp(gpio_pin,"115")==0){
	IO_value = fopen("/sys/class/gpio/gpio115/value","w");

}
	else if(strcmp(gpio_pin,"44")==0){
	IO_value = fopen("/sys/class/gpio/gpio44/value","w");

}	
else{
	perror("The gpio pin does not exist");
}
	fwrite(value,1,sizeof(value),IO_value);
	fclose(IO_value);


}
