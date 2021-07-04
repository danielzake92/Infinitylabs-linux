/*****************************************************************************
*	FILENAME:	thread_pool.cpp           AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			 
 *	REVIEWER:	Or Katz															 
 *																			 
 *	PURPOSE:    Thread Pool							     
 *																			 
 *****************************************************************************/

#include <sched.h> //sched_setparam
#include "thread_pool.hpp"
#include "logger.hpp" //logger singleton
#include "singleton.hpp" //singleton
/*****************************************************************************/
namespace ilrd_rd100
{//ilrd_rd100 - start

static Logger *s_logger = Singleton<Logger>::Handleton();

/*****************************************************************************/
/*                           Task Derivatives impl                           */
/*****************************************************************************/
ThreadPool::Task::~Task(){/*empty*/}
ThreadPool::BadApple::~BadApple(){/*empty*/}
void ThreadPool::BadApple::operator()(){/*empty*/}
/********************************* BadAppleJoin ***********************************/
ThreadPool::BadAppleJoin::BadAppleJoin(ThreadPool &pool)
                                            : m_pool(pool)
                                            {/* EMPTY */}

ThreadPool::BadAppleJoin::~BadAppleJoin(){/*empty*/}

void ThreadPool::BadAppleJoin::operator()()
{
    boost::mutex::scoped_lock Pool_Locker(m_pool.m_poolLock);
    throw(*this);
}
/****************************** BadAppleDetached ******************************/
ThreadPool::BadAppleDetached::BadAppleDetached(ThreadPool &pool)
                                                    : m_pool(pool)
                                                    {/* EMPTY */}

ThreadPool::BadAppleDetached::~BadAppleDetached(){/*empty*/}

void ThreadPool::BadAppleDetached::operator()()
{
    boost::thread::id thread_id = boost::this_thread::get_id();
    m_pool.FindAndDetach(thread_id);
    boost::mutex::scoped_lock Pool_Locker(m_pool.m_poolLock);
    throw(*this);
}
/*****************************************************************************/
/*                            PrioritizedTask impl                           */
/*****************************************************************************/
ThreadPool::PrioritizedTask::PrioritizedTask(boost::shared_ptr<Task> newTask,
                                                Priority priority)
                                            : m_pTask(newTask),
                                                m_priority(priority)
                                                {/* EMPTY */}

bool ThreadPool::PrioritizedTask::operator<(const ThreadPool::PrioritizedTask & other ) const
{
    return(m_priority < other.m_priority);
}

boost::shared_ptr<ThreadPool::Task> ThreadPool::PrioritizedTask::GetTask() const
{
    return m_pTask;
}
/*****************************************************************************/
/*                            ThreadPool API impl                            */
/*****************************************************************************/
ThreadPool::ThreadPool(size_t numThreads,int niceness)
: m_taskQueue(),
    m_threads(),
    m_threadLock(),
    m_poolLock(),
    m_cond(),
    m_running(false),
    m_alive(numThreads),
    m_niceness(niceness)

{
    CreateAndPushThreads(numThreads);
    s_logger->Log("ThreadPool(INFO) : ThreadPool::ThreadPool()\n",Logger::INFO);
}
/********************************************/
ThreadPool::~ThreadPool()
{
    Stop();

    for(size_t i = 0; i < m_alive; ++i)
    {
        Add(boost::shared_ptr<BadAppleJoin>(new BadAppleJoin(*this)), URGENT);
    }

    Run();
    
    std::vector< boost::shared_ptr<boost::thread> >::iterator begin = m_threads.begin();
    std::vector< boost::shared_ptr<boost::thread> >::iterator end = m_threads.end();

    {    
        boost::mutex::scoped_lock Pool_Locker(m_poolLock);
        while(m_alive != m_threads.size())
        {
            sleep(1);
        }
    }

    for(; begin != end; ++begin)
    {
        (*begin)->join();
    }
    s_logger->Log("ThreadPool(INFO) : ThreadPool::~ThreadPool()\n",Logger::INFO);
}
/********************************************/
void ThreadPool::Add(boost::shared_ptr<Task> newTask, Priority priority)
{
    ThreadPool::PrioritizedTask priority_task(newTask, priority);
    m_taskQueue.Push(priority_task);
}
/********************************************/
void ThreadPool::Run()
{
    boost::mutex::scoped_lock Pool_Locker(m_poolLock);
    m_running = true;
    m_cond.notify_all();
    s_logger->Log("ThreadPool(INFO) : ThreadPool::Run()\n",Logger::INFO);
}
/********************************************/
void ThreadPool::Pause()
{
    boost::mutex::scoped_lock Pool_Locker(m_poolLock);
    m_running = false;
    s_logger->Log("ThreadPool(INFO) : ThreadPool:Pause()\n",Logger::INFO);
}
/********************************************/
void ThreadPool::Stop()
{
    boost::mutex::scoped_lock Pool_Locker(m_poolLock);
    m_running = false;
    //emptying queue
    while(false == m_taskQueue.Empty())
    {
        m_taskQueue.Pop();
    }
    s_logger->Log("ThreadPool(INFO) : ThreadPool:Stop()\n",Logger::INFO);
}
/********************************************/
void ThreadPool::SetNumOfThreads(size_t num_threads)
{
    boost::mutex::scoped_lock Pool_Locker(m_poolLock); 
    if(num_threads == m_alive)
    {
        return;
    }

    ( num_threads < m_alive ) ?
                                DecThreadNum(num_threads):
                                IncThreadNum(num_threads);

    m_alive = num_threads;
    s_logger->Log("ThreadPool(INFO) : ThreadPool:SetNumOfThreads()\n",Logger::INFO);
}
/*****************************************************************************/
/*                        ThreadPool Private methods                         */
/*****************************************************************************/
void ThreadPool::IncThreadNum(size_t num_threads)
{
    CreateAndPushThreads(num_threads - m_alive);
    //new threads created wont be running by defaul
    //if flag is said to be running than we should
    //notify all new threads to be running.
    if(true == m_running)
    {
        m_cond.notify_all();
    }
}
/********************************************/
void ThreadPool::DecThreadNum(size_t num_threads)
{
    size_t bad_apple_num = m_alive - num_threads;
    for(size_t i = 0; i < bad_apple_num ; ++i)
    {
        Add(boost::shared_ptr<BadAppleDetached>(new BadAppleDetached(*this)), URGENT);
    }
}
/********************************************/
void ThreadPool::CreateAndPushThreads(size_t num_threads)
{
    struct sched_param param;
    param.sched_priority = m_niceness;
    int policy = SCHED_OTHER;

    for(size_t i = 0; i < num_threads; ++i)
    {
        ThreadPool::ThreadFunc thread_func(*this);
        boost::shared_ptr<boost::thread> thread_ptr(new boost::thread(thread_func));

        pthread_t thread_id = thread_ptr->native_handle();
        pthread_setschedparam(thread_id, policy, &param);

        m_threads.push_back(thread_ptr);

    }
}
/********************************************/
void ThreadPool::FindAndDetach(boost::thread::id thread_id)
{
    boost::mutex::scoped_lock Pool_Locker(m_poolLock);
    std::vector< boost::shared_ptr<boost::thread> >::iterator begin =
                                                            m_threads.begin();

    std::vector< boost::shared_ptr<boost::thread> >::iterator end =
                                                            m_threads.end();

    for(; begin != end; ++begin)
    {
        if((*begin)->get_id() == thread_id )
        {
            (*begin)->detach();
            m_threads.erase(begin);
            return;
        }
    }
}
/*****************************************************************************/
/*                             ThreadFunc impl                               */
/*****************************************************************************/
ThreadPool::ThreadFunc::ThreadFunc(ThreadPool &pool): m_pool(pool)
                                                    {/* EMPTY */}
/********************************************/
void ThreadPool::ThreadFunc::operator()()
{

    boost::shared_ptr<Task> my_task = boost::shared_ptr<Task>();
    ThreadPool::PrioritizedTask current_task(my_task);

    while(1)
    {
        //each thread grabs workers mutex with scope lock in his turn and
        //get blocked by cond wait until master broadcasting run
        {   
            boost::unique_lock<boost::mutex> thread_locker(m_pool.m_threadLock);
            m_pool.m_cond.wait(thread_locker);
        }

        
        while(1)
        {
            //each thread grabs pool mutex for cheking the flag 
            {
                boost::mutex::scoped_lock Pool_Locker(m_pool.m_poolLock);
                if(false == m_pool.m_running)
                {
                    break;
                }
            }

            m_pool.m_taskQueue.Dequeue(current_task);

            //if bad apple is thrown via BadAppleJoinDetach then
            //we catch and exiting thread, using detach mode,
            //and erasing it from threads vector
            try
            {
                (*current_task.GetTask())();
            }

            catch(const ThreadPool::BadApple &)
            {
                return;
            }
        }
    } 
}
}//ilrd_rd100 - end    


