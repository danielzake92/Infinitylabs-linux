/*****************************************************************************
 *	FILENAME:	framework_cmd.hpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	VERSION:	1															 *
 *																			 *
 *	PURPOSE:   API for framework_cmd lib.							             *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_FRAMEWORK_CMD_HPP__
#define __ILRD_RD100_FRAMEWORK_CMD_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/shared_ptr.hpp> //shared_ptr
#include "input_mediator_packet.hpp" //input_mediator_packet
#include "thread_pool.hpp" //for task
/*****************************************************************************/
namespace ilrd_rd100
{
    
class FrameworkCmd : private boost::noncopyable
{
public:
    virtual ~FrameworkCmd() =0;
    virtual boost::shared_ptr<FrameworkCmd> 
                             Create(boost::shared_ptr<InputMediatorPacket>) =0;
    virtual boost::shared_ptr<ThreadPool::Task> operator()() =0;
private:
    boost::shared_ptr<InputMediatorPacket> m_packet;
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_FRAMEWORK_CMD_HPP__

