/*****************************************************************************
* FILE:      simple_wd.h	           PURPOSE: Simple watchdog entrance point
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  		                   STATUS: Imp tested
******************************************************************************/

#ifndef __ILRD_SIMPLE_WD_H__
#define __ILRD_SIMPLE_WD_H__


#include <stddef.h> /*size_t*/

typedef enum wd_status
{
    FORK_ERR = -1,
    SUCCESS = 0,
    EXEC_ERR = 1,
    NEW_PROCESS_ERR = 2,
    SHELL_ERR = 127
}wd_status_t;

typedef enum function
{
    FORKEXEC = 0,
    SYSTEM = 1,
    FUNC_NUM = 2
}func_t; 

typedef wd_status_t (*spawn_t) ( const char *path,char *const argv[]);

wd_status_t ForkExec( const char *path,char *const argv[]);

wd_status_t SysExec( const char *path,char *const argv[]);





#endif
