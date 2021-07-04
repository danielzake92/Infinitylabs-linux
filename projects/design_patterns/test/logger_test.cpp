/*****************************************************************************
*	FILENAME:	logger_test.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 
 *																		
 *	REVIEWER:															
 *																		
 *	PURPOSE:    Testing for logger lib.							      	 
 *																		
 *****************************************************************************/

#include <iostream> // cout

#include "tester.hpp" // test utills

#include "logger.hpp"

using namespace ilrd_rd100;
/********************************* driver ************************************/
int main(void)
{
	Logger log("./log", Logger::CRITICAL);

	log.Log("hello logger its me\n",Logger::CRITICAL );
	log.Log("hello ddddd\n",Logger::CRITICAL );
	log.Log("yey ddddd\n",Logger::ERROR );


	// test results
	TestReport("logger_test.cpp TEST");

	return 0;
}
/*****************************************************************************/
