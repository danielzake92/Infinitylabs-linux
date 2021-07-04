/*****************************************************************************
 *	FILENAME:	input_proxy.hpp        AUTHOR: Or Katz  LAB: RD100	 
 *																			 
 *	VERSION:	2															 
 *																			 
 *	PURPOSE:   API for input_proxy lib.							             
 *																			 
 *****************************************************************************/

#ifndef __ILRD_RD100_INPUT_PROXY_HPP__
#define __ILRD_RD100_INPUT_PROXY_HPP__ 

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/shared_ptr.hpp> //shared_ptr
#include "input_mediator_packet.hpp" //input_mediator_packet
/*****************************************************************************/
namespace ilrd_rd100
{

class InputProxy : private boost::noncopyable
{//start InputProxy
public:
    virtual ~InputProxy() =0;
    virtual boost::shared_ptr<InputMediatorPacket> ReadOp(int fd) =0;
    virtual boost::shared_ptr<InputMediatorPacket> WriteOp(int fd) =0;
    virtual boost::shared_ptr<InputMediatorPacket> ExceptionOp(int fd) =0;
    static InputProxy *Create();
};//end InputProxy



} //ilrd_rd100
#endif // __ILRD_RD100_INPUT_PROXY_HPP__
