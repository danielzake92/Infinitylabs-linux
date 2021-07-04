/*****************************************************************************
 *	FILENAME:	input_proxy.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for input_proxy lib.							     *
 *																			 *
 *****************************************************************************/
#include <iostream> //std::cout
#include "input_proxy.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{
/*****************************************************************************/
/*                          Proxy Dummy Declaratoion                         */
/*****************************************************************************/
class ProxyDummy: public InputProxy
{
public:
    virtual ~ProxyDummy();
    virtual boost::shared_ptr<InputMediatorPacket> ReadOp(int fd);
    virtual boost::shared_ptr<InputMediatorPacket> WriteOp(int fd);
    virtual boost::shared_ptr<InputMediatorPacket> ExceptionOp(int fd);
};
/*****************************************************************************/
/*                          Proxy Dummy Impl                                 */
/*****************************************************************************/
ProxyDummy::~ProxyDummy()
{

}
/*****************************************************************************/
boost::shared_ptr<InputMediatorPacket> ProxyDummy::ReadOp(int fd)
{
    boost::shared_ptr<InputMediatorPacket> packet_ptr(new InputMediatorPacket());
    read(fd, packet_ptr->m_buffer, packet_ptr->MAX_PACKET_SIZE);

    return packet_ptr;
}
/*****************************************************************************/
boost::shared_ptr<InputMediatorPacket> ProxyDummy::WriteOp(int fd)
{
    (void)fd;
}
/*****************************************************************************/
boost::shared_ptr<InputMediatorPacket> ProxyDummy::ExceptionOp(int fd)
{
    (void)fd;
}
/*****************************************************************************/
/*                          Inptu Proxy Impl                                 */
/*****************************************************************************/
InputProxy::~InputProxy()
{
    /* EMPTY */
}
/*****************************************************************************/
InputProxy *InputProxy::Create()
{
    return new(ProxyDummy);
}
/*****************************************************************************/


}//end ilrd100
/*****************************************************************************/
