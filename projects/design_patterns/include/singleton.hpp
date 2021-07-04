/*****************************************************************************
 *	FILENAME:	singleton.hpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	VERSION:	2															 *
 *																			 *
 *	PURPOSE:   API for singleton lib.							             *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_SINGLETON_HPP__
#define __ILRD_RD100_SINGLETON_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/thread/mutex.hpp> //boost:mutex 
#include <boost/atomic.hpp>
/*****************************************************************************/
namespace ilrd_rd100
{

template <class T>
class Singleton: private boost::noncopyable
{
public:
    static T *Get();
    static T *Handleton();

private:
    Singleton(); //restrict publicity ctor
    ~Singleton(); //restrict publicity dtor
    static boost::mutex s_lock;
    static T *s_instance;
    static T *const s_invlaidPtr;
};

template <class T>
boost::mutex Singleton<T>::s_lock;

template <class T>
T *Singleton<T>::s_instance = 0;

template <class T>
T *const Singleton<T>::s_invlaidPtr = reinterpret_cast<T*>(0x1);

template <class T>
T *Singleton<T>::Get()
{
    if(s_invlaidPtr == s_instance)
    {
        abort();
    }

    T *temp = s_instance;
    atomic_thread_fence(boost::memory_order_release);
    if(0 == temp)
    {
        boost::mutex::scoped_lock locker(s_lock);
        temp  = s_instance;
        if(0 == temp)
        {
            temp = new T;
            atomic_thread_fence(boost::memory_order_acquire);
            s_instance = temp;
            static Singleton<T> single;
        }
    }

    return s_instance;
}

template <class T>
Singleton<T>::~Singleton()
{
    if(s_invlaidPtr == s_instance)
    {
        return;
    }
    delete s_instance;
    s_instance = s_invlaidPtr;
}

template <class T>
Singleton<T>::Singleton(){/* EMPTY */}




} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_SINGLETON_HPP__

