/*****************************************************************************
*	FILENAME:	master.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for master lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout

#include "master.hpp"
#include "tester.hpp" // test utills

using namespace ilrd_rd100;
/********************************* driver ************************************/
const char * LOG_PATH = "./test/log";

DirMonitor m_dir("./test/shared_object");
Logger *s_log = Singleton<Logger>::Handleton();
//ThreadPool *pool = Singleton<ThreadPool>::Handleton();
int main(void)
{
	s_log->Log("Master(INFO) : main()\n", Logger::INFO);

	boost::shared_ptr<InputProxy> proxy(InputProxy::Create());
	InputMediator mediator(proxy.get(), STDIN_FILENO);

	
	mediator.Run();

	TestReport("master.cpp TEST");

	return 0;
}
/*****************************************************************************/
