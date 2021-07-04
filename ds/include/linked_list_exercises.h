/********************************************************************************
 *  FILENAME:  linkedlistexcercises.h  DEVELOPER: Daniel Zaken  TEAM: Blue      *
 *                                                                              *
 *  REVIEWER: -------                                                           *
 *                                                                              *
 *  PURPOSE:  Advanced Excercises for linked list                               *
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_SINGLY_LINKED_LIST_EXCERCISES_H__
#define __ILRD_SINGLY_LINKED_LIST_EXCERCISES_H__
/****************************************************************************/
#include <stddef.h> /*required for size_t type*/
typedef struct Node node_t;

struct Node
{
	int data;
	struct Node *next;
}*first,*second;

int HasLoop( const node_t *head);

node_t *HasLoop2( const node_t *head);

node_t *Flip( node_t *head);

node_t *Intersection( node_t *head1, node_t *head2);

void IntersectionSeperation( node_t *head1, node_t *head2, node_t * intersection);

node_t *NthFromLast(node_t * head, int n);

#endif
