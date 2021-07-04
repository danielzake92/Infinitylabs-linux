/*****************************************************************************
 *	FILENAME:	singleton.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for singleton lib.							     *
 *																			 *
 *****************************************************************************/
#include <iostream>
#include <dlfcn.h>
#include "singleton.hpp"
/*****************************************************************************/

using namespace ilrd_rd100;

int *main_ptr = Singleton<int>::Get();



int main()
{
    void *handle;

    handle = dlopen("./libfile1.so", RTLD_LOCAL | RTLD_LAZY);

    void(*ptr_get)(void) = reinterpret_cast<void(*)(void)>((dlsym(handle, "foo")));

    ptr_get();

    std::cout<<Singleton<int>::Get() <<std::endl;

    return 0;
}


/*****************************************************************************/
