#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "uid.h"
#include "utl.h"

#define ARR_SIZE 10

void *ThreadFunc(void *arg);

void test1();
void test2();
void print(ilrd_uid_t uid);


ilrd_uid_t arr[ARR_SIZE];

int main()
{	
	int i = 0;
	printf ("%s*****************************************\n",RED);
	printf ("%s            Daniel Z tests               \n",RED);
	printf ("%s*****************************************\n",RED);
	
	test1();
	printf("TEST 2\n\n");
	test2();

	for(i = 0; i < ARR_SIZE; ++i)
	{
		print(arr[i]);
	}
	
	printf ("%s*****************************************\n",RED);
	printf ("%s---------------Test ended----------------\n",RED);
	printf ("%s*****************************************\n%s",RED,DEFAULT);
	
	return 0;
}

void test1()
{
	ilrd_uid_t uid1 = UIDCreate();
	
	ilrd_uid_t uid2 = {0};
	
	ilrd_uid_t uid3 = UIDGetBadUID();
	
	sleep(1);
	
	uid2 = UIDCreate();
	
	puts(GREEN"UID - 1");
	print(uid1);
	puts(GREEN"UID - 2");	
	print(uid2);
	puts(GREEN"BAD UID");	
	print(uid3);
	puts(GREEN"Is UID 1 and 2 are the smae");
	printf(YELLOW"UIDIsSame - %d\n",UIDIsSame(uid1, uid2));
	puts(GREEN"Is UID 1 and 1 are the smae");
	printf(YELLOW"UIDIsSame - %d\n",UIDIsSame(uid1, uid1));
}

void test2()
{
	pthread_t pth[ARR_SIZE] = {0}; 
	size_t i = 0;

	for(i = 0;i < ARR_SIZE; ++i)
	{
		pthread_create(&pth[i],NULL,ThreadFunc,(void*)i);
	}

	for(i = 0;i < ARR_SIZE; ++i)
	{
		pthread_join(pth[i],NULL);
	}
}


void *ThreadFunc(void *arg)
{
	size_t s_i = (size_t)arg;
	arr[s_i] = UIDCreate();
	return NULL;
}

void print(ilrd_uid_t uid)
{
	printf(YELLOW"my pid number : %d\n", uid.pid);
	printf(YELLOW"time creation : %ld\n", uid.creation_time);
	printf(YELLOW"count : %lu\n", uid.counter);
}