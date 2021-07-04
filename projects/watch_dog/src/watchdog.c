/****************************************************************************
* FILE: watchdog.c  Purpose: library for avl data structure
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Elizabeta Vitovsky		STATUS: 
*
****************************************************************************/
#define _POSIX_C_SOURCE 200809L /*for setenv*/
/*standart lib */ 
#include <stdio.h>
#include <stdlib.h> /* strtol, atoi, setenv, getenv */
#include <assert.h> /*asserts*/
#include <pthread.h> /*torjan horse thread into */

/*fork stuff*/
#include <sys/wait.h> /* wait */
#include <unistd.h> /* fork */
#include <errno.h> /* perror */
#include <signal.h> /* signal */

/* named semaphore includes*/
#include <semaphore.h>
#include <fcntl.h> /* O_CREAT flag in sem init */

/* my implemented libs for creating watch dog */
#include "scheduler.h"
#include "watchdog_util.h"
#include "watchdog.h"

/*globals*/

/* misses counters */
sig_atomic_t user_sig_misses = 0;
sig_atomic_t wd_sig_misses = 0;
/* stop flag */
sig_atomic_t sched_stop = 0;
/* thread pid */
pthread_t thread_pid = 0;
/* named semaphores objects */
sem_t *sem_user = NULL;
sem_t *sem_dog = NULL;
sem_t *sem3 = NULL;

