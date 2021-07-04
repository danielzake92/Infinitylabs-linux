/*****************************************************************************
 *	FILENAME:	p3_shm.c                   AUTHOR: Daniel Zaken  LAB: RD100	 *
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
    char *shared_mem = NULL;

    key_t key = ftok("my shm", 10);

    /* Getting shared mem id */
    int shm_id = shmget(key,PAGE_SIZE, 0666|IPC_CREAT );

    /* attaching the shm_mem into process v mem */
    shared_mem = (char*)shmat(shm_id, NULL, 0);

    printf("p3_read = %s\n", shared_mem);

    /* detaching the shm_mem from process v mem */
    shmdt(shared_mem);

    return 0;
}

//ipcrm -a