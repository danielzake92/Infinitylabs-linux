/****************************************************************************
* FILE: scope_lock.hpp		            Purpose: Implementation for Lock Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Elizabeta Vitovsky		STATUS: Approved
*
*
****************************************************************************/

#ifndef __ILRD_RD100_Lock_HPP__
#define __ILRD_RD100_Lock_HPP__

#include <boost/core/noncopyable.hpp>

namespace ilrd_rd100
{
/*****************************************************************************/
template<class T>
class ScopeLock : private boost::noncopyable
{
public :
    explicit ScopeLock(T &lock);
    ~ScopeLock();
private:
    T &m_lock;
};
/*****************************************************************************/
/*****************************************************************************/
template<class T>
ScopeLock<T>::ScopeLock(T &lock) : m_lock(lock)
{
    m_lock.Lock();
}

template<class T>
ScopeLock<T>::~ScopeLock()
{
    m_lock.Unlock();
}



}
#endif//__ILRD_RD100_Lock_HPP__ - end
