/****************************************************************************
* FILE: bst.c  Purpose: library for bst data structure
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Roger Farber				STATUS: Approved
*
****************************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*asserts*/

#include "bst.h" /*my current lib*/

#define MAX(a,b) ((a)>(b))?(a):(b)
/****************************************************************************/
/****************************************************************************/
typedef struct bst_node bst_node_t;
static int IsRightChild(const bst_iterator_t target);
static int IsLeftChild(const bst_iterator_t target);
static int HowManyChilds(const bst_iterator_t target);
static size_t GetRootHeight(bst_node_t *root);


typedef enum children
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}children_t;

struct bst_node
{
	void *data;
	bst_node_t *parent;
	bst_node_t *child[NUM_OF_CHILDREN];
};

struct bst
{
	bst_node_t root;
	bst_compare_func_t compare_func;
};
/****************************************************************************/
bst_t *BSTCreate(bst_compare_func_t compare_func)
{
    bst_t *bst = NULL;
    assert(compare_func);

    bst = (bst_t*)malloc(sizeof(bst_t));

    if( NULL == bst )
    {
        return NULL;
    }

    /*The field root in bst manager is represented as dummy*/
    (bst->root).data = (void*)bst;
    (bst->root).parent = NULL;
    (bst->root).child[LEFT] = NULL;
    (bst->root).child[RIGHT] = NULL;

    bst->compare_func = compare_func;

    return bst;
}
/****************************************************************************/
void BSTDestroy(bst_t *tree)
{
    assert(tree);


	while( TRUE != BSTIsEmpty(tree) )
	{
		BSTRemove((void*)(tree->root.child[LEFT]));
	}

	tree->compare_func = NULL;
	free(tree);
	tree = NULL;

}
/****************************************************************************/
bst_iterator_t BSTBegin(const bst_t *tree)
{
    bst_node_t *runner = NULL;
    assert(tree);

    runner = (bst_node_t *)(&(tree->root));

    while(NULL != runner->child[LEFT] )
    {
        runner = runner->child[LEFT];
    }

    return((void*)runner);
}
/****************************************************************************/
bst_iterator_t BSTEnd(const bst_t *tree)
{
    assert(tree);

    return((void*)(&(tree->root)));
}
/****************************************************************************/
bst_iterator_t BSTInsert(bst_t *tree, void *data)
{
    bst_node_t *cur = NULL;
    bst_node_t *next = NULL;
    bst_compare_func_t comparator = NULL;
	children_t dir = LEFT;
    bst_node_t *new_node = NULL;

    assert(tree);

    comparator = tree->compare_func;

    cur = (bst_node_t *)(&(tree->root)); /*dummy*/
    next = cur->child[LEFT]; /*real root*/

    while( NULL != next )
    {
        cur = next;
        if( comparator(data, BSTGetData(cur)) > 0 )
        {
            next = next->child[RIGHT];
            dir = RIGHT;
        }
        else if (comparator(data, BSTGetData(cur)) < 0)
        {
            next = next->child[LEFT];
            dir = LEFT;
        }
		else
		{
			return BSTEnd(tree);
		}
    }

	new_node = (bst_node_t*)malloc(sizeof(bst_node_t));

	if( NULL == new_node )
    {
        return NULL;
    }

    new_node->data = data;
    new_node->child[RIGHT] = NULL;
    new_node->child[LEFT] = NULL;
    cur->child[dir] = new_node;
    new_node->parent = cur;

    return ((void*)new_node);
}
/****************************************************************************/
void BSTRemove(bst_iterator_t target)
{
    bst_node_t *to_remove = NULL;
    bst_node_t *successor = NULL;
	bst_node_t *to_remove_parent = NULL;
	int childs_num = 0;
    assert(target);

	childs_num = HowManyChilds(target);

    to_remove = (bst_node_t*)target;
	to_remove_parent = to_remove->parent;

	if( 2 > childs_num )
	{
		if ( NULL != to_remove->child[RIGHT] )
        {
            successor = to_remove->child[RIGHT];
			successor->parent = to_remove_parent;
        }
        else if ( NULL != to_remove->child[LEFT] )
        {
            successor = to_remove->child[LEFT];
			successor->parent = to_remove_parent;
        }

		if ( TRUE == IsRightChild(to_remove) )
        {
			to_remove_parent->child[RIGHT] = successor;
		}
		else
		{
			to_remove_parent->child[LEFT] = successor;
		}

		free(to_remove);
		to_remove = NULL;
	}
	else /*In case of two childs*/
	{
		successor = BSTNext(target);

		to_remove->data = successor->data;

		BSTRemove((void*)successor);
	}
}
/****************************************************************************/
size_t BSTSize(const bst_t *tree)
{
    bst_node_t *runner = NULL;
    size_t counter = 0;

    assert(tree);

    runner = BSTBegin(tree);

    while( TRUE != BSTIsEqualIterator(runner, BSTEnd(tree)))
    {
		runner = BSTNext(runner);
		++counter;
    }
    return counter;
}
/****************************************************************************/
boolean_t BSTIsEmpty(const bst_t *tree)
{
    assert(tree);

    return( NULL == (tree->root).child[LEFT] );
}
/****************************************************************************/
boolean_t BSTIsEqualIterator(const bst_iterator_t one, const bst_iterator_t other)
{
    assert(one);
    assert(other);

    return( one == other );
}
/****************************************************************************/
bst_iterator_t BSTNext(const bst_iterator_t target)
{
    bst_node_t *runner = NULL;

    assert(target);

    runner = (bst_node_t*)target;

    if( NULL != runner->child[RIGHT]) /*whether there is a right subtree*/
    {
        runner = runner->child[RIGHT];
        while( NULL != runner->child[LEFT] )
        {
            runner = runner->child[LEFT];
        }
    }
    else /*if no then we are looking for ancestors*/
    {
        while( IsRightChild(runner) )
        {
            runner = runner->parent;
        }
        runner = runner->parent;
    }
    /*if we try to get next for the max value then
    we will get the dummy this way by going back
    on the tree to the ancestors.
    */
    return (void*)runner;
}
/****************************************************************************/
bst_iterator_t BSTPrev(const bst_iterator_t target)
{
    bst_node_t *runner = NULL;

    assert(target);

    runner = (bst_node_t*)target;

    if( NULL != runner->child[LEFT]) /*whether there is a left subtree*/
    {
        runner = runner->child[LEFT];
        while( NULL != runner->child[RIGHT] )
        {
            runner = runner->child[RIGHT];
        }
    }
    else /*if no then we are looking for ancestors*/
    {
        while( IsLeftChild(runner) && runner->parent->parent != NULL )
        {
            runner = runner->parent;
        }
        runner = runner->parent;
    }
    return (void*)runner;
}
/****************************************************************************/
void *BSTGetData(const bst_iterator_t target)
{
    assert(target);

    return(((bst_node_t*)target)->data);
}
/****************************************************************************/
bst_iterator_t BSTFind(const bst_t *tree, void *data)
{
	bst_node_t *cur = NULL;
    bst_node_t *next = NULL;
    bst_compare_func_t comparator = NULL;

    assert(tree);

    comparator = tree->compare_func;

    cur = (bst_node_t *)(&(tree->root)); /*dummy*/
    next = cur->child[LEFT]; /*real root*/

    while( NULL != next )
    {
        cur = next;
        if( comparator(data, BSTGetData(cur)) > 0 )
        {
            next = next->child[RIGHT];
        }
        else if (comparator(data, BSTGetData(cur)) < 0)
        {
            next = next->child[LEFT];
        }
		else
		{
			return (void*)cur;
		}
    }
	return (void*)(&(tree->root));
}
int BSTForEach(bst_iterator_t from, bst_iterator_t to, bst_operation_func_t callback, void *parameters)
{
	int res = 0;

	assert(from);
	assert(to);
	assert(callback);

	while( SUCCESS == res && FALSE == BSTIsEqualIterator(from, to))
	{
		res = callback( BSTGetData(from), parameters );
		from = BSTNext(from);
	}
	return res;
}
/****************************************************************************/
/****************************************************************************/
static int IsRightChild(const bst_iterator_t target)
{
    assert(target);

    return( ((bst_node_t*)target) == ((bst_node_t*)target)->parent->child[RIGHT] );
}
/****************************************************************************/
static int IsLeftChild(const bst_iterator_t target)
{
    assert(target);

    return( ((bst_node_t*)target) == ((bst_node_t*)target)->parent->child[LEFT] );
}
/****************************************************************************/
static int HowManyChilds(const bst_iterator_t target)
{
	int counter = 2;
    assert(target);

	if( NULL == ((bst_node_t*)target)->child[LEFT] ) --counter;
	if( NULL == ((bst_node_t*)target)->child[RIGHT] ) --counter;

    return counter;
}
int IsPerfect(bst_t *tree)
{
    bst_node_t * root = &(tree->root);

    size_t height = GetRootHeight(root->child[LEFT]);
    size_t size = BSTSize(tree);

    return ( size == (size_t)((1 << (height + 1)) - 1) );
}

static size_t GetRootHeight(bst_node_t *root)
{
    if ( NULL == root )
    {
        return -1;
    }

    return MAX(GetRootHeight(root->child[LEFT]), GetRootHeight(root->child[LEFT])) + 1;
}
/****************************************************************************/
