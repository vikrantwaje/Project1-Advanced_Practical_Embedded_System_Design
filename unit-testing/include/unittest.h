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


/**************************************************************************************
*					FUNCTION PROTOTYPE
***************************************************************************************/
int cunit_add_testsuite();
int cunit_temp_test(void);
int cunit_light_test(void);
int cunit_logger_test(void);

void temp_write_test(void);
void temp_read_test(void);
void light_write_test(void);
void light_read_test(void);


#endif