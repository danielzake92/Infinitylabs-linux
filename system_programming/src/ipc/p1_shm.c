/*****************************************************************************
 *	FILENAME:	p1_shm.c                   AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Implementing for ipc lib.					    		     *
 *																			 *
 *****************************************************************************/
#include <sys/shm.h> //shared memory
#include <stdio.h> //printf

#define PAGE_SIZE 0x1000

/*****************************************************************************/

int main()
{
    int shm_id = 0;
    char *shared_mem = NULL;

    /* creating unique key */
    key_t key = ftok("my shm", 10);

    /* creating shared mem id */
    shm_id = shmget(key,PAGE_SIZE ,
                    IPC_CREAT | IPC_EXCL | 0666 );

    printf("shm_id = %d ->created\n", shm_id);

    /* attaching the shm_mem into process v mem */
    shared_mem = (char*)shmat(shm_id, NULL, 0);

    sprintf(shared_mem, "hello world written in p1");

    /* detaching the shm_mem from process v mem */
    shmdt(shared_mem);

    return 0;
}

//ipcrm -a