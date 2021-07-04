#include <stdio.h>
#include "priority_queue.h"
#include "utl.h"

int Comparator(const void *data1, const void *data2);
void Test();
int Match(const void *data, const void *parameter);

int main()
{
	Test();
	return 0;
}


int Comparator(const void *data1, const void *data2)
{
	return *((int *)data1) - *((int *)data2); 
}

void Test()
{
	p_queue_t *test1 = NULL;
	p_queue_t *test2 = NULL;
	size_t counter1 = 0;
	size_t counter2 = 0;
	int a = 33;
	int b = 12;
	int c = -56;
	int d = 100001;
	void *res = NULL; 
	
	test1 = PriorityQueueCreate(Comparator);
	test2 = PriorityQueueCreate(Comparator);
	
	PriorityQueueEnqueue(test1, &a);
	

	if(test1 && test2)
	{
		printf(CYAN"PriorityQueueCreate SUCCESS\n");
	}
	else
	{
		printf(RED"PriorityQueueCreate FAIL\n");
		
	}
	
	counter1 =  PriorityQueueSize(test1);
	counter2 =  PriorityQueueSize(test2);
	
	
	if(counter1 == 1 && counter2 == 0)
	{
		printf(CYAN"PriorityQueueSize SUCCESS\n");
	}
	else
	{
		printf(RED"PriorityQueueSize FAIL\n");
		
	}
	
	
	counter1 =  PriorityQueueIsEmpty(test1);
	counter2 =  PriorityQueueIsEmpty(test2);
	if(counter1 == 0 && counter2 == 1)
	{
		printf(CYAN"PriorityQueueIsEmpty SUCCESS\n");
	}
	else
	{
		printf(RED"PriorityQueueIsEmpty FAIL\n");
		
	}
	
	PriorityQueueEnqueue(test1,&c);
	PriorityQueueEnqueue(test1,&d);
	PriorityQueueEnqueue(test2,&b);
	
	if((*(int*)PriorityQueuePeek(test1)) == -56 && (*(int*)PriorityQueuePeek(test2)) == 12)
	{
		printf(CYAN"PriorityQueuePeek SUCCESS\n");
	}
	else
	{
		printf(RED"PriorityQueuePeek FAIL\n");
		
	} 
	
	counter1 =  PriorityQueueSize(test1);
	counter2 =  PriorityQueueSize(test2);
	
	if(counter1 == 3 && counter2 == 1)
	{
		printf(CYAN"PriorityQueueEnqueue SUCCESS\n");
	}
	else
	{
		printf(RED"PriorityQueueEnqueue FAIL\n");
		
	}
	
	PriorityQueueDequeue(test1);
	counter1 = PriorityQueueSize(test1);
	
	if((*(int*)PriorityQueuePeek(test1)) == 33 && counter1 == 2)
	{
		printf(CYAN"PriorityQueueDequeue SUCCESS\n");
	}
	else
	{
		printf(RED"PriorityQueueDequeue FAIL\n");
		
	} 
	PriorityQueueEnqueue(test2,&b);
	PriorityQueueEnqueue(test2,&a);
	PriorityQueueEnqueue(test2,&c);
	PriorityQueueEnqueue(test2,&d);
	
	
	res = PriorityQueueErase(test2, Match, &b);
	counter2 = PriorityQueueSize(test2);
	
	if((*(int*)res == 12 && counter2 == 4))
	{
		printf(CYAN"PriorityQueueErase SUCCESS\n");
	}
	else
	{
		printf(RED"PriorityQueueErase FAIL\n");
		
	}
	
	PriorityQueueClear(test1);
	PriorityQueueClear(test2);
	
	counter1 =  PriorityQueueSize(test1);
	counter2 =  PriorityQueueSize(test2);
	
	if(counter1 == 0 && counter2 == 0)
	{
		printf(CYAN"PriorityQueueClear SUCCESS\n");
	}
	else
	{
		printf(RED"PriorityQueueClear FAIL\n");
		
	}
	PriorityQueueDestroy(test1);
	PriorityQueueDestroy(test2);
}



int Match(const void *data, const void *parameter)
{
	return (*((int *)data) == *((int *)parameter));
}


