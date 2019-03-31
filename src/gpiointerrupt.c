/********************************************************************************************
 *					FILENAME: gpiointerrupt.c
 **********************************************************************************************/
/* Title bist.c
 * Brief: Contains function that are used for built in self test
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 16, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1

 * Reference[1]: http://www.
 * 
 * 
 * */
/****************************************************************************************
 *					HEADER FILE SECTION
 *****************************************************************************************/
#include "gpiointerrupt.h"

int IRQ_handler(void)
{
	struct pollfd filedes[1];

	filedes[0].fd = open("/sys/class/gpio/gpio20/value", O_RDONLY);
    int ret_val;

	ret_val = poll( filedes, NUM_FD, TIMEOUT_MSECS );

	return ret_val;
	
}