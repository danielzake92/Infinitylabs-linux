/****************************************************************************
* FILE: dir_monitor.hpp	            Purpose: API Dir_monitor
* DEVELOPER: Elizabeta Vitovsky
*
* REVIEWER:  			                STATUS: IMPL
*
* VERSION: 2
*
****************************************************************************/
#ifndef __ILRD_RD100_DIR_MONITOR_HPP__
#define __ILRD_RD100_DIR_MONITOR_HPP__

#include <iostream> 
#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/thread/mutex.hpp> //boost:mutex 
#include <boost/thread.hpp> //thread class
#include <boost/shared_ptr.hpp> //shared_ptr
#include <stack>
#include "dispatcher.hpp"


namespace ilrd_rd100
{//ilrd_rd100 start

/**********************************************/
/*              struct Notification           */
/**********************************************/
struct Notification
{
    explicit Notification(uint32_t mask, std::string str);

    uint32_t events;
    std::string file_name;
};
/**********************************************/
/*                  DirMonitor                */
/**********************************************/
class DirMonitor: private boost::noncopyable
{
public:
    explicit DirMonitor(const std::string &directory);
    ~DirMonitor();
    void Stop();
    void Subscribe(Callback<Notification> *callback);
private:
/***************PrivateMembers*******************/
    Dispatcher<Notification> m_dispatcher;
    int m_fd;
    boost::mutex m_lock;
    boost::shared_ptr<boost::thread> m_thread;
    std::string m_directory;
    int m_wd;
    bool m_flag;

/*****************ThreadFunc********************/
    class ThreadFunc
    {
    public:
        explicit ThreadFunc(DirMonitor &monitor);

        void operator()();

    private:
        DirMonitor &m_monitor;
        static void FdSet(fd_set *fdset,struct timeval *tv ,int fd, time_t interval);
        void EventParser(size_t read_len, char *buffer);
    };

}; //end DirMonitor
/**********************************************/
/*                  DsoLoader                 */
/**********************************************/
class DsoLoader: private boost::noncopyable
{
public:
    explicit DsoLoader(DirMonitor *dirmonitor); 
      
    class LoaderCallback: public Callback<Notification>
    {
    public:
        virtual ~LoaderCallback();
        virtual void operator()(const Notification &event);
        virtual void DispatcherIsDead();   
    private:
        std::stack<void*> m_plugins;
        boost::mutex m_lock;
    };//end LoaderCallback
private:
    LoaderCallback m_callback;
}; //end DsoLoader

}
#endif