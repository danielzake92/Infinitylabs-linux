/********************************************************************************
 *  FILENAME:  sorted_list.c  DEVELOPER: Daniel Zaken   TEAM: Blue              * 
 *                                                                              *
 *  Reviwer:   Vladi                                                            * 
 *                                                                              *
 *  PURPOSE:   Library for Modifying & creating Sortedlist          			*
 *                                                                              *
 *******************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <unistd.h>
#include <pthread.h> /* thread is needed */
#include <semaphore.h> /*sem_t*/
#include <sys/types.h> /*pid_t type*/
#include <sys/syscall.h>
#include <stdatomic.h>    /* atomic size_t */
#include "uid.h"
#include "utl.h"


# if __WORDSIZE == 64
#  define SIZE_MAX              (18446744073709551615UL)
# else
#  define SIZE_MAX              (4294967295U)
# endif


static atomic_size_t g_count = 1;

/*
void __attribute__((constructor)) InitMutex(void);
void __attribute__((destructor)) DestroyMutex(void);
*/

ilrd_uid_t UIDCreate() 
{
	ilrd_uid_t uid = {0};

	uid.pid = getpid();
	uid.creation_time = time(NULL);

	uid.counter = __sync_add_and_fetch(&g_count,1); /*atomic add and sync operation */
	
	return uid;
}



int UIDIsSame(ilrd_uid_t id1,ilrd_uid_t id2)
{
	return ( id1.pid == id2.pid
			&& id1.creation_time == id2.creation_time
			&& id1.counter == id2.counter );
}


ilrd_uid_t UIDGetBadUID()
{
	ilrd_uid_t uid = {0};
	
	uid.pid = -1;
	uid.creation_time = -1;
	uid.counter = 0;
	
	return uid;
}
/*
void __attribute__((constructor)) InitMutex(void)
{
	pthread_mutex_init(&mutex, NULL);
}
void __attribute__((destructor)) DestroyMutex(void)
{
	pthread_mutex_destroy(&mutex);
}
*/