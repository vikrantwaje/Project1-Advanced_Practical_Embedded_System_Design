/********************************************************************************************
*					FILENAME: led.h
**********************************************************************************************/
/* Title: led.h
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
#ifndef LED_H_
#define LED_H_

#include <stdio.h>
#include<string.h>
#include<stdint.h>
/**************************************************************************************
*					     MACROS
****************************************************************************************/
#define RED_LED  ("49")
#define BLUE_LED ("117")
#define GREEN_LED ("115")
#define YELLOW_LED ("44")
/**************************************************************************************
*					GLOBAL VARIABLES
****************************************************************************************/

/**************************************************************************************
*					FUNCTION PROTOTYPE
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

void led_init(uint8_t gpio_pin[]);


/*******************************************************************************************
 * @brief Turn ON the led
 *
 * Turn the given LED ON, i.e output logic 1
 *
 * @param gpio_pin: GPIO pin which is to be turned ON
 *
 * @return null
 ********************************************************************************************/

void led_on(uint8_t gpio_pin[]);


/*******************************************************************************************
 * @brief Turn OFF the led
 *
 * Turn the given LED OFF, i.e output logic 0
 *
 * @param gpio_pin: GPIO pin which is to be turned OFF
 *
 * @return null
 ********************************************************************************************/
void led_off(uint8_t gpio_pin[]);

#endif /*LED_H*/	
