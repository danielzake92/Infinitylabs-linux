/****************************************************************************
* FILE: watchdog_test.c  Purpose: library for avl data structure
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    ------------  			STATUS: 
*
****************************************************************************/
#include <stdio.h>
#include <unistd.h> /* sleep */

#include "watchdog.h"


int main(int argc, char *argv[])
{
    int i = 15;

    MMI(argc, argv,1 ,3, 0,NULL ,NULL );
    
    printf("watchdog_test\n");

    while(i)
    {
        sleep(1);
        --i;
    }

    DNR();

    puts("After DNR  -> user process has ended");
    (void)argc;

    return 0;
}


