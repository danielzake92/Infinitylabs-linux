#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <limits.h> 
#include "huffman.h"
#include "priority_queue.h" 

static size_t histogram[ASCII] = {0};
static h_node_t *g_coding[ASCII] = {NULL};
static char g_path[ASCII] = {0};
static char g_depth[ASCII] = {0};

int main(int argc, char *argv[])
{
	size_t cur_size = 0;
	size_t compressed_size = 0;
	if( NUM_ARGS > argc )
	{
		puts("Not enough args");
		return 0;
	}
		
	if( NUM_CHARS != strlen(argv[1]) )
	{
		puts("Syntax err");
		return 0;
	}

	Statistics(argv[2], &cur_size, &compressed_size);

	printf("cur_size = %lu\ncompressed_size = %lu\n", cur_size, compressed_size);

	/*ParseToHistogram(argv[2]);*/

	switch( strcmp(argv[1],"-a") ) 
	{
		case ('s' - 'a'):
			puts("-s");
			/* statistics func */
			break;
		case ('c' - 'a'):
			puts("-c");
			/* compress func */
			break;
		case ('d' - 'a'):
			puts("-d");
			/* decompress func */
			break;
		default:
			puts("syntax err");
			break;
	}

	return 0;
}

h_status_t ParseToHistogram(const char *f_name)
{
	FILE *file = NULL;
	h_status_t status = SUCCESS;

	if ( ( file = fopen(f_name, "r") ) == NULL )
	{
		return(ERR_OPEN);
	}

	while( SUCCESS == feof(file) )
	{
		++ histogram[fgetc(file)];
	}

	if( (status = fclose(file) ) != 0)
	{
		return (ERR_CLOSE);
	}  

	return SUCCESS;

}


void CreateDepthAndPath(void)
{
	size_t i = 0;
	h_node_t *iter = NULL;

	for (i = 0; i < ASCII; ++i)
	{
		iter = g_coding[i];

		if (iter)
		{
			char mask = 1;
			char num = 0;
			while (iter->parent)
			{
				if (IsLeftChild(iter))
				{
					num |= mask;
				}
				++g_depth[i];
				g_path[i] = num;
				
				iter = iter->parent;
				mask <<= 1;
			}
		}
	}
}

static int IsLeftChild(const h_node_t *target)
{
    assert(target);

    return( ((h_node_t*)target) == ((h_node_t*)target)->parent->left );
}


h_status_t Statistics(const char *f_name, size_t *curr_size, size_t *compressed_size)
{
	h_status_t status = SUCCESS;
	p_queue_t * pq = NULL;
	h_node_t *tree = NULL;

	size_t i = 0;

	assert(curr_size);
	assert(compressed_size);

	*curr_size = 0;
	*compressed_size = 0;

	status = ParseToHistogram(f_name);

	pq = HistogramToPQ(&status);
	tree = PQToTree(pq, &status);
	
	CreateDepthAndPath();

	/* retrieving cur_size  */
	for(i = 0; i < ASCII; ++i)
	{
		*curr_size += histogram[i];
	}

	/* retrieving compressed_size  */
	for(i = 0; i < ASCII; ++i)
	{
		*compressed_size += (histogram[i] * g_depth[i]);
	}

	*compressed_size = (*compressed_size / CHAR_BIT) + !(*compressed_size % CHAR_BIT);  

	return SUCCESS;

}


/* h_status_t Compress(h_node_t *root, const char *f_name)
{

}
 *//* gd huffman.c huffman.h ../../ds/src/priority_queue/priority_queue.c ../../ds/src/doubly_linked_list/doubly_linked_list.c ../../ds/src/sorted_list/sorted_list.c ../../ds/include/priority_queue.h ../../ds/include/sorted_list.h ../../ds/include/doubly_linked_list.h -I ../../ds/include/ */