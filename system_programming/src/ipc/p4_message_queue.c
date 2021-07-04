/*****************************************************************************
 *	FILENAME:	p4_message_queue.c         AUTHOR: Daniel Zaken  LAB: RD100	 
 *																			 
 *	REVIEWER:	Or Katz													     
 *																			 
 *	PURPOSE:    Implementing for ipc lib.  STATUS: IMPL DONE	    	     
 *																			 
 *****************************************************************************/
#define _GNU_SOURCE //msg
#include <sys/shm.h> //shared memory
#include <stdio.h> //printf
#include <sys/msg.h> //msg unix api
/*****************************************************************************/
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

    /* creating shared mem id */
    q_id = msgget(key, 0666 | IPC_CREAT );


    msgrcv(q_id,&msg,sizeof(msg),0, IPC_NOWAIT | MSG_COPY);

    printf("(p4)msg = %s\n", msg.msg_text);

    msgctl(q_id,IPC_RMID,NULL);

    printf("q_id = %d ->destroyed\n", q_id);

    return 0;
}
