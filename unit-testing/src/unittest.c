/********************************************************************************************
*					FILENAME: unittest.c
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
/**********************************************************************************************
*					HEADER FILE SECTION
***********************************************************************************************/
#include "../include/unittest.h"


int main()
{
	if( CU_initialize_registry() == CUE_NOMEMORY )
	{
		return CU_get_error();
	}
	
	if( cunit_add_testsuite() == 0 )
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode( CU_BRM_VERBOSE );

	CU_basic_run_tests();

	CU_automated_run_tests();

	CU_cleanup_registry();

	return CU_get_error();
}


/**********************************************************************************************
*				FUNCTION DEFINITION
***********************************************************************************************/

int cunit_add_testsuite(void)
{
	CU_pSuite pSuite_temp, pSuite_light, pSuite_logger = NULL;
	pSuite_temp = CU_add_suite( "BeagleBone Linux Testing - Temperature Sensor Task", cunit_temp_test, NULL );

	if( pSuite_temp == NULL )
	{
		return 0;
	}

	pSuite_light = CU_add_suite( "BeagleBone Linux Testing - Light Sensor Task", cunit_light_test, NULL );

	if( pSuite_light == NULL )
	{
		return 0;
	}

	pSuite_logger = CU_add_suite( "BeagleBone Linux Testing - Logger Task", cunit_logger_test, NULL );

	if( pSuite_logger == NULL )
	{
		return 0;
	}

	if( ( CU_add_test(pSuite_temp, "Temperature Sensor Write-to-Register Test", temp_write_test ) == NULL ) || \
		( CU_add_test(pSuite_temp, "Temperature Sensor Read-from-Register Test", temp_read_test ) == NULL ) )
	{
		return 0;
	}	

	if( ( CU_add_test(pSuite_light, "Light Sensor Write-to-Register Test", light_write_test ) == NULL ) || \
		( CU_add_test(pSuite_light, "Light Sensor Read-from-Register Test", light_read_test ) == NULL ) )
	{
		return 0;
	}

	return 1;
}



int cunit_temp_test(void)
{
	return 0;
}

int cunit_light_test(void)
{
	return 0;
}

int cunit_logger_test(void)
{
	return 0;
}

void temp_write_test(void)
{

}

void temp_read_test(void)
{

}

void light_write_test(void)
{

}

void light_read_test(void)
{

}

