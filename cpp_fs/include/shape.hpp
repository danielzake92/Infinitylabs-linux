/*****************************************************************************
 *	FILENAME:	square.hpp              AUTHOR: Daniel Z     LAB: RD100	     *
 *																			 *
 *	VERSION:	3															 *
 *																			 *
 *	PURPOSE:   API for square lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_SHAPE_HPP__
#define __ILRD_RD100_SHAPE_HPP__

#include <iostream> //size_t & std::string
/*****************************************************************************/
namespace ilrd_rd100
{

class Shape
{
public:
    explicit Shape();
    virtual ~Shape();
    virtual void Draw() const = 0;
    virtual Shape& Move(size_t offset);
protected:
    size_t GetOffset() const;
    std::string SpaceCreator() const;
private:    
    size_t m_offset; 
};
 
} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_SHAPE_HPP__

