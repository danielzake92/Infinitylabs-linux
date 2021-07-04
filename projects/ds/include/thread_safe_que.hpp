/*****************************************************************************
 *	FILENAME:	thread_safe_que.hpp        AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			 
 *	VERSION:	1															 
 *																			 
 *	PURPOSE:   API for thread_safe_que lib.							         
 *																			 
 *****************************************************************************/

#ifndef __ILRD_RD100_THREAD_SAFE_QUE_HPP__
#define __ILRD_RD100_THREAD_SAFE_QUE_HPP__

#include <cstddef> // size_t
#include <queue> //std::queue
#include <boost/core/noncopyable.hpp> //boost::noncopyable
#include <boost/thread/mutex.hpp> //boost:mutex boost::condition_variable 
#include <boost/interprocess/sync/scoped_lock.hpp> //bost::scoped_lock
// boost::interprocess::interprocess_semaphore
#include <boost/interprocess/sync/interprocess_semaphore.hpp> 

/*
    BEWARE :
            Each method in Thread safe queue is Thread safe
            when called seperatly but may not be safe in 
            when combined
*/

/*****************************************************************************/
namespace ilrd_rd100
{//ilrd_rd100 - start
/*****************************************************************************/
//PriorityQueue - start
template < class T>
class PriorityQueue
{
public:
    void pop();
    void push(T data);

    T front() const;

    size_t size() const;
    bool empty() const;

private:
    std::priority_queue<T> m_que;
};
//PriorityQueue - end
/*****************************************************************************/
//TSQueue - start
template < class T, class Q = std::queue<T> >
class TSQueue : private boost::noncopyable
{
public:
    explicit TSQueue();
    void Pop();
    void Push(T data);

    void Dequeue(T &target);

    T Front() const;
    T Back() const;
    //T Top() const;

    size_t Size() const;
    bool Empty() const;

private:
    Q m_que;
    mutable boost::mutex m_lock;
    boost::interprocess::interprocess_semaphore m_count;

};
//TSQueue - end
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template < class T>
void PriorityQueue<T>::pop()
{
    m_que.pop();
}
/*****************************************************************************/
template < class T>
void PriorityQueue<T>::push(T data)
{
    m_que.push(data);
}
/*****************************************************************************/
template < class T>
T PriorityQueue<T>::front() const
{
    return m_que.top();
}
/*****************************************************************************/
template < class T>
size_t PriorityQueue<T>::size() const
{
    return m_que.size();
}
/*****************************************************************************/
template < class T>
bool PriorityQueue<T>::empty() const
{
    return m_que.empty();
}
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template <class T, class Q>
TSQueue<T, Q>::TSQueue() : m_que(), m_lock(), m_count(0)
{
    /* empty */
}
/*****************************************************************************/
template <class T, class Q>
void TSQueue<T,Q>::Pop()
{
    m_count.wait();

    boost::mutex::scoped_lock mut_lock(m_lock);

    m_que.pop();
}
/*****************************************************************************/
template <class T, class Q>
void TSQueue<T, Q>::Push(T data)
{
    boost::mutex::scoped_lock mut_lock(m_lock);

    m_que.push(data);

    m_count.post();
}
/*****************************************************************************/
template <class T, class Q>
T TSQueue<T, Q>::Front() const
{
    boost::mutex::scoped_lock mut_lock(m_lock);

    return m_que.front();
}
/*****************************************************************************/
template <class T, class Q>
T TSQueue<T, Q>::Back() const
{
    boost::mutex::scoped_lock mut_lock(m_lock);
    return m_que.back();
}
/*****************************************************************************/
template <class T, class Q>
size_t TSQueue<T, Q>::Size() const
{
    boost::mutex::scoped_lock mut_lock(m_lock);
    return m_que.size();
}
/*****************************************************************************/
template <class T, class Q>
bool TSQueue<T, Q>::Empty() const
{
    boost::mutex::scoped_lock mut_lock(m_lock);
    return m_que.empty();
}
/*****************************************************************************/
template <class T, class Q>
void TSQueue<T, Q>::Dequeue(T &target)
{
    m_count.wait();
    boost::mutex::scoped_lock mut_lock(m_lock);
    target = m_que.front();
    m_que.pop();
}

/*****************************************************************************/
} //ilrd_rd100 - end
/*****************************************************************************/
#endif // __ILRD_RD100_THREAD_SAFE_QUE_HPP__

