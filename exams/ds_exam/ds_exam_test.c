#include <stdio.h>
#include <stdlib.h> /*Required for malloc*/
#include "ds_exam.h" /*exam lib*/
#include "../../ds/include/utl.h" /*utl for colors and etc*/
/****************************************************************************/
#define SIZE1 10


static node_t *CreateLinkedList(int *arr, int size);
static void DestroyLinkedList(node_t *head);
static void PrintLinkedList(node_t *head);
static node_t *Insert(node_t *node, int data);

static q_t *QueueCreate(void);
static void QueueDestroy(q_t *queue);
static void PrintQueue(q_t *queue);

void SllTest(void);
void OtherTest(void);
void QueueTest(void);
void MatrixTest(void);

static void CreateMatrix1(int arr[SIZE][SIZE]);
static void CreateMatrix2(int arr[SIZE][SIZE]);
static void PrintMatrix(int arr[SIZE][SIZE], int row, int col);

/****************************************************************************/
/****************************************************************************/
int main()
{
	printf ("%s*****************************************\n",PURPLE);
	printf ("%s---------------Ds_Exam tests-------------\n",PURPLE);
	printf ("%s*****************************************\n",PURPLE);
	printf(DEFAULT);
	SllTest();
	OtherTest();
	QueueTest();
	MatrixTest();
	printf ("%s*****************************************\n",PURPLE);
	printf ("%s---------------Test ended----------------\n",PURPLE);
	printf ("%s*****************************************\n",PURPLE);
	return 0;
}
/****************************************************************************/
/****************************************************************************/


void SllTest(void)
{
    int arr1[SIZE1] = {1,2,3,4,5,6,7,8,9,10};
	int arr2[SIZE1] = {11,12,13,14,15,16,17,18,19,20};
    node_t *head1 = CreateLinkedList(arr1, SIZE1);
	node_t *head2 = CreateLinkedList(arr2, SIZE1);
/****************************************************************************/
	printf(YELLOW"List 1\n"GREEN);
	PrintLinkedList(head1);
	printf(YELLOW"List 2\n"GREEN);
	PrintLinkedList(head2);
	puts(DEFAULT);
/****************************************************************************/
	printf(YELLOW"Remove 3 from list 1\n"GREEN);
	SllRemove(head1->next->next);
	PrintLinkedList(head1);
	puts(DEFAULT);
/****************************************************************************/
	printf(YELLOW"Flip List 1\n"GREEN);
	head1 = Flip(head1);
	PrintLinkedList(head1);
	puts(DEFAULT);
/****************************************************************************/
	printf(YELLOW"Flip List 1 again\n"GREEN);
	head1 = Flip(head1);
	PrintLinkedList(head1);
	puts(DEFAULT);
/****************************************************************************/
	printf(YELLOW"List 1 intersects with list 2\n"GREEN);
	head1->next->next->next->next->next->next->next->next->next = head2->next->next->next->next;
	PrintLinkedList(head1);
	puts(DEFAULT);
/****************************************************************************/
	printf(YELLOW"List 1 and 2 after intersection seperation\n"GREEN);
	IntersectionSeperation(head1,head2);
	PrintLinkedList(head1);
	PrintLinkedList(head2);
/****************************************************************************/
	printf(YELLOW"List 1 with looping it and opening it\n"GREEN);
	head1->next->next->next->next->next->next->next->next->next = head1->next->next->next->next;
	LoopOpener(head1);
	PrintLinkedList(head1);
	puts(DEFAULT);
/****************************************************************************/
	DestroyLinkedList(head1);
	DestroyLinkedList(head2);
}


void OtherTest(void)
{
	int arr[24] = {0};
	int i = 0;
	int j = 0;

	for( i = 0; i < 12 ; ++i, ++j)
	{
		arr[i] = j;
	}
	++j;
	for( ; i < 24 ; ++i, ++j)
	{
		arr[i] = j;
	}

	for( i = 0; i < 24 ; ++i)
	{
		printf("%d ", arr[i]);
	}


	printf(YELLOW"\nWhoIsMissing = "GREEN"%d \n"DEFAULT, WhoIsMissing(arr, 24));

	puts(DEFAULT);
}

void QueueTest(void)
{
	q_t *q = QueueCreate();
	PushChar(q, 'M');
	PushChar(q, 'y');
	PushChar(q, 'n');
	PushChar(q, 'a');
	PushChar(q, 'm');
	PushChar(q, 'e');
	PushChar(q, 'i');
	PushChar(q, 's');

	PrintQueue(q);
	puts("");

	PopChar(q);
	PopChar(q);
	PopChar(q);
	PopChar(q);

	PrintQueue(q);
	puts("");

	PushChar(q, '*');
	PushChar(q, '*');
	PushChar(q, '*');
	PushChar(q, '*');

	PrintQueue(q);
	puts("");

	QueueDestroy(q);
}

