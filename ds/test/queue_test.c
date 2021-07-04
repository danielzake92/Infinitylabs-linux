#include <stdio.h>
#include "singly_linked_list.h"/*Lib header*/
#include "queue.h"/*Lib header*/



void Test();

int main()
{
	Test();
	return 0;
}


void Test()
{
	int a = 77;
	int b = 90;
	int c = 1;
	int d = -32;
	int e = 7;
	int f = 12;
	queue_t *q1 = NULL;
	queue_t *q2 = NULL;
	
	q1 = QueueCreate();
	q2 = QueueCreate();
/****************************************************************************/   	
 	printf ("\033[34;1mLISTS EMPTINESS CHECK\033[0m \n");
    
	printf("is q1 empty -> %d  queue size -> %ld \n",QueueIsEmpty(q1), QueueSize(q1) );
    printf("is q2 empty -> %d  queue size -> %ld \n",QueueIsEmpty(q2), QueueSize(q2) );	
/****************************************************************************/ 
	printf ("\033[34;1mq1 - ENQUEUE - three times\033[0m \n");

	QueueEnqueue(q1, (int*)(&a) );
	printf("Enqueued a = %d \n", a);
	QueueEnqueue(q1, (int*)(&b) );
	printf("Enqueued b = %d \n", b);
	QueueEnqueue(q1, (int*)(&c) );
	printf("Enqueued c = %d \n", c);
	printf("q1 peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
/****************************************************************************/   
	printf ("\033[34;1mq1 - DEQUEUE - three times\033[0m \n");
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("is q1 empty -> %d  queue size -> %ld \n",QueueIsEmpty(q1), QueueSize(q1) );
/****************************************************************************/   
	printf ("\033[34;1mq1 - ENQUEUE again - three times\033[0m \n");
	
	QueueEnqueue(q1, (int*)(&a) );
	printf("Enqueued a = %d \n", a);
	QueueEnqueue(q1, (int*)(&b) );
	printf("Enqueued b = %d \n", b);
	QueueEnqueue(q1, (int*)(&c) );
	printf("Enqueued c = %d \n", c);
	printf("q1 peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
/****************************************************************************/   
	printf ("\033[34;1mq2 - ENQUEUE - three times\033[0m \n");	
	
	
	QueueEnqueue(q2, (int*)(&d) );
	printf("Enqueued d = %d \n", d);
	QueueEnqueue(q2, (int*)(&e) );
	printf("Enqueued e = %d \n", e);
	QueueEnqueue(q2, (int*)(&f) );
	printf("Enqueued f = %d \n", f);
	printf("q2 peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q2) ),QueueIsEmpty(q2), QueueSize(q2) );

/****************************************************************************/    
    printf ("\033[34;1mAfter Appending\033[0m \n");
    QueueAppend(q1, q2);
	
	printf("is q1 empty -> %d  queue size -> %ld \n",QueueIsEmpty(q1), QueueSize(q1) );
    printf("is q2 empty -> %d  queue size -> %ld \n",QueueIsEmpty(q2), QueueSize(q2) );	
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("peeked val -> %d    is queue empty -> %d  queue size -> %ld \n", ( *(int *)QueuePeek(q1) ),QueueIsEmpty(q1), QueueSize(q1) );
	puts("Dequeue");
	QueueDequeue(q1);
	
	printf("is q1 empty -> %d  queue size -> %ld \n",QueueIsEmpty(q1), QueueSize(q1) );
	
	QueueDestroy(q1);
	QueueDestroy(q2);
}
