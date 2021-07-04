#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "utl.h"

int Parentheses(char *string);

int main()
{
	char str1[] = "[()](){[()]()}";
	char str2[] = "[{}(])";
	
	
	printf(GREEN"checking str1 - %s the ans is - %d \n",str1, Parentheses(str1));
	printf(GREEN"checking str2 - %s the ans is - %d \n",str2, Parentheses(str2));
	

	
	return 0;
}


int Parentheses(char *str)
{
	stack_t *stack = NULL;
	
	assert(str);
	
	stack = StackCreate(30);
	
	while(*str)
	{
		
		if(*str == '[' || *str == '(' || *str == '{' ) StackPush(stack, str);
	
		else if( *((char*)StackPeek(stack)) == '[' && *str == ']'  )
		{
			StackPop(stack);
		}
		else if( *((char*)StackPeek(stack)) == '(' && *str == ')'  )
		{
			StackPop(stack);
		}
		else if( *((char*)StackPeek(stack)) == '{' && *str == '}'  )
		{
			StackPop(stack);
		}
		else return 0;		
		++str;
	}
	
	if(StackIsEmpty(stack))
	{
		StackDestroy(stack);
		return 1;
	}
	
	StackDestroy(stack);
	return 0;
}



