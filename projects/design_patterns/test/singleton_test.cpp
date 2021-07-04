/*****************************************************************************
*	FILENAME:	singleton_test.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for singleton lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <iostream> //cout, endl
#include <boost/thread.hpp> //thread
#include <boost/thread/mutex.hpp> //mutex

#include "singleton.hpp"
#include "tester.hpp"

using namespace ilrd_rd100;

boost::mutex g_lock;

class X
{
public:
    int GetA() {return m_a;}
    double GetB() {return m_b;}
    void SetA(int a) {m_a = a;}
    void SetB(double b) {m_b = b;}
private:
    int m_a;
    double m_b;
};

class ThreadFunc
{
public:
    void operator()()
    {         
        int* ptr1 = Singleton<int>::Get();
        boost::mutex::scoped_lock lock(g_lock);

        *ptr1 = 1;
    }
};


int main()
{

    X *ptr = Singleton<X>::Get();
    X *ptr2 = Singleton<X>::Get();
    int *ptr3 = Singleton<int>::Get();



    ptr->SetA(3);
    ptr2->SetB(5.0);
    std::cout << ptr->GetA() << " " << ptr2->GetA() << std::endl;
    std::cout << ptr->GetB() << " " << ptr2->GetB() << std::endl;

    *ptr3 = 4;
    ThreadFunc func;
    boost::thread thread(func);
    while(1)
    {
        boost::mutex::scoped_lock lock(g_lock);
        if (1 == *ptr3)
        {
            break;
        }
    }

    thread.join();

    return 0;
}