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

int *main_ptr = Singleton<int>::Get();

extern int *ptr1;

int main()
{
    
    if(main_ptr == ptr1)
    {
        std::cout<<"works" <<std::endl;
    }

    return 0;
}


/*****************************************************************************/
