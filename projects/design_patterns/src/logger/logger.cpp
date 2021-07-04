/*****************************************************************************
 *	FILENAME:	logger.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for logger lib.							     *
 *																			 *
 *****************************************************************************/

#include "logger.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{
/*****************************************************************************/
/*                                Logger                                     */
/*****************************************************************************/
Logger::Logger(const std::string &logFilePath, Priority threshold):
m_logFilePath(logFilePath),
m_threshold(threshold),
m_msgQueue(),
m_logging(true),
m_thread(Logger::ThreadFunc(this))
{
    /*  EMPTY */
}
/*****************************************************************************/
Logger::~Logger()
{
    m_logging = false;
    Log("EOF\n", CRITICAL);
    m_thread.join();
}
/*****************************************************************************/
void Logger::Log(const std::string &msg, Priority priority)
{
    if(priority >= m_threshold)
    {
        m_msgQueue.Push(msg);
    }
}
/*****************************************************************************/
/*                              ThreadFunc                                   */
/*****************************************************************************/
Logger::ThreadFunc::ThreadFunc(Logger *logger): 
m_logger(logger)
{
    /* EMPTY */
}
/*****************************************************************************/
void Logger::ThreadFunc::operator()()
{
    std::string buffer;
    std::ofstream myfile;

    while(m_logger->m_logging || false == m_logger->m_msgQueue.Empty())
    {
        m_logger->m_msgQueue.Dequeue(buffer);

        myfile.open (m_logger->m_logFilePath.c_str(),
                     std::ofstream::out | std::ofstream::app);
        myfile<<buffer;
        myfile.close();
    }
    
}

}// end ilrd_rd100
/*****************************************************************************/
