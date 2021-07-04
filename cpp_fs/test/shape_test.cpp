/****************************************************************************
* FILE: rc_string_test.cpp		    PURPOSE: Implementation for RCString Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: ******* 				STATUS: Approved
*
****************************************************************************/

#include "shape.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "tester.hpp" //test utils lib
using namespace ilrd_rd100;

int main()
{
    Line l1;

    l1.Draw();
    l1.Move(4);
    l1.Draw();

    Circle c1;

    c1.Draw();
    c1.Move(6);
    c1.Draw();

    Rectangle r1;

    r1.Draw();
    r1.Move(9);
    r1.Draw();

    Square s1;

    s1.Draw();
    s1.Move(6);
    s1.Draw();

    Shape *arr[4] = {0};

    arr[0] = new Line;
    arr[1] = new Circle;
    arr[2] = new Rectangle;
    arr[3] = new Square;

    size_t i = 0;

    for(; i < 4; ++i)
    {
        arr[i]->Draw();
        arr[i]->Move(4);
        arr[i]->Draw();
    }

    delete arr[0];
    delete arr[1];
    delete arr[2];
    delete arr[3];
     
    return 0;
}

