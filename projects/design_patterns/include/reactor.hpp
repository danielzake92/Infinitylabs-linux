/*****************************************************************************
 *	FILENAME:	reactor.hpp              AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			
 *	VERSION:	2															 
 *																			 
 *	PURPOSE:   API for reactor lib.							             
 *																			
 *****************************************************************************/

#ifndef __ILRD_RD100_REACTOR_HPP__
#define __ILRD_RD100_REACTOR_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/unordered_map.hpp> // unordered_map
#include <boost/function.hpp> //boost functions 


namespace ilrd_rd100
{


class FdWaiter;
class Reactor: private boost::noncopyable
{//start of Reactor
public:
    enum Mode
    {
        READ = 0,
        WRITE = 1,
        EXCEPTION = 2,
        NUM_MODES = 3
    };
    explicit Reactor();
    ~Reactor();
    void Add(boost::function<void(int)>, int fd, Mode mode );
    void Remove(int fd, Mode mode);
    void Run();
    void Stop();
private:
    //forward declaration

    boost::unordered_map<std::pair<int, Mode>, boost::function<void(int)> > m_map;
    FdWaiter *m_fds;
    bool m_running;

}; //end of Reactor

}//ilrd_rd100 - end
#endif



   
    
    