/*****************************************************************************
 *	FILENAME:	singleton.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for singleton lib.							     *
 *																			 *
 *****************************************************************************/
#include <iostream>
#include "singleton.hpp"
/*****************************************************************************/
using namespace ilrd_rd100; 
int *ptr1 = Singleton<int>::Get();

extern "C" void foo()
{
    std::cout<<Singleton<int>::Get() <<std::endl;
}




/*****************************************************************************/