/***************/
/*API FUNCTIONS*/
/***************/
int MMI(int argc,
        char **argv,
        time_t interval,
        int grace, 
        int startup_defend,
        wd_call_back call_back,
        void *call_back_param)
{
    wd_status_t status = SUCCESS_WD;

    /* updating sig handlers and initing semaphores also creating env vars */
    WDUserUpdateSigHandlers();
    status = SemaphoresInit();
    if( SUCCESS_WD != status )
    {
        return SEM_ERR;
    }

    status = WDEnvIntervalGraceUserPid(interval, grace);
    if( SUCCESS_WD != status )
    {
        return ENV_ERR;
    }

    /* spawning watch dog */
    status = WDSpawn(argv);
    if( SUCCESS_WD != status )
    {
        return status;
    }

    /* creating user sched thread {adding tasks + running } */
    status = pthread_create(&thread_pid ,NULL ,WDUserSched,(void*)argv);
    if( EAGAIN == status )
    {
        return THREAD_ERR;
    }

    /* wating for user and dog scheduler to be ready */
    status = sem_wait(sem3);
    if( SUCCESS_WD != status )
    {
        return SIGNAL_ERR;
    }

    (void)argc;
    (void)startup_defend;
    (void)call_back;
    (void)call_back_param;
    return SUCCESS_WD;
}
/******************************************************************/
int DNR(void)
{
    void *user_sched = NULL;
    wd_status_t status = SUCCESS_WD;
    sched_stop = 1;
    
    status = kill(GetDogPid(), SIGUSR2);
    if( SUCCESS_WD != status )
    {
        return KILL_ERR;
    }
    
    wait(&status);
    status = pthread_join(thread_pid, &user_sched);
    if( SUCCESS_WD != status )
    {
        return THREAD_ERR;
    }

    SchedulerDestroy((scheduler_t*)user_sched);

    status = SemaphoresClose();
    if( SUCCESS_WD != status )
    {
        return SEM_ERR;
    }

    return SUCCESS_WD;
}
/********************************************************************/
/*                        UTIL FUNCTIONS                            */
/********************************************************************/
/******************************************************************/
wd_status_t WDSpawn(char **argv)
{
    pid_t wd_pid = 0;
    wd_status_t status = SUCCESS_WD;

    /* forking to watch-dog process */
    wd_pid = fork();
    if( FORK_ERR == wd_pid )
    {
        return FORK_ERR;
    }
    /* adding environment var watch-dog pid number */
    status = WDEnvPids(wd_pid);
    if( SUCCESS_WD != status)
    {
        return ENV_ERR;
    }

    if ( 0 == wd_pid ) /* wd_process */
    {
        execv(WD_EXEC_PATH,argv);
        return EXEC_ERR;
    }
    return SUCCESS_WD;
}
/******************************************************************/
void *WDUserSched(void *arg)
{
    scheduler_t *user_sched = SchedulerCreate();
    if (NULL == user_sched)
    {
        return NULL;
    }

    assert(arg);

    SchedulerAddTask(user_sched,
                     WDFeed,
                     DestroyDummyFunction,
                     GetInterval(),
                     NULL);

    SchedulerAddTask(user_sched,
                     WDIsDogAlive,
                     DestroyDummyFunction,
                     GetInterval(),
                     (void*)arg);

    SchedulerAddTask(user_sched,
                     WDTerminate,
                     DestroyDummyFunction,
                     1,
                     (void*)user_sched);

    /* waiting for the barrier */
    HandShakeUser();

    SchedulerRun(user_sched);
    
    return user_sched;
}
/******************************************************************/
void WDDogSched(scheduler_t *dog_sched, char **argv)
{
    
    SchedulerAddTask(dog_sched,
                     UserFeed,
                     DestroyDummyFunction,
                     GetInterval(),
                     NULL);

    SchedulerAddTask(dog_sched,
                     WDIsUserAlive,
                     DestroyDummyFunction,
                     GetInterval(),
                     (void*)argv);

    SchedulerAddTask(dog_sched,
                     WDTerminate,
                     DestroyDummyFunction,
                     1,
                     (void*)dog_sched);

    /* waiting for the barrier */
    HandShakeDog();

    SchedulerRun(dog_sched);

}
/********************************************************************/
wd_status_t WDEnvIntervalGraceUserPid(time_t interval, int grace)
{
    char buffer[LENGTH] = "";
    wd_status_t status = SUCCESS_WD;

    sprintf(buffer,"%ld", interval);
    status = setenv("INTERVAL",buffer , OVERWRITE);

    sprintf(buffer,"%d", grace);
    status = setenv("GRACE",buffer , OVERWRITE);    

    sprintf(buffer,"%d", getpid());
    status = setenv("USER_PID",buffer , OVERWRITE); 

    if( SUCCESS_WD != status)
    {
        return ENV_ERR;
    }
    return status;
}
/******************************************************************/
wd_status_t WDEnvPids(pid_t dog_pid)
{
    char buffer[LENGTH] = "";
    wd_status_t status = SUCCESS_WD;

    sprintf(buffer,"%d", dog_pid);
    status = setenv("DOG_PID",buffer , OVERWRITE);

    if( SUCCESS_WD != status)
    {
        return ENV_ERR;
    }
    return status;
}
/********************************************************************/
void ArgvPrint(char **argv)
{
	size_t count = 0;	
	assert(argv);
	
    puts("\nCOMMAND LINE ARGUMENTS");
    puts("**********************");

	while(*argv)
	{
		printf("#%lu) %s \n",count ,*argv);	
		++argv;
        ++count;	
	}
	puts("");
}
/********************************************************************/
/*                            TASKS                                 */
/********************************************************************/
int WDFeed(void *arg)
{
    wd_status_t status = SUCCESS_WD;

    (void)arg;

    status = kill(GetDogPid(), SIGUSR1);
    if( SUCCESS_WD != status )
    {
        return KILL_ERR;
    }

    return status;
}
/********************************************************************/
int UserFeed(void *arg)
{
    wd_status_t status = SUCCESS_WD;
    
    (void)arg;

    status = kill(GetUserPid(), SIGUSR1);
    if( SUCCESS_WD != status )
    {
        return KILL_ERR;
    }

    return status;
}
/********************************************************************/
/********************************************************************/
int WDIsDogAlive(void *arg)
{
    char **argv = NULL;
    wd_status_t status = 0;

    assert(arg);

    argv = (char**)arg;

    if( wd_sig_misses >= GetGrace() )
    {
        wd_sig_misses = 0;

        status = kill(GetDogPid(), SIGKILL);
        if( SUCCESS_WD != status )
        {
            return KILL_ERR;
        }

        waitpid(GetDogPid(), NULL, 0); 
        status = WDSpawn(argv);
        if( SUCCESS_WD != status )
        {
            return status;
        }

        HandShakeUser();
    }
    else
    {
        ++wd_sig_misses;
    }
    return SUCCESS_WD;
}
/********************************************************************/
int WDIsUserAlive(void *arg)
{
    char **argv = NULL;
    int status = 0;

    assert(arg);

    argv = (char**)arg;
    if( user_sig_misses >= GetGrace() )
    {
        /*sending termination signal to parent id which is process id*/
        user_sig_misses = 0;
        
        status = kill(GetUserPid(), SIGKILL); 

        waitpid(GetUserPid(), NULL, 0);  

        execv(argv[0], argv); 
        return EXEC_ERR;
    }
    else
    {
        ++user_sig_misses;
    }
    return status;
}
/********************************************************************/
int WDTerminate(void *arg)
{
	scheduler_t *sched = NULL;
    assert(arg);

    sched = (scheduler_t*)arg;

	if( 1 == sched_stop )
    {
        SchedulerStop(sched);
    }
	return SUCCESS_WD;
}
/********************************************************************/
void DestroyDummyFunction(void *arg)
{
    (void)arg;
}
/********************************************************************/
/*                            HANDLERS                              */
/********************************************************************/
void WDDogUpdateSigHandlers(void)
{
    struct sigaction sa = {0};

    sa.sa_handler = &WDDogHandler1;
    sigaction (SIGUSR1, &sa, NULL);

    sa.sa_handler = &WDDogHandler2;
    sigaction (SIGUSR2, &sa, NULL);
}
/********************************************************************/
void WDUserUpdateSigHandlers(void)
{
    struct sigaction sa = {0};

    sa.sa_handler = &WDUserHandler1;
    sigaction (SIGUSR1, &sa, NULL);
}
/********************************************************************/
void WDDogHandler1(int sig_num)
{
    (void)sig_num;
    user_sig_misses = 0;
    write(STDOUT_FILENO,"dog handler1\n",14);
}
/********************************************************************/
void WDDogHandler2(int sig_num)
{
    write(STDOUT_FILENO,"dog handler2\n",14);
    sched_stop = 1;

    (void)sig_num;
}
/********************************************************************/
void WDUserHandler1(int sig_num)
{
    wd_sig_misses = 0;
    write(STDOUT_FILENO,"user handler1\n",15);
    (void)sig_num;
}
/********************************************************************/
/*                         Get functions                            */
/********************************************************************/
time_t GetInterval(void)
{
    return strtol(getenv("INTERVAL"),NULL, 10);
}
/********************************************************************/
int GetGrace(void)
{
    return atoi(getenv("GRACE"));
}
/********************************************************************/
pid_t GetDogPid(void)
{
    return atoi(getenv("DOG_PID"));
}
/********************************************************************/
pid_t GetUserPid(void)
{
    return atoi(getenv("USER_PID"));
}
/********************************************************************/
/*                         Sync functions                           */
/********************************************************************/
wd_status_t SemaphoresInit(void)
{
    sem_user = sem_open("/sem_user",O_CREAT,S_IRWXU,0);
    sem_dog = sem_open("/sem_dog",O_CREAT,S_IRWXU,0);
    sem3 = sem_open("/sem3",O_CREAT,S_IRWXU,0);

    if( SEM_FAILED == sem_user || SEM_FAILED == sem_dog || SEM_FAILED == sem3 )
	{
		return SEM_ERR;
	}
    return SUCCESS_WD;
}
/********************************************************************/
wd_status_t SemaphoresClose(void)
{
    wd_status_t status = SUCCESS_WD;

    status = sem_close(sem_user);
    status = sem_close(sem_dog);
    status = sem_close(sem3);

    status = sem_unlink("sem_user");
    status = sem_unlink("sem_dog");
    status = sem_unlink("sem3");
 
    if( SUCCESS_WD != status )
	{
		return SEM_ERR;
	}
    return SUCCESS_WD;
}
/********************************************************************/
void HandShakeUser(void)
{
    sem_post(sem_dog);
    sem_wait(sem_user);
    sem_post(sem3);
}

void HandShakeDog(void)
{
    sem_wait(sem_dog);
    sem_post(sem_user);
}