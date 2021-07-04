/*****************************************************************************
 *	FILENAME:	locks.hpp              AUTHOR: Daniel Zaken  LAB: RD100	 
 *																		
 *	VERSION:	1														
 *																		
 *	PURPOSE:   API for lock lib.							    
 *																		
 *****************************************************************************/

#ifndef __ILRD_RD100_LOCK_HPP__
#define __ILRD_RD100_LOCK_HPP__

#include <boost/core/noncopyable.hpp> // boost::noncopyable
#include <cstddef> // size_t
#include <pthread.h> //mutex
#include <semaphore.h> //semaphore
#include <boost/shared_ptr.hpp> //shared_ptr

/*****************************************************************************/
namespace ilrd_rd100
{

    class Mutex : private boost::noncopyable
    {
    public:
        explicit Mutex();
       
        void Lock();

        void Unlock();

        boost::shared_ptr<pthread_mutex_t> Get() ;

        ~Mutex();

    private:
        pthread_mutex_t m_lock;

    };
/*****************************************************************************/
    class Semaphore : private boost::noncopyable
    {
    public:
        explicit Semaphore(unsigned int sem_size = 0); 

        void Wait();

        void TryWait();

        void Post();

        ~Semaphore();
    private:
        sem_t m_sem;
    };
/*****************************************************************************/
    class Condition : private boost::noncopyable
    {
    public:
        explicit Condition(Mutex &mutex); 
        //pthread_cond_init(&con, NULL)
        void Broadcast();

        void Wait();

        ~Condition();
        //pthread_cond_destroy
    private:
        pthread_cond_t m_cond;
        Mutex &m_mutex;
    };


} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_THREAD_SAFE_QUE_HPP__

