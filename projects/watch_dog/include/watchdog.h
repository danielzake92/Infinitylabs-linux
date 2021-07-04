/********************************************************************************
 *  FILENAME:  watchdog.h  DEVELOPER: Daniel Zaken   TEAM: Yellow                
 *                                                                             
 *  Reviwer:   Elizabeta vitovsky                                          
 *                                                                              
 *  PURPOSE:  LIB for modifying & creating a watchdog.             		
 *                                                                              
 *******************************************************************************/
#ifndef __ILRD_WATCHDOG_H__
#define __ILRD_WATCHDOG_H__

#include <stddef.h> /*required for size_t type*/
#include <time.h> /*time_t*/
#include <sys/types.h> /*pid_t*/

typedef int(*wd_call_back)(void *arg);
/* add explanation */
int MMI(int argc,
        char **argv,
        time_t interval,
        int grace, 
        int startup_defend,
        wd_call_back call_back,
        void *call_back_param);

/* add explanation */
int DNR(void);


#endif



/*****************************************************************************/







/*****************************************************************************/
