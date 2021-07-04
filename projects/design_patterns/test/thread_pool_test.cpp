/*****************************************************************************
*	FILENAME:	thread_pool_test.cpp      AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			 
 *	REVIEWER:	Or Katz															 
 *																			 
 *	PURPOSE:    Testing for thread_pool lib.							     
 *																			 
 *****************************************************************************/

#include <iostream> //std::cout

#include "thread_pool.hpp" //thread pool api
#include "tester.hpp" //tester utils

using namespace ilrd_rd100;

int testCounter = 0;
boost::mutex mut;

class MyTask: public ThreadPool::Task
{
public:
    virtual ~MyTask()
    {
        //EMPTY
    }
    virtual void operator()()
    {
        boost::mutex::scoped_lock lock(mut);
        
        ++testCounter;
        // write(STDOUT_FILENO,"Task has been completed\n", 24);
    }
};


int main()
{
    ThreadPool pool(1);
    boost::shared_ptr<MyTask> task1(new MyTask);
    pool.Add(task1,ThreadPool::LOW);
    pool.Add(task1,ThreadPool::LOW);
    pool.Add(task1,ThreadPool::LOW);
    pool.Add(task1,ThreadPool::LOW);

    pool.Run();
    pool.Run();


    pool.SetNumOfThreads(30);
    pool.SetNumOfThreads(3);
    // pool.SetNumOfThreads(10);
    // pool.SetNumOfThreads(5);

    sleep(1);
    pool.Stop();
    pool.Stop();

    boost::mutex::scoped_lock lock(mut);
    std::cout <<  "testCounter = " << testCounter << std::endl;
    Test((int)testCounter, 4, "tasks run", __LINE__);

    TestReport("Thread Pool");

    return 0;
}