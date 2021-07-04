/*****************************************************************************
*	FILENAME:	reactor_test.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for reactor lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <iostream> //std::cout
#include <boost/bind.hpp> //boost::bind

#include "reactor.hpp"

using namespace ilrd_rd100;

void RecieveStdIn(int fd, Reactor *reactor)
{
   char buff[100] = {0};

    read(fd, buff, 100);

    if (!strcmp(buff,"exit\n"))
    {
        reactor->Stop();
        std::cout << "exiting" << std::endl;
    }
    else if (!strcmp(buff,"What is your name\n"))
    {
        std::cout << "Daniel Z" << std::endl;
    }
}

int main()
{
    Reactor reactor;
    boost::function<void(int)> func = boost::bind(RecieveStdIn, _1, &reactor);

    reactor.Add(func, STDIN_FILENO, Reactor::READ);

    reactor.Run();

    return 0;
}
