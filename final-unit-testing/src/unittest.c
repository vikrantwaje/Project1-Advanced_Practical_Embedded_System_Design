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
#include <pthread.h>
#include <mqueue.h>

pthread_t thread1, thread2, thread3, thread4;
mqd_t mqdes_server;
struct mq_attr attribute_server;



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
	CU_pSuite pSuite_pthread, pSuite_ipc, pSuite_temp = NULL;

	pSuite_pthread = CU_add_suite( "BeagleBone Linux Testing - Posix Thread Creation Task", cunit_pthread_test, NULL );

	if( pSuite_pthread == NULL )
	{
		return 0;
	}

	pSuite_ipc = CU_add_suite( "BeagleBone Linux Testing - Inter Thread Communication Task", cunit_ipc_test, NULL );

	if( pSuite_ipc == NULL )
	{
		return 0;
	}

	pSuite_temp = CU_add_suite( "BeagleBone Linux Testing - Temperature conversion task", cunit_temp_test, NULL );

	if( pSuite_temp == NULL )
	{
		return 0;
	}


	if( ( CU_add_test(pSuite_pthread, "Pthread: Create and Join Test", pthread_create_test ) == NULL ) )
	{
		return 0;
	}	

	if( ( CU_add_test(pSuite_ipc, "Message Queue: Open Test", message_queue_open_test ) == NULL ) || \
		( CU_add_test(pSuite_ipc, "Message Queue: Close Test", message_queue_close_test ) == NULL ) )
	{
		return 0;
	}


	if( ( CU_add_test(pSuite_temp, "Temperature Sensor: Conversion Test", temp_conversion_test ) == NULL) )
	{
		return 0;
	}

	return 1;
}



int cunit_pthread_test(void)
{
	return 0;
}

int cunit_ipc_test(void)
{
	return 0;
}

int cunit_temp_test(void)
{
	return 0;
}

void pthread_create_test(void)
{
	CU_ASSERT_EQUAL(main_func(),PTHREAD_SUCCESS);
}

void message_queue_open_test(void)
{
	CU_ASSERT_EQUAL(open_message_queue_server(&mqdes_server, &attribute_server), MQ_SUCCESS);
}

void message_queue_close_test(void)
{
	CU_ASSERT_EQUAL(close_message_queue_server(&mqdes_server), MQ_SUCCESS);
}



void temp_conversion_test(void)
{
	CU_ASSERT_EQUAL(get_temperature(REQUEST_CELSIUS, 0x0320), 50.0);
	CU_ASSERT_EQUAL(get_temperature(REQUEST_CELSIUS, 0x04B0), 75.0);
	CU_ASSERT_EQUAL(get_temperature(REQUEST_CELSIUS, 0x0190), 25.0);
	CU_ASSERT_EQUAL(get_temperature(REQUEST_FAHRENHEIT, 0x0320), 122.0);
	CU_ASSERT_EQUAL(get_temperature(REQUEST_FAHRENHEIT, 0x04B0), 167.0);
	CU_ASSERT_EQUAL(get_temperature(REQUEST_FAHRENHEIT, 0x0190), 77.0);
	CU_ASSERT_EQUAL(get_temperature(REQUEST_KELVIN, 0x0320), 323.15);
	CU_ASSERT_EQUAL(get_temperature(REQUEST_KELVIN, 0x04B0), 348.15);
	CU_ASSERT_EQUAL(get_temperature(REQUEST_KELVIN, 0x0190), 298.15);

	CU_ASSERT_NOT_EQUAL(get_temperature(REQUEST_CELSIUS, 0x0190), 40.0);
}