void MatrixTest(void)
{
	int matrix[SIZE][SIZE] = {0};

	CreateMatrix1(matrix);

	printf("\nprint matrix %d X %d\n\n", SIZE, SIZE);
	PrintMatrix(matrix,0,3);
	printf("IsInShape = %d\n",IsInShape(matrix, SIZE, SIZE, 0, 3));

	printf("\nprint matrix %d X %d\n\n", SIZE, SIZE);
	PrintMatrix(matrix,3,3);
	printf("IsInShape = %d\n",IsInShape(matrix, SIZE, SIZE, 3, 3));
/****************************************************************************/

	CreateMatrix2(matrix);
	printf("\nprint matrix %d X %d\n\n", SIZE, SIZE);
	PrintMatrix(matrix,5,3);
	printf("IsInShape = %d\n",IsInShape(matrix, SIZE, SIZE, 5, 3));

	printf("\nprint matrix %d X %d\n\n", SIZE, SIZE);
	PrintMatrix(matrix,5,8);
	printf("IsInShape = %d\n",IsInShape(matrix, SIZE, SIZE, 5, 8));

	printf("\nprint matrix %d X %d\n\n", SIZE, SIZE);
	PrintMatrix(matrix,8,0);
	printf("IsInShape = %d\n",IsInShape(matrix, SIZE, SIZE, 8, 0));

	printf("\nprint matrix %d X %d\n\n", SIZE, SIZE);
	PrintMatrix(matrix,0,7);
	printf("IsInShape = %d\n",IsInShape(matrix, SIZE, SIZE, 0, 7));

	printf("\nprint matrix %d X %d\n\n", SIZE, SIZE);
	PrintMatrix(matrix,7,2);
	printf("IsInShape = %d\n",IsInShape(matrix, SIZE, SIZE, 7, 2));

}

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

static q_t *QueueCreate()
{
	q_t *queue = (q_t*)malloc(sizeof(q_t));

	if( NULL == queue)
	{
		return NULL;
	}

	queue->m_elements_in_q = 0;
	queue->m_first_element = 0;

	return queue;
}

static void QueueDestroy(q_t *queue)
{
	free(queue);
}

static void PrintQueue(q_t *queue)
{
	int first = queue->m_first_element;
	int ele_num = queue->m_elements_in_q;
	int i = 0;

	for( i = first; i < ele_num; ++i)
	{
		printf("%c", (queue->m_queue)[i]);
	}

}

static void CreateMatrix1(int arr[SIZE][SIZE])
{
	int i = 0;
	int j = 0;

	for(i = 0; i < SIZE; ++i)
	{
		for(j = 0; j < SIZE; ++j)
		{
			arr[i][j] = 0;
		}
	}

	arr[1][2] = 1;
	arr[1][3] = 1;
	arr[1][4] = 1;

	arr[2][1] = 1;
	arr[2][5] = 1;

	arr[3][1] = 1;
	arr[3][5] = 1;

	arr[4][1] = 1;
	arr[4][5] = 1;

	arr[5][2] = 1;
	arr[5][3] = 1;
	arr[5][4] = 1;

}

static void CreateMatrix2(int arr[SIZE][SIZE])
{
	int i = 0;
	int j = 0;

	for(i = 0; i < SIZE; ++i)
	{
		for(j = 0; j < SIZE; ++j)
		{
			arr[i][j] = 0;
		}
	}
	arr[6][0] = 1;
	arr[7][1] = 1;
	arr[8][2] = 1;
	arr[7][3] = 1;
	arr[6][4] = 1;
	arr[7][5] = 1;
	arr[8][6] = 1;
	arr[7][7] = 1;
	arr[6][8] = 1;

	arr[5][7] = 1;
  arr[5][6] = 1;
	arr[4][5] = 1;
  arr[4][4] = 1;

	arr[3][3] = 1;
	arr[3][2] = 1;

	arr[2][2] = 1;

	arr[2][3] = 1;
	arr[2][4] = 1;
	arr[2][5] = 1;
	arr[2][6] = 1;
	arr[2][7] = 1;

	arr[1][7] = 1;
	arr[0][6] = 1;
	arr[0][5] = 1;
	arr[0][4] = 1;
	arr[0][3] = 1;
	arr[0][2] = 1;
	arr[0][1] = 1;
	arr[0][0] = 1;

	arr[1][0] = 1;
	arr[2][0] = 1;
	arr[3][0] = 1;
	arr[4][0] = 1;
	arr[5][0] = 1;






}

static void PrintMatrix(int arr[SIZE][SIZE], int row, int col)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < SIZE; ++i)
	{
		for(j = 0; j < SIZE; ++j)
		{
			if( i == row && j == col )
			{
				printf(RED"%d   "DEFAULT,arr[i][j]);
				continue;
			}
			if( arr[i][j] == 1 )
			{
				printf(GREEN"%d   "DEFAULT,arr[i][j]);
			}
			else
			{
				printf("%d   ",arr[i][j]);
			}
		}
		puts("\n");
	}
}
