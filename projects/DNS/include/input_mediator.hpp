/*****************************************************************************
 *	FILENAME:	input_mediator.hpp        AUTHOR: Or Katz  LAB: RD100	 
 *																			 
 *	VERSION:	2															 
 *																			 
 *	PURPOSE:   API for input_mediator lib.							             
 *																			 
 *****************************************************************************/

#ifndef __ILRD_RD100_INPUT_MEDIATOR_HPP__
#define __ILRD_RD100_INPUT_MEDIATOR_HPP__

#include "reactor.hpp" //reactor
#include "input_proxy.hpp" //input proxy

/*****************************************************************************/
namespace ilrd_rd100
{

class InputMediator : private boost::noncopyable
{
public:
    explicit InputMediator(InputProxy *inputProxy, int fd);
    ~InputMediator();
    void Run();

private:
    InputProxy *m_inputProxy;
    Reactor m_reactor;

    void ReadOp(int fd);
    void WriteOp(int fd);
    void ExceptionOp(int fd);
    void DeliverTask(const InputMediatorPacket& packet);
    void Stop();
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_INPUT_MEDIATOR_HPP__
