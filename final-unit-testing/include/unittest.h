/********************************************************************************************
*					FILENAME: unittest.h
**********************************************************************************************/
/* Title:thread.h
 * Brief: Responsible for performing unit testing using CUnit unit testing framework
 * Author: Tanmay Chaturvedi, Vikrant Waje
 * Date Created: March 26, 2019
 * Course: Advanced Embedded Software Development
 * Project: 1
 * 
 * 
 * */
/****************************************************************************************
*					HEADER FILE SECTION
*****************************************************************************************/
#ifndef SRC_UNITTEST_H_
#define SRC_UNITTEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include <CUnit/CUnit.h>
#include "main.h"
#include "ipc.h"
#include <mqueue.h>
#include "temp_sensor.h"

/**************************************************************************************
*					FUNCTION PROTOTYPE
***************************************************************************************/
int cunit_add_testsuite();
int cunit_pthread_test(void);
int cunit_ipc_test(void);
int cunit_temp_test(void);

void pthread_create_test(void);
void message_queue_open_test(void);
void message_queue_close_test(void);
void temp_conversion_test(void);


#endif