/*****************************************************************************
 *	FILENAME:	dir_monitor.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for dir_monitor lib.							     *
 *																			 *
 *****************************************************************************/

#include <sys/inotify.h> //inotify
#include <sys/time.h> //time_val struct
#include <sys/select.h> //select api
#include <cstring> //memset
#include <dlfcn.h> //dlopen
#include "dir_monitor.hpp"
#include "logger.hpp" //logger
#include "singleton.hpp" //singleton
/*****************************************************************************/
namespace ilrd_rd100
{

const time_t INTERVAL_U_SECONDS = 500000;
const size_t ONE_MIL = 1000000;
const size_t MAX_NAME_LENGTH = 128;
const size_t EVENT_SIZE = sizeof(struct inotify_event);
const size_t NUM_OF_EVENTS = 1024;
const size_t EVENT_BUFF_LEN = (EVENT_SIZE + MAX_NAME_LENGTH) * NUM_OF_EVENTS;
static Logger *s_logger = Singleton<Logger>::Handleton();
/**********************************************/
/*                  ThreadFunc                */
/**********************************************/
/*****************************************************************************/
DirMonitor::ThreadFunc::ThreadFunc(DirMonitor &monitor): m_monitor(monitor)
{
    /* EMPTY */
}
/*****************************************************************************/
void DirMonitor::ThreadFunc::operator()()
{
    fd_set fdset;
    timeval tv;
    char buffer[EVENT_BUFF_LEN] = {0};
    int n_ready = 0;

    while(1) 
    {
        {
            boost::mutex::scoped_lock locker(m_monitor.m_lock);
            if(!m_monitor.m_flag)
            {
                return;
            }
        }

        FdSet(&fdset, &tv, m_monitor.m_fd , INTERVAL_U_SECONDS);
        n_ready = select(m_monitor.m_fd + 1, &fdset, NULL, NULL, &tv);
        if(-1 == n_ready)
        {
            s_logger->Log("DirMonitor(ERROR) at" + LOG_LINE + ": select failed\n",Logger::ERROR);
            return;
        }

        if (FD_ISSET(m_monitor.m_fd, &fdset))
        {
            ssize_t len = read(m_monitor.m_fd,buffer,EVENT_BUFF_LEN );
            if(-1 == len)
            {
                s_logger->Log("DirMonitor(ERROR) at" + LOG_LINE + ": read buffer failed\n",Logger::ERROR);
                return;
            }

            EventParser(len, buffer);
        }
    }


}
/*****************************************************************************/
void DirMonitor::ThreadFunc::EventParser(size_t read_len, char *buffer)
{
    size_t jump = 0;
    inotify_event *i_event = NULL;

    while(jump < read_len)
    {
        i_event = reinterpret_cast<inotify_event*>(buffer + jump);
        jump += (EVENT_SIZE + i_event->len);
        
        if(!i_event->mask)
        {
            break;
        }

        Notification notification(i_event->mask,
                                  m_monitor.m_directory + '/' + i_event->name);
        m_monitor.m_dispatcher.SendEvent(notification);
    }
    memset(buffer, 0,EVENT_BUFF_LEN );
}
/*****************************************************************************/
void DirMonitor::ThreadFunc::FdSet(fd_set *fdset,
                                   struct timeval *tv ,
                                   int fd,
                                   time_t m_sec_interval)
{
    FD_ZERO(fdset);
    FD_SET(fd,fdset);

    tv->tv_sec = m_sec_interval / ONE_MIL;
    tv->tv_usec = m_sec_interval % ONE_MIL;
}
/**********************************************/
/*                 Notification               */
/**********************************************/
Notification::Notification(uint32_t mask, std::string str): 
                                                    events(mask),
                                                    file_name(str)
{
    /* EMPTY */
}
/**********************************************/
/*                  DirMonitor                */
/**********************************************/
/*****************************************************************************/
DirMonitor::DirMonitor(const std::string &directory): 
                                        m_dispatcher(),
                                        m_fd(inotify_init()),
                                        m_lock(),
                                        m_thread(),
                                        m_directory(directory),
                                        m_wd(),
                                        m_flag(true)
{
    m_wd = inotify_add_watch(m_fd, directory.c_str(),IN_ALL_EVENTS ); 
    if(-1 == m_wd)
    {
        s_logger->Log("DirMonitor(ERROR) at" + LOG_LINE + ": inotify_add_watch failed\n",Logger::ERROR);
        return;
    }

    ThreadFunc thread_func(*this);
    m_thread = boost::shared_ptr<boost::thread>(new boost::thread(thread_func));
    s_logger->Log("DirMonitor(INFO) : DirMonitor::DirMonitor()\n",Logger::INFO);
}
/*****************************************************************************/
DirMonitor::~DirMonitor()
{
    Stop();
    close(m_fd);
    close(m_wd);
    s_logger->Log("DirMonitor(INFO) : DirMonitor::~DirMonitor()\n",Logger::INFO);
}
/*****************************************************************************/
void DirMonitor::Stop()
{
    if(m_flag)
    {
        {    
            boost::mutex::scoped_lock locker(m_lock);
            m_flag = false;
        }
        m_thread->join();
    }
    s_logger->Log("DirMonitor(INFO) : DirMonitor::Stop()\n",Logger::INFO);
}
/*****************************************************************************/
void DirMonitor::Subscribe(Callback<Notification> *callback)
{
    boost::mutex::scoped_lock locker(m_lock);
    m_dispatcher.Subscribe(callback);
    s_logger->Log("DirMonitor(INFO) : DirMonitor::Subscribe()\n",Logger::INFO);
}
/**********************************************/
/*               LoaderCallback               */
/**********************************************/
DsoLoader::LoaderCallback::~LoaderCallback()
{
    boost::mutex::scoped_lock locker(m_lock);
    while(!m_plugins.empty())
    {
        dlclose(m_plugins.top());
        m_plugins.pop();
    }
}
/*****************************************************************************/
void DsoLoader::LoaderCallback::operator()(const Notification &event)
{
    void *handle = dlopen(event.file_name.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if( NULL != handle )
    {
        m_plugins.push(handle);
    }
}
/*****************************************************************************/
void DsoLoader::LoaderCallback::DispatcherIsDead()
{
    /* EMPTY */
}
/**********************************************/
/*                  DsoLoader                 */
/**********************************************/
DsoLoader::DsoLoader(DirMonitor *dirmonitor)
{
    dirmonitor->Subscribe(&m_callback);
}


}
/*****************************************************************************/
