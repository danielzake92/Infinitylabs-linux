/*****************************************************************************
 *	FILENAME:	input_mediator.cpp       AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			 
 *	REVIEWER:																 
 *																			 
 *	PURPOSE:    Implementing for input_mediator lib.							    
 *																			 
 *****************************************************************************/
#include <boost/bind.hpp> //boost::bind
#include <iostream> //std::cout
#include "input_mediator.hpp"
#include "singleton.hpp"
#include "thread_pool.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{
/*****************************************************************************/
/*                            InputMediator-IMPL                             */
/*****************************************************************************/
InputMediator::InputMediator(InputProxy *inputProxy, int fd):
m_inputProxy(inputProxy),
m_reactor()
{
    boost::function<void(int)> func = boost::bind(&InputMediator::ReadOp,
                                                  this,
                                                  _1);
    m_reactor.Add(func, fd, Reactor::READ);

    func = boost::bind(&InputMediator::WriteOp,this, _1);
    m_reactor.Add(func, fd, Reactor::WRITE);

    func = boost::bind(&InputMediator::ExceptionOp,this, _1);
    m_reactor.Add(func, fd, Reactor::EXCEPTION);

}
/*****************************************************************************/
InputMediator::~InputMediator()
{
    m_inputProxy = NULL;
}
/*****************************************************************************/
void InputMediator::Run()
{
    m_reactor.Run();
}
/*****************************************************************************/
void InputMediator::Stop()
{
    m_reactor.Stop();
}
/*****************************************************************************/
void InputMediator::ReadOp(int fd)
{
    boost::shared_ptr<InputMediatorPacket> packet_ptr = m_inputProxy->ReadOp(fd);


    if (!strcmp(packet_ptr->m_buffer,"exit\n"))
    {
        Stop();
        std::cout << "exiting" << std::endl;
    }
    else 
    {
        std::cout << packet_ptr->m_buffer << std::endl;
    }

}
/*****************************************************************************/
void InputMediator::WriteOp(int fd)
{
    m_inputProxy->WriteOp(fd);
}
/*****************************************************************************/
void InputMediator::ExceptionOp(int fd)
{
    m_inputProxy->ExceptionOp(fd);
}
/*****************************************************************************/
void InputMediator::DeliverTask(const InputMediatorPacket& packet)
{
    ThreadPool *pool = Singleton<ThreadPool>::Handleton();
    (void)pool;
    (void)packet;
}


}//end ilrd-100
/*****************************************************************************/
