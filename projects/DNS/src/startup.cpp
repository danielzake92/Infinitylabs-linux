/*****************************************************************************
*	FILENAME:	startup.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for startup lib.							      	 *
 *																			 *
 *****************************************************************************/


/********************************* driver ************************************/
#include <iostream> // io
#include <unistd.h> //write

namespace ilrd_rd100
{

__attribute__((constructor))
static void example_plugin_ctor() 
{
    write(STDOUT_FILENO, "framework.so loaded!\n",22);
}

}
/*****************************************************************************/
