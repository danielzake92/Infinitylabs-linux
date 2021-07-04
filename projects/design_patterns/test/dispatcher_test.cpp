/*****************************************************************************
*	FILENAME:	dispacher_test.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for dispacher lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout
#include <boost/atomic.hpp> //atomic vars
#include <boost/thread.hpp> //thread class
#include <boost/thread/mutex.hpp> //boost:mutex 
#include <boost/shared_ptr.hpp> //shared_ptr
#include "tester.hpp" // test utills

#include "dispatcher.hpp"

using namespace ilrd_rd100;
/********************************* driver ************************************/
boost::mutex lock;
__sig_atomic_t g_counter = 0;

template <class Event>
class Add : public Callback<Event>
{
public:
	explicit Add(bool flag = false) : m_bool(flag) {/* EMPTY */}
	virtual void operator()(const Event &event)
	{
		boost::mutex::scoped_lock locker(lock);
		(void)event;
		++g_counter;
		m_bool = true;
	}

	virtual void DispatcherIsDead()
	{
		//std::cout<< "Add:dispatcher is dead" <<std::endl;
	}

	bool GetBool() const
	{
		return m_bool;
	}

	virtual ~Add()
	{
		/* EMPTY */
	}
private:
	bool m_bool;
};

template <class Event>
class ThreadFunc
{
public:

	ThreadFunc(Add<Event> *callback) : m_callback(callback){/* EMPTY */}

	Add<Event> *GetCallBack()
	{
		return m_callback;
	}

	void operator()()
	{
		while(!m_callback->GetBool())
		{

		}

		boost::mutex::scoped_lock locker(lock);
		++g_counter;

	}

private:

	Add<Event> *m_callback;

};

template <class Event>
class Unsubscriber : public Callback<Event>
{
public:
	virtual void operator()(const Event &event)
	{
		(void)event;
		Callback<Event>::Unsubscribe();
	}

	virtual void DispatcherIsDead()
	{
		std::cout<< "Unsubscriber:dispatcher is dead" <<std::endl;
	}

	virtual ~Unsubscriber()
	{
		/* EMPTY */
	}

};

void Test1()
{
	Add<int> callback1;
	Add<int> callback2;
	Unsubscriber<int> callback3;


	Dispatcher<int> ds;

	Add<int> callback4;
	Unsubscriber<int> callback5;

	ds.Subscribe(&callback1);
	ds.Subscribe(&callback2);
	ds.Subscribe(&callback3);
	ds.Subscribe(&callback4);
	ds.Subscribe(&callback5);

	ds.SendEvent(5);
	ds.SendEvent(66);
	ds.SendEvent(666);

	Test(g_counter, 9, "counter test", __LINE__);
}

void Test2()
{
	Dispatcher<int> ds;

	Add<int> callback1;
	Add<int> callback2;

	ThreadFunc<int> tf1(&callback1);
	ThreadFunc<int> tf2(&callback2);


	boost::shared_ptr<boost::thread> thread_ptr1(new boost::thread(tf1));
	boost::shared_ptr<boost::thread> thread_ptr2(new boost::thread(tf2));

	ds.Subscribe(&callback1);
	ds.Subscribe(&callback2);

	ds.SendEvent(5);

	thread_ptr1->join();
	thread_ptr2->join();

	//std::cout<<g_counter<<std::endl;
	boost::mutex::scoped_lock locker(lock);
	Test(g_counter, 13, "counter test", __LINE__);


}


int main(void)
{
	Test1();
	Test2();

	TestReport("dispacher_test.cpp TEST");

	return 0;
}
/*****************************************************************************/
