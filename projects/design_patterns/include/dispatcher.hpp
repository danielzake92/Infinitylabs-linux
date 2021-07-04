/****************************************************************************
* FILE: dispatcher.hpp		     Purpose: API for Dispatcher.
*
* DEVELOPER: Itamar Aron
*
* REVIEWER: 			        STATUS: 
*
* VERSION: 1
*
****************************************************************************/
#ifndef __ILRD_RD100_DISPATCHER_HPP__
#define __ILRD_RD100_DISPATCHER_HPP__


#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/unordered_map.hpp> // unordered_map
#include <boost/container/list.hpp>
#include <boost/thread/recursive_mutex.hpp> //boost:mutex 

namespace ilrd_rd100
{

//forward declaration
template <class Event>
class Dispatcher;

/*****************************************************************************/
/*                            Callback - API                                 */
/*****************************************************************************/
template <class Event>
class Callback: private boost::noncopyable
{
public:
    explicit Callback();
    virtual ~Callback() = 0;
protected:
    void Unsubscribe(); 
private:
    virtual void operator()(const Event &event) = 0;
    virtual void DispatcherIsDead() = 0;
    void SetDispatcher(Dispatcher<Event> *dispatcher);
    friend class Dispatcher<Event>;    

    Dispatcher<Event> *m_dispatcher;
};//Callback - end
/*****************************************************************************/
/*                            Dispatcher - API                               */
/*****************************************************************************/
template <class Event>
class Dispatcher: boost::noncopyable
{
public:
    ~Dispatcher();
    void Subscribe(Callback<Event> *callback);
    void SendEvent(const Event &event);

private:

    typedef boost::container::list<Callback<Event>*> list_t;
    list_t m_callBacks;
    boost::unordered_map<Callback<Event>*, typename list_t::iterator> m_iters;
    boost::recursive_mutex m_lock;

    void Unsubscribe(Callback<Event> *callback);
    friend class Callback<Event>;
};//Dispatcher - end

/*****************************************************************************/
/*                            Callback - IMPL                                */
/*****************************************************************************/
//Ctor
template <class Event>
Callback<Event>::Callback() : m_dispatcher(NULL) {/* EMPTY */}
/*****************************************************************************/
//Dtor
template <class Event>
Callback<Event>::~Callback()
{
    if(m_dispatcher)
    {
        m_dispatcher->Unsubscribe(this);
    }
}
/*****************************************************************************/
//SetDispatcher
template <class Event>
void Callback<Event>::SetDispatcher(Dispatcher<Event> *dispatcher)
{
    m_dispatcher = dispatcher;
}
/*****************************************************************************/
//Unsubscribe
template <class Event>
void Callback<Event>::Unsubscribe()
{
    m_dispatcher->Unsubscribe(this);
}
/*****************************************************************************/
/*                            Dispatcher - IMPL                              */
/*****************************************************************************/
//Subscribe
template <class Event>
void Dispatcher<Event>::Subscribe(Callback<Event> *callback)
{
    boost::recursive_mutex::scoped_lock locker(m_lock);

    if( NULL != callback->m_dispatcher )
    {
        callback->m_dispatcher->Unsubscribe(callback);
    }
    m_callBacks.push_back(callback);
    m_iters[callback] = --m_callBacks.end();
    callback->SetDispatcher(this);
}
/*****************************************************************************/
//UnSubscribe
template <class Event>
void Dispatcher<Event>::Unsubscribe(Callback<Event> *callback)
{
    boost::recursive_mutex::scoped_lock locker(m_lock);

    typename list_t::iterator iter = m_iters.at(callback);
    
    m_iters.erase(callback);
    m_callBacks.erase(iter);
    callback->SetDispatcher(NULL);
    
}
/*****************************************************************************/
//SendEvent
template <class Event>
void Dispatcher<Event>::SendEvent(const Event &event)
{
    boost::recursive_mutex::scoped_lock locker(m_lock);

    list_t copy_callbacks(m_callBacks);
    typename list_t::iterator begin = copy_callbacks.begin();
    typename list_t::iterator end = copy_callbacks.end();

    for(; begin != end; ++begin)
    {
        (*begin)->operator()(event);
    }

}
/*****************************************************************************/
template <class Event>
Dispatcher<Event>::~Dispatcher()
{
    boost::recursive_mutex::scoped_lock locker(m_lock);
    typename list_t::iterator begin = m_callBacks.begin();
    typename list_t::iterator end = m_callBacks.end();

    for(; begin != end; ++begin)
    {
        (*begin)->DispatcherIsDead();
        (*begin)->SetDispatcher(NULL);
    }

}

}//ilrd_rd100 - end






#endif