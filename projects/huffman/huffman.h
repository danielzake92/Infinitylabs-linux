/****************************************************************************
* FILE: avl.h		Purpose: library for avl data structure
*
* DEVELOPER:						TEAM:
*
* REVIEWER: 						STATUS: In Development
*
****************************************************************************/

#ifndef __ILRD_HUFFMAN_H__
#define __ILRD_HUFFMAN_H__

/****************************************************************************/

#include <stddef.h> /*size_t*/
#include <limits.h> 
#include "priority_queue.h" 
/****************************************************************************/
/**********************************************SOURCE FILE***********************/


/*****************************************************************************/

#define ASCII 256
#define NUM_CHARS 2
#define NUM_ARGS 3
#define HISTOGRAM_SIZE (ASCII) * (sizeof(size_t))

typedef enum h_status
{
	SUCCESS = 0,
	ERR_RMV = -1,
	ERR_OPEN = -2,
	ERR_CLOSE = -3,
	ERR_RENAME = -4,
	ERR_FPUTS = -5,
	ERR_UNKNOWN = -6,
	EXIT = -9,
	NONE = -10
}h_status_t;

typedef struct h_node h_node_t;
typedef int(*h_cmp_t)(const void *lhs, const void *rhs);

struct h_node
{
	h_node_t *parent;
	h_node_t *left;
	h_node_t *right;

	size_t freq;
	char val;
};


h_status_t ParseToHistogram(const char *f_name);
p_queue_t *HistogramToPQ(h_status_t *status);
h_node_t *PQToTree(p_queue_t *pq, h_status_t *status);
static int IsLeftChild(const h_node_t *target);
h_status_t Statistics(const char *f_name, size_t *curr_size, size_t *compressed_size);

#endif

