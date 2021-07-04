/********************************************************************************
 *  FILENAME:  ds_exam.h  DEVELOPER: Daniel Zaken   TEAM: Greem
 *
 *  Reviwer:
 *
 *  PURPOSE:   Ds test functions
 *
 *******************************************************************************/
#ifndef __ILRD_DS_EXAM_H__
#define __ILRD_DS_EXAM_H__

#include <stddef.h> /*required for size_t type*/
#define Q_SIZE 8
#define SIZE 9
typedef struct node node_t;
typedef struct queue q_t;

struct queue
{
    char m_queue[Q_SIZE];
    size_t m_elements_in_q;
    size_t m_first_element;
};

struct node
{
    int data;
    node_t *next;
};


node_t *Flip( node_t *head);
node_t *HasLoop( const node_t *head);
void LoopOpener(const node_t *head);
node_t *Intersection( node_t *head1, node_t *head2);
void IntersectionSeperation(node_t *head1, node_t *head2);
void SllRemove( node_t *to_remove);

int WhoIsMissing(int *arr, int max_num);
int PushChar(q_t *queue, char c);
char PopChar(q_t *queue);

int IsInShape(int matrix[][SIZE], int row, int col, int x, int y);

#endif
