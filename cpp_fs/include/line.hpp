/*****************************************************************************
 *	FILENAME:	square.hpp              AUTHOR: Daniel Z     LAB: RD100	     *
 *																			 *
 *	VERSION:	3															 *
 *																			 *
 *	PURPOSE:   API for square lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_LINE_HPP__
#define __ILRD_RD100_LINE_HPP__

#include "shape.hpp"
/*****************************************************************************/
namespace ilrd_rd100
{

class Line: public Shape
{
public:
    virtual ~Line();
    virtual void Draw() const;
protected:
};

} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_LINE_HPP__

