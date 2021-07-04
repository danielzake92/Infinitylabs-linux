#include <stdio.h>
#include "stack.h"

union 
{
	void *data;
	int num;
	float f;
	double d;
	char c;
	char *str;
}convert;

void StackTest(int a, char b, float c);

int main()
{	
	int i = 2000000000;
	float f = 150000.52;
	double d= 25000000000.326; 
	char c = 'a';
	char str[] = "hello world";
	
	stack_t *s1 = StackCreate(5);
/******************************************************************************/	
	convert.num = i;	
	StackPush(s1, convert.data);
	convert.data = StackPeek(s1);
    printf("%d\n",convert.num);
/******************************************************************************/		
	convert.f = f;
	StackPush(s1, convert.data);
	convert.data = StackPeek(s1);
    printf("%f\n",convert.f);
/******************************************************************************/	
	convert.d = d;
	StackPush(s1, convert.data);
	convert.data = StackPeek(s1);
    printf("%f\n",convert.d);
/******************************************************************************/	
	convert.c = c;
	StackPush(s1, convert.data);
	convert.data = StackPeek(s1);
    printf("%c\n",convert.c);
/******************************************************************************/	
	convert.str = str;
	StackPush(s1, convert.data);
	convert.data = StackPeek(s1);
    printf("%s\n",convert.str);
/******************************************************************************/	
	
	printf("Stack IS Full before popping  : %d\n", StackIsFull(s1));
	printf("Stack size before popping     : %lu\n", StackSize(s1));
	printf("Stack capacity before popping : %lu\n", StackCapacity(s1));
	puts("Pop");
	StackPop(s1);
	puts("Pop");
	StackPop(s1);
	printf("Stack IS Full after popping   : %d\n", StackIsFull(s1));
	printf("Stack size after popping      : %lu\n", StackSize(s1));
	printf("Stack capacity before popping : %lu\n", StackCapacity(s1));
	convert.data = StackPeek(s1);
	puts("Peek");
    printf("%f\n",convert.d);
    
    StackDestroy(s1);
	puts("stack is destroyed");
	
	puts("Peek - supposed to cause core dump");
	
   /* convert.data = StackPeek(s1);*/
    
    StackTest(10,'z',3.1459);
    
	
	return 0;
}

void StackTest(int a, char b, float c)
{
    stack_t *stack = StackCreate(a);
    int i = 0;
    printf("total capacity of stack: %lu\n\n",StackCapacity(stack));
    StackPush(stack,(void*)(size_t)a);
    printf("Pushed %d\n",a);
    StackPush(stack,(void*)(size_t)b);
    printf("Pushed %c\n",b);
    StackPush(stack,(void*)(size_t)c);
    printf("Pushed %f\n\n",c);
    
    printf("current size: %lu\n\n",StackSize(stack));
    printf("current top is: %f\n",(float)(size_t)StackPeek(stack));
    StackPop(stack);
    printf("StackPopped\n");
    printf("current size: %lu\n",StackSize(stack));
    printf("current top is: %c\n",(char)(size_t)StackPeek(stack));
    StackPop(stack);
    printf("StackPopped\n");
    printf("current size: %lu\n",StackSize(stack));
    printf("is stack empty?: %d\n",StackIsEmpty(stack));
    StackPop(stack);
    printf("StackPopped\n");
    printf("is stack empty?: %d\n",StackIsEmpty(stack));
    printf("is stack full?: %d\n",StackIsFull(stack));
    for ( ; i < a ; ++i)
    {
        StackPush(stack,(void*)(size_t)a);
    }
    printf("Pushing %d times\n",a);
    printf("is stack full?: %d\n",StackIsFull(stack));
    StackDestroy(stack);
    
}
