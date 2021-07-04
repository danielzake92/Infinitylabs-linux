#ifndef __ILRD_RECURSION_H__
#define __ILRD_RECURSION_H__

#include "stack.h"
typedef struct Node node_t;

struct Node
{
	int data;
	struct Node *next;
};

union converter
{
	void *v;
	int i;
}g_converter;

int VtoI(void *data);
void *ItoV(int data);

int Fibonacci(int element_index);
int FibonacciIter(int n);

node_t *FlipRec( node_t *head);
void StackSort(stack_t *to_sort);

size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *StrCpy(char *src, const char *dest);
char *StrCat(char *src, const char *dest);
char *StrStr(const char *haystack, const char *needle);
void RevString(char *str);


#endif
