/********************************************************************************
 *  FILENAME:  linkedlistexcercises.h  DEVELOPER: Daniel Zaken  TEAM: Blue      *
 *                                                                              *
 *  REVIEWER: -------                                                           *
 *                                                                              *
 *  PURPOSE:  Advanced Excercises for linked list                               *
 *                                                                              *
 *******************************************************************************/

#include <assert.h>
#include <linked_list_exercises.h>



node_t *Intersection( node_t *head1, node_t *head2)
{
	int count1 = 0;
	int count2 = 0;
	node_t *run1 = NULL;
	node_t *run2 = NULL;

	assert(head1);
	assert(head2);

	run1 = head1;
	run2 = head2;

	while( run1->next )
	{
		++count1 ;
		run1 = run1->next;
	}

	while( run2->next )
	{
		++count2 ;
		run2 = run2->next;
	}

	if ( run1 != run2 )return NULL;

	run1 = head1;
	run2 = head2;

	while(count1 > count2)
	{
		run1 = run1->next;
		--count1;
	}
	while(count2 > count1)
	{
		run2 = run2->next;
		--count2;
	}

	while( run1 != run2 )
	{
		run1 = run1->next;
		run2 = run2->next;
	}

	return run1;

}

void IntersectionSeperation( node_t *head1, node_t *head2, node_t * intersection)
{
	assert(head1);
	assert(head2);
	assert(intersection);

	(void)head2;

	while(head1->next != intersection )head1 = head1->next;
	head1->next = NULL;

}

node_t *Flip( node_t *head)
{
	node_t *prev = NULL;
	node_t *cur = head;
	node_t *next = NULL;

	while(cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	head = prev;;

	return head;
}



int HasLoop( const node_t *head)
{
    const node_t *q,*p;
    q = head;
    p = head;
    do
    {
        p = p->next;
        q = q->next;
        if(q != NULL)
        {
            q = q->next;
        }
    }
    while(p && q && p!=q);

    if(p==q)
    {
        return 1;
    }
    return 0;
}


node_t *HasLoop2( const node_t *head)
{
    const node_t *fast,*slow;
    fast = head;
    slow = head;
    do
    {
        slow = slow->next;
        fast = fast->next;
        if(fast != NULL)
        {
            fast = fast->next;
        }
    }
    while(slow && fast && slow != fast);

    if( slow == fast )
    {
        return (node_t*)fast;
    }
    return NULL;
}

void FixLoop(const node_t *head)
{
    node_t *runner = (node_t*)head;
    node_t *in_loop = HasLoop2(head);

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

node_t *NthFromLast(node_t * head, int n)
{
	node_t *runner = NULL;
	int i = 0;
	assert(head);

	runner = head;

	while( i < n && head->next != NULL )
	{
		head = head->next;
		++i;
	}

		while( head->next != NULL )
	{
		head = head->next;
		runner = runner->next;
	}
	return runner;
}
