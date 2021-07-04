/********************************************************************************
 *  FILENAME:  watchdog_util.h  DEVELOPER: Daniel Zaken   TEAM: Yellow                
 *                                                                             
 *  Reviwer:   Elizabeta vitovsky                                             
 *                                                                              
 *  PURPOSE:  LIB for modifying & creating a watchdog.             		
 *                                                                              
 *******************************************************************************/
#ifndef __ILRD_WATCHDOG_UTIL_H__
#define __ILRD_WATCHDOG_UTIL_H__

#include "watchdog.h"
#include "scheduler.h"

#define DO_NOT_OVERWRITE     0
#define OVERWRITE            1
#define LENGTH               20
#define WD_EXEC_PATH         "./out/watchdog_main_DEBUG.out"

typedef enum WD_STATUS
{
    KILL_ERR = -2,
    FORK_ERR = -1,
    SIGNAL_ERR = -1,
    SUCCESS_WD = 0,
    EXEC_ERR = 1,
    THREAD_ERR = 3,
    ENV_ERR = 4,
    SEM_ERR = 5
}wd_status_t;

/*spawns a WD process*/
wd_status_t WDSpawn(char **argv);

/*user thread function that runs the scheduler*/
void *WDUserSched(void *arg);

/*watch dog function that runs the scheduler*/
void WDDogSched(scheduler_t *dog_sched, char** argv);

/*signal handler for wd for SIGUSR1*/
void WDDogHandler1(int sig_num);

/*signal handler for wd for SIGUSR2*/
void WDDogHandler2(int sig_num);

/*signal handler for user for SIGUSR1*/
void WDUserHandler1(int sig_num);

/*********/
/* TASKS */
/*********/

/*task for user feeding dog with signals*/
int WDFeed(void *arg);

/*task for dog feeding user with signals*/
int UserFeed(void *arg);

/*task for checking dog flag and handle*/
int WDIsDogAlive(void *arg);

/*task for checking user flag and handle*/
int WDIsUserAlive(void *arg);

/*task for terminating watchdog app*/
int WDTerminate(void *arg);

/* task for stopping the scheduler */
void DestroyDummyFunction(void *arg);

/*prints all the strings in argv*/
void ArgvPrint(char **argv);

/*void SIGUSR2_Handler(int signal_number);*/
void WDDogUpdateSigHandlers(void);
void WDUserUpdateSigHandlers(void);

/* ********************* */
/* environment functions */
/* ********************* */

/* Initiation of interval grace and user pid */
wd_status_t WDEnvIntervalGraceUserPid(time_t interval, int grace);

wd_status_t WDEnvPids(pid_t dog_pid);

time_t GetInterval(void);

int GetGrace(void);

pid_t GetDogPid(void);

pid_t GetUserPid(void);

/* ********************************/
/* semaphores and sync functions  */
/* ********************************/

wd_status_t SemaphoresInit(void);

wd_status_t SemaphoresClose(void);

void HandShakeUser(void);
void HandShakeDog(void);

#endif

