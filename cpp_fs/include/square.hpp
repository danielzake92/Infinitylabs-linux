/*****************************************************************************
 *	FILENAME:	square.hpp              AUTHOR: Daniel Z     LAB: RD100	     *
 *																			 *
 *	VERSION:	3															 *
 *																			 *
 *	PURPOSE:   API for square lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_SQUARE_HPP__
#define __ILRD_RD100_SQUARE_HPP__

#include "shape.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{
    
class Square: public Shape
{
public:
    virtual ~Square();
    virtual void Draw() const;   
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_SQUARE_HPP__

