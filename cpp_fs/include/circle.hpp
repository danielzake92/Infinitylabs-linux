/*****************************************************************************
 *	FILENAME:	square.hpp              AUTHOR: Daniel Z     LAB: RD100	     *
 *																			 *
 *	VERSION:	3															 *
 *																			 *
 *	PURPOSE:   API for square lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_CIRCLE_HPP__
#define __ILRD_RD100_CIRCLE_HPP__

#include "shape.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class Circle: public Shape
{
public:
    virtual ~Circle();
    virtual void Draw() const;
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_CIRCLE_HPP__

