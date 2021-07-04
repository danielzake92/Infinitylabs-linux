/********************************************************************************
 *  FILENAME:  ds_exam.c  DEVELOPER: Daniel Zaken   TEAM: Green
 *
 *  Reviwer:
 *
 *  PURPOSE:   Ds test functions
 *
 *******************************************************************************/
#include <assert.h>/*For assertion*/
#include <stdlib.h>/*for calloc*/
#include "ds_exam.h"/*Our sorts lib*/
#include "../../ds/include/utl.h"


node_t *Flip( node_t *head)
{
	node_t *prev = NULL;
	node_t *cur = head;
	node_t *next = NULL;

	while( NULL != cur )
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	return prev;
}

node_t *HasLoop( const node_t *head)
{
    node_t *fast,*slow;
    fast = (node_t*)head;
    slow = (node_t*)head;
    do
    {
        slow = slow->next;
        fast = fast->next;
        if(fast != NULL)
        {
            fast = fast->next;
        }
    }while(slow && fast && slow != fast);

    if( slow == fast )
    {
        return (node_t*)fast;
    }
    return NULL;
}


void LoopOpener(const node_t *head)
{
    node_t *runner = (node_t*)head;
    node_t *in_loop = HasLoop(head);

    if( NULL == in_loop )
    {
        return;
    }

    while( runner->next != in_loop->next )
    {
        runner = runner->next;
        in_loop = in_loop->next;
    }
    in_loop->next = NULL;
}


node_t *Intersection( node_t *head1, node_t *head2)
{
	int count1 = 0, count2 = 0;

	node_t *run1 = head1, *run2 = head2;

	while( NULL != run1->next ) {++count1 ; run1 = run1->next;}
    while( NULL != run2->next ) {++count2 ; run2 = run2->next;}

	if ( run1 != run2 )return NULL;

	run1 = head1; run2 = head2;

	while(count1 > count2) {run1 = run1->next; --count1;}
    while(count2 > count1) {run2 = run2->next; --count2;}

	while( run1->next != run2->next )
	{
		run1 = run1->next;
		run2 = run2->next;
	}

	return run1;

}

void IntersectionSeperation(node_t *head1, node_t *head2)
{
    node_t * before_intersect = Intersection(head1, head2);

	/*The if i forgot to put int the test*/
	if ( NULL != before_intersect)
	{
		before_intersect->next = NULL;
	}
	/*before_intersect = NULL;*/  /*a mistake line becuase i forgot im geting one node before
	intersection */
}

void SllRemove( node_t *to_remove)
{
    node_t *next = to_remove->next;

    if( NULL == next )return;

    to_remove->data = next->data;
    to_remove->next = next->next; /*the correct line*/

    /*next->next = NULL; a mistake */

    next->next = NULL;

    free(next);
}

int WhoIsMissing(int *arr, int max_num)
{
	int math_sum = (( 1 + max_num ) * max_num) / 2;
	int sum = 0;
	int offset = 0;
	int i = 0;

	for( i = 0; i < max_num; ++i)
	{
		sum += arr[i];
	}
	offset = math_sum - sum;

	return offset;
}

int PushChar(q_t *queue, char c)
{
	size_t i = 0;
	size_t ele_num = queue->m_elements_in_q;
	size_t first_ele = queue->m_first_element;

	if( ele_num == Q_SIZE )return FAIL;

	if( ele_num + first_ele < Q_SIZE )
	{
		(queue->m_queue)[ele_num + first_ele] = c;
	}
	else
	{
		while( queue->m_first_element )
		{
			(queue->m_queue)[i] = (queue->m_queue)[first_ele + i];
			--queue->m_first_element;
			++i;/*missing line*/
		}
		(queue->m_queue)[ele_num] = c;
	}
	++queue->m_elements_in_q;
	return SUCCESS;
}
char PopChar(q_t *queue)
{
	char temp = (queue->m_queue)[queue->m_first_element];
	++(queue->m_first_element);
	--(queue->m_elements_in_q);
	return temp;
}

int IsInShape(int matrix[][SIZE], int row, int col, int x, int y)
{
	int count_ones = 0;
	(void)row;
	while( y < col - 1 )
	{
		if(matrix[x][y] - matrix[x][y + 1] == -1)
		{
			++count_ones;
		}
		++y;
	}
	return (count_ones % 2);
}
