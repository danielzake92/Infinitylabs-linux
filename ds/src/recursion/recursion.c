/****************************************************************************
* FILE: recursion.c  Purpose: library for calculator
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Michael  				STATUS: Impl done
*
****************************************************************************/
#include <assert.h> /*asserts*/

#include "recursion.h" /*our lib*/
#include "utl.h" /*my util*/

static int StrNCmp(const char *str1, const char *str2, size_t n);/*for strstr*/ /*implemented recursively*/
static void StackSortHelper(stack_t *to_sort,void *elem); /*worksheet requierments*/
static void SwapChars(char *a, char *b);
static void RevStringHelper(char *start, char *end);

int Fibonacci(int element_index)
{
    if(element_index <= 1)
    {
        return element_index;
    }
    return (Fibonacci( element_index - 1) + Fibonacci( element_index - 2));
}
/****************************************************************************/
int FibonacciIter( int n )
{
	int a = 0;
	int b = 1;
	int res = 1;

	while(n - 1)
	{
		res = a + b;
		a = b;
		b = res;
		--n;
	}
	return res;
}
/****************************************************************************/
/*
node_t *FlipRec( node_t *head)
{
    node_t *rest = NULL;

    if(head->next == NULL) return head;

    rest = FlipRec(head->next);
    head->next->next = head;
    head->next = NULL;

    return rest;
}
*/



/****************************************************************************/
size_t StrLen(const char *str)
{
    assert(str);

    if( '\0' == *str )
    {
        return 0;
    }
    return StrLen(++str) + 1;
}
/****************************************************************************/
int StrCmp(const char *str1, const char *str2)
{
    assert(str1);
	assert(str2);

    if( '\0' == *str1 || *str1 != *str2 )
    {
        return (*str1 - *str2);
    }
    return StrCmp(++str1, ++str2);
}
/****************************************************************************/
static int StrNCmp(const char *str1, const char *str2, size_t n)
{
    assert(str1);
	assert(str2);

    if( '\0' == *str1 || *str1 != *str2 )
    {
        if (0 == n)return 0;

        return (*str1 - *str2);
    }
    return StrNCmp(++str1, ++str2,--n);
}
/****************************************************************************/
char *StrCpy(char *dest, const char *src)
{
    assert(dest);
    assert(src);

    if( '\0' == *src )
    {
        *dest = '\0';
        return dest;
    }
    *dest = *src;
    StrCpy(dest + 1, src + 1);
    return dest;
}
/****************************************************************************/
char *StrCat(char *dest, const char *src)
{
    char *mid = NULL;
    assert(dest);
	assert(src);

    mid = dest + StrLen(dest);

    if( '\0' == *src )
    {
        *dest = '\0';
        return dest;
    }

    *mid = *src;
    StrCat(mid + 1, ++src);
    return dest;
}
/****************************************************************************/
char *StrStr(const char *haystack, const char *needle)
{
    size_t len = 0;

    assert(haystack);
	assert(needle);

    len = StrLen(needle);

    if( '\0' == *haystack )
    {
        return NULL;
    }

    if ( SUCCESS == StrNCmp(haystack, needle, len) )
    {
        return (char*)haystack;
    }
    return StrStr(haystack + 1, needle);
}
/****************************************************************************/
void StackSort(stack_t *to_sort)
{
    void *elem = NULL;

    assert(to_sort);

    if( StackIsEmpty(to_sort) )
    {
        return;
    }

    elem = StackPeek(to_sort);
    StackPop(to_sort);
    StackSort(to_sort);
    StackSortHelper(to_sort, elem);
}

static void StackSortHelper(stack_t *to_sort,void *elem)
{
    void *top = NULL;
    assert(to_sort);

    if( StackIsEmpty(to_sort) )
    {
        StackPush(to_sort, elem);
        return;
    }

    top = StackPeek(to_sort);

    if( VtoI(elem) <= VtoI(top) )
    {
        StackPush(to_sort,elem);
    }
    else
    {
        StackPop(to_sort);
        StackSortHelper(to_sort, elem);
        StackPush(to_sort,top);
    }
}
#if 0
void SortStackRec(stack_t *stack)
{
    void *temp = NULL;
    if(StackIsEmpty(stack) == 1)
    {
        return ;
    }
    else
    {
        temp = StackPeek(stack);
        StackPop(stack);
        SortStackRec(stack);
        pushSortRec(stack,temp);
    }
}

void pushSortRec(stack_t *stack, void *data)
{
    void *temp = NULL;
    if(StackIsEmpty(stack) || *(int*)StackPeek(stack) <= *(int*)data)
    {
        StackPush(stack, data);
    }
    else
    {
        temp = StackPeek(stack);
        StackPop(stack);
        pushSortRec(stack,data);
        StackPush(stack,temp);
    }
}
#endif
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
int VtoI(void *data)
{
    g_converter.v = data;
    return(g_converter.i);
}
/****************************************************************************/
void *ItoV(int data)
{
	g_converter.i = data;
	return(g_converter.v);
}
/****************************************************************************/
node_t *FlipRec( node_t *head)
{
    node_t *rest = NULL;
    
    if(!head->next) return head;
    rest = FlipRec(head->next);

    head->next->next = head;
    head->next = NULL;
    return rest;
}

void RevString(char *str)
{
    char *start = NULL;
    char *end = NULL;
    assert(str);

    start = str;
    end = str + StrLen(str) - 1;
    RevStringHelper(start, end);
}

static void RevStringHelper(char *start, char *end)
{
    if(start < end )
    {
        SwapChars(start, end);
        RevStringHelper(start + 1, end - 1);
    }
}

static void SwapChars(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}