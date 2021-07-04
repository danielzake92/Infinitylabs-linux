/****************************************************************************
* FILE: rc_string_test.cpp		    PURPOSE: Implementation for RCString Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: ******* 				STATUS: Approved
*
****************************************************************************/

#include <pthread.h>
#include <semaphore.h>
#include "scope_lock.hpp"

using namespace ilrd_rd100;

class Mutex : private boost::noncopyable
{
public:
    explicit Mutex() 
    {
        m_lock = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_init(&m_lock, NULL);
    }

    void Lock()
    {
        pthread_mutex_lock(&m_lock);
    }

    void Unlock()
    {
        pthread_mutex_unlock(&m_lock);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&m_lock);
    }
private:
    pthread_mutex_t m_lock;

};
/*****************************************************************************/

class Semaphore : private boost::noncopyable
{
public:
    explicit Semaphore() 
    {
        m_lock = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_init(&m_lock, NULL);
    }

    void Lock()
    {
        pthread_mutex_lock(&m_lock);
    }

    void Unlock()
    {
        pthread_mutex_unlock(&m_lock);
    }

    ~Semaphore()
    {
        pthread_mutex_destroy(&m_lock);
    }
private:
    sem_t m_lock;

};




int main()
{
    Mutex mut1;
    Mutex mut2;

    ScopeLock <Mutex> s1(mut1);

    ScopeLock <Mutex> s2(mut2);


    return 0;
}

