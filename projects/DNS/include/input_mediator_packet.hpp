/*****************************************************************************
 *	FILENAME:	packet.hpp        AUTHOR: Or Katz  LAB: RD100	 
 *																			 
 *	VERSION:	2															 
 *																			 
 *	PURPOSE:   API for packet lib.							             
 *																			 
 *****************************************************************************/

#ifndef __ILRD_RD100_INPUT_MEDIATOR_PACKET_HPP__
#define __ILRD_RD100_INPUT_MEDIATOR_PACKET_HPP__ 

#include <boost/interprocess/mapped_region.hpp> //get page size
#include <unistd.h> // uint64_t
/*****************************************************************************/
namespace ilrd_rd100
{

struct InputMediatorPacket
{
    enum Mode
    {
        READ = 0,
        WRITE = 1,
        EXCEPTION = 2,
        NUM_MODES = 3
    };
    uint64_t m_id;
    Mode m_cmdMode;
    static const int MAX_PACKET_SIZE = 1 << 16;
    char m_buffer[MAX_PACKET_SIZE];
}; //end InputMediatorPacket

}//ilrd_rd100
#endif // __ILRD_RD100_INPUT_MEDIATOR_PACKET_HPP__

