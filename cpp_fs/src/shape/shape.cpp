/****************************************************************************
* FILE: shapes.cpp		     PURPOSE: API for Shapes
*
* DEVELOPER: DanielZ		 TEAM: RD100
*
* REVIEWER:  Liad Oz   	  	 STATUS: Approved
*
****************************************************************************/
#include <iostream> //std::cout
#include <cstring> //strlen, strcpy
 
#include "shape.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "rectangle.hpp"

namespace ilrd_rd100
{//ilrd_rd100 start

/*****************************************************************************/
    Shape::Shape():m_offset(0){}
    Shape::~Shape(){}

    Shape &Shape::Move(size_t offset)
    {
        m_offset += offset;
        return *this;
    }

    std::string Shape::SpaceCreator() const
    {
        std::string str;
        size_t i = 0;
        for(i = 0; i < m_offset; ++i)
        {
            str += " ";
        }
        return str;
    }

    size_t Shape::GetOffset() const
    {
        return m_offset;
    }

/*****************************************************************************/
    Line::~Line(){}

    void Line::Draw() const
    {
        std::string s1 = SpaceCreator();
        s1 += "LINE";
        std::cout<< s1 << std::endl;
    }
/*****************************************************************************/
    Circle::~Circle(){}

    void Circle::Draw() const
    {
       std::string s1 = SpaceCreator();
       s1 += "CIRCLE";
       std::cout<< s1 << std::endl;
    }
/*****************************************************************************/
    Rectangle::~Rectangle(){}

    void Rectangle::Draw() const
    {
        std::string s1 = SpaceCreator();
        s1 += "RECTANGLE";
        std::cout<< s1 << std::endl;
    } 
/*****************************************************************************/
    Square::~Square(){}

    void Square::Draw() const
    {
       std::string s1 = SpaceCreator();
       s1 += "SQUARE";
       std::cout<< s1 << std::endl;
    }  
}//ilrd_rd100 end
