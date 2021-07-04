/*****************************************************************************
 *	FILENAME:	logger.hpp              AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			 
 *	VERSION:	1															 
 *																			 
 *	PURPOSE:   API for logger lib.							            
 *																			 
 *****************************************************************************/

#ifndef __ILRD_RD100_LOGGER_HPP__
#define __ILRD_RD100_LOGGER_HPP__

#include <iostream> // i/o streams
#include <cstddef> // size_t

#include <boost/thread.hpp> //thread class
#include <boost/core/noncopyable.hpp> // noncopyable
#include <queue> //std::queue
#include <fstream> //std::ofstream
#include "thread_safe_que.hpp" //thread safe queue

#define LOG_LINE (static_cast<std::ostringstream*>( &(std::ostringstream() << __LINE__) )->str() )

/*****************************************************************************/
namespace ilrd_rd100
{
/*****************************************************************************/
/*                                Logger                                     */
/*****************************************************************************/
class Logger : private boost::noncopyable
{
public:
/*****************************************************************************/
/*                              Priority                                     */
/*****************************************************************************/
    enum Priority
    {
        INFO = 0,
        DEBUG = 1,
        ERROR = 2,
        CRITICAL = 3
    };
    explicit Logger(const std::string &logFilePath, Priority threshold);
    ~Logger();
    void Log(const std::string &msg, Priority priority);

private:
/*****************************************************************************/
/*                               ThreadFunc                                  */
/*****************************************************************************/
    class ThreadFunc
    {
    public:
        explicit ThreadFunc(Logger *logger);
        void operator()();
    private:
        Logger *m_logger;
    };
    
    std::string m_logFilePath;
    Priority m_threshold;
    TSQueue<std::string, std::queue<std::string> > m_msgQueue;
    bool m_logging;
    boost::thread m_thread;

};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_LOGGER_HPP__

