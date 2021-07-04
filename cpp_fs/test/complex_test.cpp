/****************************************************************************
* FILE: complex_test.cpp            Purpose: Implementation for Complex Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Elizabeta Vitovsky		STATUS: Approved
*
*
****************************************************************************/
#include <iostream> //io tests
#include <sstream> //string stream
#include <string> //string
#include <ctime> //clock_t

#include "complex.hpp"
#include "tester.hpp"
using namespace ilrd_rd100;

void CreationTest(void);
void StreamOpTest(void);
void OpTest(void);
void BenchmarkTest(void);

int main()
{

    CreationTest();

    StreamOpTest();

    OpTest();

    BenchmarkTest();

    TestReport("Report Summary");

}


void StreamOpTest(void)
{
    Complex c2(5, -9);
    
    std::ostringstream lhs_stream;
    std::ostringstream rhs_stream;

    char imSign = ((c2.GetImaginary() < 0) ? (0) : ('+'));

    lhs_stream << c2;
    rhs_stream << c2.GetReal()<< imSign << c2.GetImaginary() << "i" << std::endl;

    std::string lhs_str = lhs_stream.str();
    std::string rhs_str = rhs_stream.str();

    Test(lhs_str, rhs_str,"Operator <<", __LINE__ );

    std::cin >> c2;

    std::cout<< c2;
}

void CreationTest(void)
{
    Complex c1;
    Complex c2(5, -3);
    Complex c3(-8, -1);
    Complex c4(-8);
    Complex c5(c2);
    
    Test(c1,Complex(0, 0), "Default Ctor", __LINE__ );
    Test(c2,Complex(5, -3), "Ctor (int, int)", __LINE__ );
    Test(c3,Complex(-8, -1), "Ctor (int, int)", __LINE__ );
    Test(c4,Complex(-8), "Ctor (int)", __LINE__ );
    Test(c5,c2, "Copy constructor", __LINE__ );

    Complex c[5];
    c[1] = c2; 
    c[2] = c3; 
    Test(c[1],c2, "Creation of array", __LINE__ );
    Test(c[2],c3, "Creation of array", __LINE__ );
}

void OpTest(void)
{
    Complex c2(5, -3);
    Complex c3(-8, -1);

    Test(c2 + c3,Complex(-3, -4), "Regular Addition", __LINE__ );
    Test(c2 - c3,Complex(13, -2), "Regular Substraction", __LINE__ );
    Test(c2 * c3,Complex(-43, 19), "Regular Multiplying", __LINE__ );
    Test(c2 / c3,Complex((-37.0/65.0), (29.0/65.0)), "Regular Division", __LINE__ );

    c3 += c2;
    Test(c3,Complex(-3, -4), "Compound Addition", __LINE__ );

    c3 -= c2;
    Test(c3,Complex(-8, -1), "Compund Substraction", __LINE__ );

    c3 *= c2;
    Test(c3,Complex(-43, 19), "Compund Multiplying", __LINE__ );

    c3 /= c2;
    Test(c3,Complex(-8, -1), "Compund Division", __LINE__ );
}

void BenchmarkTest(void)
{
    size_t i = 0;

    Complex c1(1,1);

    clock_t tick = clock();

    for(; i < 10000000; ++i)
    {
        c1 = c1 + 1;
    }


   std::cout << "Time: " << (clock() - tick)/(CLOCKS_PER_SEC*1.0) << std::endl;

    /* when you use return by val, while not using implicit or 
    explicit declaration the compiler knows to optimize it and he woent call Cctor
    and thus the penalty is minor */

    /* This phenomenon called copy elision (== "emited Cctor") */

}
