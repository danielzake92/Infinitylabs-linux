/*****************************************************************************
*	FILENAME:	dir_monitor_test.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for dir_monitor lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout

#include "tester.hpp" // test utills

#include "dir_monitor.hpp"

using namespace ilrd_rd100;
/********************************* driver ************************************/
int main(void)
{

	DirMonitor dir_monitor("./test_dir");
	DsoLoader dso_loader(&dir_monitor);

	sleep(3);

	dir_monitor.Stop();

	// test results
	TestReport("dir_monitor_test.cpp TEST");

	return 0;
}
/*****************************************************************************/
