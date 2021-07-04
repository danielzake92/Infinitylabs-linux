/*****************************************************************************
 *	FILENAME:	p1_message_queue.c         AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			 
 *	REVIEWER:	Or Katz													     
 *																			 
 *	PURPOSE:    Implementing for ipc lib.  STATUS: IMPL DONE	    	     
 *																			 
 *****************************************************************************/
#include <sys/shm.h> //shared memory
#include <stdio.h> //printf
#include <sys/msg.h> //msg unix api
#include <string.h> //strcpy

/*****************************************************************************/
// structure for message queue

struct mesg_buffer
{
    long msg_type;
    char msg_text[100];
}msg;

int main()
{
    int q_id = 0;

    /* creating unique key */
    key_t key = ftok("my msg", 10);

    msg.msg_type = 1;
    strcpy(msg.msg_text, "hello world written in p1" );

    /* creating shared mem id */
    q_id = msgget(key, 0666 | IPC_CREAT );

    printf("q_id = %d ->created\n", q_id);

    msgsnd(q_id, &msg, sizeof(msg),0666);


    return 0;
}
