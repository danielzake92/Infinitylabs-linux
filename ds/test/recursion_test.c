#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "recursion.h"
#include "utl.h"

#define SIZE1 10
#define SIZE2 5


static void TestFibonacci(void);
static void TestSll(void);
static void TestStackSort(void);
static void TestStrings(void);
static void TestRevStrings(void);


void StrLenTest (char *str);
void StrCmpTest (char *s1, char *s2);

static node_t *CreateLinkedList(int *arr, int size);
static void DestroyLinkedList(node_t *head);
static void PrintLinkedList(node_t *head);
static node_t *Insert(node_t *node, int data);

int main()
{
	printf ("%s*****************************************\n",WHITE);
	printf ("%s---------------Recursion tests---------------\n",WHITE);
	printf ("%s*****************************************\n",WHITE);

	TestFibonacci();
	TestSll();
	TestStackSort();
	TestStrings();
	TestRevStrings();

	printf ("%s*****************************************\n",WHITE);
	printf ("%s---------------Recursion ended----------------\n",WHITE);
	printf ("%s*****************************************\n",WHITE);

	return 0;
}
/****************************************************************************/
static void TestFibonacci(void)
{
	int index = 15;
	printf("Rec - Fibonacci Index = %d Fibonacci num = %d\n", index, Fibonacci(index));
	printf("Iter - Fibonacci Index = %d Fibonacci num = %d\n", index, FibonacciIter(index));
}
/****************************************************************************/
static void TestSll(void)
{
    int arr1[SIZE1] = {1,2,3,4,5,6,7,8,9,10};
    node_t *head1 = CreateLinkedList(arr1, SIZE1);
/****************************************************************************/
	printf(YELLOW"List 1\n"GREEN);
	PrintLinkedList(head1);
	puts(DEFAULT);
/****************************************************************************/
	printf(YELLOW"FlipRec List 1\n"GREEN);
	head1 = FlipRec(head1);
	PrintLinkedList(head1);
	puts(DEFAULT);
/****************************************************************************/
	printf(YELLOW"FlipRec List 1 again\n"GREEN);
	head1 = FlipRec(head1);
	PrintLinkedList(head1);
	puts(DEFAULT);

	DestroyLinkedList(head1);
}
/****************************************************************************/
static void TestStackSort()
{
	int i = 0;
	int arr[SIZE2] = {6, 4, 1, 9, 7};
	stack_t *s1 = StackCreate(SIZE2);

	for(i = 0; i < SIZE2 ; ++i)
	{
		printf("%d ", arr[i] );
		StackPush(s1, ItoV(arr[i]));
	}

	puts("");

	StackSort(s1);

	for(i = 0; i < SIZE2 ; ++i)
	{
		printf("%d ", VtoI(StackPeek(s1)) );
		StackPop(s1);
	}
	puts("");

	StackDestroy(s1);
}

static void TestStrings(void)
{
	char dest1[25];
	char dest2[25];
	/*strcat strings*/
	char start1 [25] = "hello";
	char start2 [25] = "hello";
	char *end = "world 1234";

	/*StrStr strings*/
	char *ret1 = NULL;
	char *ret2 = NULL;

	StrLenTest("hello");
	StrCmpTest("hello", "hello");
	StrCmpTest("helloff", "hello");


	/*STRCPY TESTS*/
	printf ("\033[34;1m STRCPY\033[0m ");
	printf(" origin -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	strcpy(dest1, "hell"), StrCpy(dest1, "hell"));

	printf ("\033[34;1m STRCPY\033[0m ");
	printf(" origin -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	strcpy(dest2, "hell boy"), StrCpy(dest2, "hell boy"));
	puts("");


	/*STRCAT TESTS*/
	printf ("\033[34;1m STRCAT\033[0m ");/*blue msg*/
	printf("origin -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	strcat(start1, end), StrCat(start2, end));
	puts("");

	/*STRSTR TESTS*/
	ret1 = StrStr("abimbambom", "bam");
	ret2 = strstr("abimbambom", "bam");
	printf ("\033[34;1m STRSTR\033[0m ");
	printf("source -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	ret2, ret1);


}

static void TestRevStrings()
{
	char str1[] = "daniel";
	char str2[] = "d";
	char str3[] = "fg";
	char str4[] = "oddss";

	RevString(str1);
	printf("%s\n",str1 );
	RevString(str2);
	printf("%s\n",str2 );
	RevString(str3);
	printf("%s\n",str3 );
	RevString(str4);
	printf("%s\n",str4 );

}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
node_t *CreateLinkedList(int *arr, int size)
{
    node_t *start = NULL;
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if (NULL == head)
    {
        return NULL;
    }

    start = head;
    head->data = *arr;
    head->next = NULL;
    ++arr;
    --size;

    while (size)
    {
        head = Insert(head, *arr);
        ++arr;
        --size;
    }

    return start;
}
/****************************************************************************/
void DestroyLinkedList(node_t *head)
{
    node_t *prev = NULL;
    node_t *curr = NULL;

    curr = head;
    prev = curr;
    while (curr)
    {
        curr = curr->next;
        free(prev);
        prev = NULL;
        prev = curr;
    }
}
/****************************************************************************/
void PrintLinkedList(node_t *head)
{
    while (head)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
/****************************************************************************/
node_t *Insert(node_t *node, int data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (NULL == new_node)
    {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    node->next = new_node;

    return new_node;
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void StrLenTest (char *str)
{
	int origin = strlen(str), my_imp = StrLen(str);

	printf (BLUE"STRLEN\n"DEFAULT);/*blue msg*/

	if (origin == my_imp)
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[32;1m OK \033[0m\n");/*grn msg*/
	}
	else
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[31;1m NOT OK \033[0m\n");/*red msg*/
	}
}

void StrCmpTest (char *s1, char *s2)
{
	int origin = strcmp(s1,s2), my_imp = StrCmp(s1,s2);

	printf ("\033[34;1m STRCMP \033[0m ");

	if (origin == my_imp || origin*my_imp >= 0 )
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[32;1m OK \033[0m\n");
	}
	else
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[31;1m NOT OK \033[0m\n");
	}
}
