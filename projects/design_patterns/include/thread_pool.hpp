/*****************************************************************************
*	FILENAME:	thread_pool.hpp           AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			 
 *	REVIEWER:	Or Katz															 
 *																			 
 *	PURPOSE:    Thread Pool							     
 *																			 
 *****************************************************************************/
#ifndef __ILRD_RD100_THREADPOOL_HPP__
#define __ILRD_RD100_THREADPOOL_HPP__

#include <boost/core/noncopyable.hpp> //boost::noncopyable
#include <boost/thread.hpp> //thread class
#include <boost/shared_ptr.hpp> //shared_ptr
#include <boost/thread/mutex.hpp> //boost:mutex boost::condition_variable 
#include <boost/interprocess/sync/scoped_lock.hpp> //bost::scoped_lock

#include "thread_safe_que.hpp" //thread safe queue

namespace ilrd_rd100
{//ilrd_rd100 - start

class ThreadPool: private boost::noncopyable
{
   
public:
/*****************************************************************************/
/*                            Priority enum                                  */
/*****************************************************************************/
    enum Priority
    {
        LOW = 0,
        MEDIUM = 1,
        HIGH = 2,
        URGENT = 3
    };
/*****************************************************************************/
/*                            Task Interface                                 */
/*****************************************************************************/   
    class Task
    {
    public:
        virtual ~Task() = 0; 
        virtual void operator()() = 0;
    };//Task - end
/*****************************************************************************/
/*                         ThreadPool Api Methods                            */
/*****************************************************************************/
    explicit ThreadPool(size_t numThreads = boost::thread::hardware_concurrency(),
                        int niceness = 0);
    ~ThreadPool();

    void Add(boost::shared_ptr<Task> newTask, Priority priority);
    
    void Run();
    /* Pause threads in pool from acquiring new tasks */
    void Pause();
    /* Stop threads in pool for acquiring new tasks and empty queue of tasks */
    void Stop(); 

    void SetNumOfThreads(size_t num_threads);
/*****************************************************************************/
/*                       ThreadPool Private Members                          */
/*****************************************************************************/
private:
    class PrioritizedTask; //forward declaration

    void IncThreadNum(size_t num_threads);
    void DecThreadNum(size_t num_threads);
    void CreateAndPushThreads(size_t num_threads);
    void FindAndDetach(boost::thread::id thread_id);

    TSQueue<PrioritizedTask, PriorityQueue<PrioritizedTask> > m_taskQueue;
    std::vector< boost::shared_ptr<boost::thread> > m_threads;
    boost::mutex m_threadLock;
    boost::mutex m_poolLock;
    boost::condition_variable m_cond;
    boost::atomic<bool> m_running;
    size_t m_alive;
    int m_niceness;
/*****************************************************************************/
/*                        ThreadFunc class for impl                          */
/*****************************************************************************/
    class ThreadFunc
    {
    public:
        explicit ThreadFunc(ThreadPool &pool);
       

        void operator()();

    private:
        ThreadPool &m_pool;
    };
/*****************************************************************************/
/*                      BadApple Task class for impl                         */
/*****************************************************************************/
    class BadApple : public ThreadPool::Task
    {
    public:
        virtual ~BadApple();
        virtual void operator()();
    };     
/*****************************************************************************/
/*                      BadAppleJoin Task class for impl                     */
/*****************************************************************************/
    class BadAppleJoin : public ThreadPool::BadApple
    {
    public:
        explicit BadAppleJoin(ThreadPool &pool);
        virtual ~BadAppleJoin();
        virtual void operator()();
    private:
        ThreadPool &m_pool;
    }; 
/*****************************************************************************/
/*                   BadAppleDetached Task class for impl                    */
/*****************************************************************************/
    class BadAppleDetached : public ThreadPool::BadApple
    {
    public:
        explicit BadAppleDetached(ThreadPool &pool);

        virtual ~BadAppleDetached();
        virtual void operator()();
    private:
        ThreadPool &m_pool;
    }; 
/*****************************************************************************/
/*                   PrioritizedTask Task class for impl                     */
/*****************************************************************************/
    class PrioritizedTask
    {
    public:
        explicit PrioritizedTask(boost::shared_ptr<Task> newTask,
                                 Priority priority = LOW);

        boost::shared_ptr<Task> GetTask() const;

        bool operator<(const PrioritizedTask &other) const;

    private:
        boost::shared_ptr<Task> m_pTask;
        Priority m_priority;
    };

};//ThreadPool - end


}//ilrd_rd100 - end

#endif