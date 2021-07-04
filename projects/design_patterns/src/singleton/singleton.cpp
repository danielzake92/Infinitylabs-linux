/*****************************************************************************
 *	FILENAME:	singleton.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for singleton lib.							     *
 *																			 *
 *****************************************************************************/

#include "singleton.hpp"
#include "logger.hpp" //specialization for logger
/*****************************************************************************/
namespace ilrd_rd100
{   
const char *LOG_PATH = "./test/log";
/*****************************************************************************/
/*                                Logger                                     */
/*****************************************************************************/
template <>
Logger *Singleton<Logger>::Get()
{
    if(s_invlaidPtr == s_instance)
    {
        abort();
    }

    Logger *temp = s_instance;
    atomic_thread_fence(boost::memory_order_release);
    if(0 == temp)
    {
        boost::mutex::scoped_lock locker(s_lock);
        temp  = s_instance;
        if(0 == temp)
        {
            temp = new Logger(LOG_PATH,Logger::INFO);
            atomic_thread_fence(boost::memory_order_acquire);
            s_instance = temp;
            static Singleton<Logger> single;
        }
    }

    return s_instance;
}
/*****************************************************************************/    
template <>
Logger *Singleton<Logger>::Handleton()
{
    return Singleton<Logger>::Get();
}

}
/*****************************************************************************/
