/*****************************************************************************
* FILE:      ping_pong.h	           PURPOSE: Signals Ping Pong
* DEVELOPER: Daniel Zaken              TEAM:    Yellow
*
* REVIEWER:  		                   STATUS: IMPL
******************************************************************************/

#ifndef __ILRD_PING_PONG_H__
#define __ILRD_PING_PONG_H__


#include <sys/types.h> /*pid_t*/

typedef enum pp_status
{
    FORK_ERR = -1,
    SUCCESS = 0,
    EXEC_ERR = 1,
    NEW_PROCESS_ERR = 2,
    SHELL_ERR = 127
}pp_status_t;


typedef enum function
{
    EX1 = 0,
    EX2 = 1,
    EX_NUM = 2
}func_t;


typedef pp_status_t (*ex_t) ( const char *path,char *const argv[]);

pp_status_t PP_EX1( const char *path,char *const argv[]);

pp_status_t PP_EX2( const char *path,char *const argv[]);

pp_status_t Spawn( const char *path,char *const argv[], pid_t *current_pid);

#endif
