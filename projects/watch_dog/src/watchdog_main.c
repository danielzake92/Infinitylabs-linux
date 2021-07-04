/****************************************************************************
* FILE: watchdog_main.c  Purpose: library for avl data structure
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    -----------  			STATUS: 
*
****************************************************************************/
#include <stdio.h>

#include "watchdog_util.h"
#include "watchdog.h"


int main(int argc, char *argv[])
{
    scheduler_t *dog_sched = NULL;
    /* init semaphores */
    SemaphoresInit();
    /* init signal handlers for dog */
    WDDogUpdateSigHandlers();
    
    dog_sched = SchedulerCreate();
    if (NULL == dog_sched)
    {
        return 0;
    }
    /* creating dog sched thread {adding tasks + running } */
    WDDogSched(dog_sched, argv);
    /* destroying scheduler */
    SchedulerDestroy(dog_sched);
    /* closing and unlinking the semaphores */
    SemaphoresClose();

    (void)argc;
    return 0;
}