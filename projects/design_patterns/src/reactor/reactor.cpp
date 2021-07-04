/*****************************************************************************
 *	FILENAME:	reactor.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for reactor lib.							     *
 *																			 *
 *****************************************************************************/

#include <sys/types.h> // portability with BSD 
#include <sys/time.h> //time_val struct
#include <sys/select.h> //select api
#include <cstring> //memcpy
#include "reactor.hpp"
#include "logger.hpp" //logger singleton
#include "singleton.hpp" //singleton
/*****************************************************************************/
namespace ilrd_rd100
{

static Logger *s_logger = Singleton<Logger>::Handleton();

/*****************************************************************************/
/*                                 FdWaiter                                  */
/*****************************************************************************/    
class FdWaiter: private boost::noncopyable
{//start of FdWaiter
public:
    virtual void Add(int fd, Reactor::Mode mode) =0;
    virtual void Remove(int fd, Reactor::Mode mode) =0;
    virtual std::pair<int, Reactor::Mode> Wait() =0;
    virtual ~FdWaiter() =0;
    std::pair<int, Reactor::Mode> static BadPair();
}; //end of FdWaiter

FdWaiter::~FdWaiter()
{
    /* EMPTY */
}
/*****************************************************************************/
std::pair<int, Reactor::Mode> FdWaiter::BadPair()
{
    return(std::pair<int, Reactor::Mode>(-1, Reactor::NUM_MODES));
}

/*****************************************************************************/
/*                             FdWaiterSelect                                */
/*****************************************************************************/    
class FdWaiterSelect: public FdWaiter 
{
public:
    FdWaiterSelect();
    virtual void Add(int fd, Reactor::Mode mode);
    virtual void Remove(int fd, Reactor::Mode mode);
    virtual std::pair<int, Reactor::Mode> Wait();
    virtual ~FdWaiterSelect();
private:
    int max_fd;
    fd_set m_arr[Reactor::NUM_MODES];
    void UpdateMax();
    bool IsInSets(int fd)const;
};

FdWaiterSelect::FdWaiterSelect(): max_fd(0), m_arr()
{
    for(size_t i = 0; i < Reactor::NUM_MODES; ++i)
    {
        FD_ZERO(&m_arr[i]);
    }
}
/*****************************************************************************/
void FdWaiterSelect::Add(int fd, Reactor::Mode mode)
{
    FD_SET(fd, &m_arr[mode]);
    max_fd = (max_fd > fd) ? max_fd : fd;
}
/*****************************************************************************/
void FdWaiterSelect::Remove(int fd, Reactor::Mode mode)
{
    FD_CLR(fd, &m_arr[mode]);
    UpdateMax();
}
/*****************************************************************************/
std::pair<int, Reactor::Mode> FdWaiterSelect::Wait()
{
    fd_set set_copy[Reactor::NUM_MODES];
    for(size_t i = 0; i < Reactor::NUM_MODES; ++i)
    {
        memcpy(&set_copy[i],&m_arr[i], sizeof(fd_set));
    }


    int fd_ready = select(max_fd + 1,
                          &set_copy[Reactor::READ],
                          &set_copy[Reactor::WRITE],
                          &set_copy[Reactor::EXCEPTION],
                          NULL);
    if( -1 == fd_ready)
    {
        return BadPair();
        /* log */
    }

    std::pair<int, Reactor::Mode> ret = BadPair();

    for(int i = 0; i <= max_fd ; ++i)
    {
        if(FD_ISSET(i, &m_arr[Reactor::READ]))
        {
            ret.first = i;
            ret.second = Reactor::READ;
            return ret;
        }
        if(FD_ISSET(i, &m_arr[Reactor::WRITE]))
        {
            ret.first = i;
            ret.second = Reactor::WRITE;
            return ret;
        }
        if(FD_ISSET(i, &m_arr[Reactor::EXCEPTION]))
        {
            ret.first = i;
            ret.second = Reactor::EXCEPTION;
            return ret;
        }
    }

    return ret;

}
/*****************************************************************************/
FdWaiterSelect::~FdWaiterSelect()
{
    /* EMPY */
}
/*****************************************************************************/
void FdWaiterSelect::UpdateMax() 
{
    for(int i = 0; i <= max_fd; ++i)
    {
        if(IsInSets(i) )
        {
            max_fd = i;
        }
    }
}
/*****************************************************************************/
bool FdWaiterSelect::IsInSets(int fd)const
{
    return(FD_ISSET(fd, &m_arr[Reactor::READ]) ||
           FD_ISSET(fd, &m_arr[Reactor::WRITE])||
           FD_ISSET(fd, &m_arr[Reactor::EXCEPTION]));
}
/*****************************************************************************/
/*                                 Reactor                                  */
/*****************************************************************************/
Reactor::Reactor(): m_map() ,m_fds(new FdWaiterSelect()), m_running(false)
{
    /* EMPTY */
}
/*****************************************************************************/
void Reactor::Add(boost::function<void(int)> f, int fd, Mode mode )
{
    m_fds->Add(fd, mode);
    m_map[std::pair<int, Mode>(fd, mode)] = f;
}
/*****************************************************************************/
void Reactor::Remove(int fd, Mode mode )
{
    m_fds->Remove(fd, mode);
    m_map.erase(std::pair<int, Mode>(fd, mode));
}
/*****************************************************************************/
void Reactor::Run()
{
    m_running = true;

    std::pair<int, Mode> ans_pair;

    while(m_running)
    {
        ans_pair = m_fds->Wait();
        if(ans_pair == FdWaiter::BadPair())
        {
            s_logger->Log("Reactor(ERROR) at" + LOG_LINE + ": wait failed -  with BadPair\n",Logger::ERROR);
            continue;
        }
        m_map.at(ans_pair)(ans_pair.first);
    }
}
/*****************************************************************************/
void Reactor::Stop()
{
    m_running = false;
}
/*****************************************************************************/
Reactor::~Reactor()
{
    delete m_fds;
}







}
/*****************************************************************************/
