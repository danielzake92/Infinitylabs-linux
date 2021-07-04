#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "utl.h"

typedef struct bst_node node_t;

static int Compare(const void *lhs,const void *rhs);

static void PrintInOrder(const bst_t *tree);

static void PrintInReverseOrder(const bst_t *tree);

static int PlusNum(void *target, void *parameters);


int main()
{
	size_t i = 0;
/*
	int to_insert = 9;
	int val = 5;
	bst_iterator_t to_remove = NULL;
*/
	bst_iterator_t iter = NULL;
	bst_iterator_t root = NULL;
	int arr[24] = {25, 20, 10, 5, 1, 8, 12, 15, 36, 30, 28, 40, 38, 39, 37, 48, 45, 50, 35, 34, 60, 70, -2, -10};
	size_t size = 24;

	int arr2[15] = {15, 10, 20, 5, 13, 17, 25, 3, 7, 11, 14, 16, 19, 23, 28};
	size_t size2 = 15;

	bst_t *tree = NULL;
	int to_find = 0;
	int for_each_plus = 1;


	printf ("%s*****************************************\n",WHITE);
	printf ("%s---------------BST tests---------------\n",WHITE);
	printf ("%s*****************************************\n",WHITE);
/****************************************************************************/
	printf(GREEN"BSTCreate - Should be empty\n"DEFAULT);
	tree = BSTCreate(Compare);
	printf(YELLOW"Is Empty = "BLUE"%d"YELLOW", BSTSize = "BLUE"%lu\n"DEFAULT,BSTIsEmpty(tree),BSTSize(tree) );
	puts("");
/****************************************************************************/
	printf(GREEN"BST pushing 19 elemnts - should be printed in-order and reversed order\n"DEFAULT);
	for(i = 0;i < size ;++i)
	{
		BSTInsert(tree, &arr[i]);
	}
	printf(YELLOW"Print in order -> "DEFAULT);
	PrintInOrder(tree);
	printf(YELLOW"Print in reverse order -> "DEFAULT);
	PrintInReverseOrder(tree);
	printf(YELLOW"Is Empty = "BLUE"%d"YELLOW", BSTSize = "BLUE"%lu\n"DEFAULT,BSTIsEmpty(tree),BSTSize(tree) );
	puts("");
/****************************************************************************/

	printf(GREEN"BSTForEach - plus %d\n"DEFAULT, for_each_plus);
	BSTForEach(BSTBegin(tree), BSTEnd(tree), PlusNum, (void *)(size_t)for_each_plus);

	printf(YELLOW"Print in order -> "DEFAULT);
	PrintInOrder(tree);
	puts("");

/****************************************************************************/
	printf(GREEN"Find and remove root\n"DEFAULT);
	to_find = 25 + for_each_plus;
	root = BSTFind(tree, (void*)(&to_find));
	printf(YELLOW"Root is = "BLUE"%d\n"DEFAULT, *((int *)BSTGetData(root)));
	BSTRemove(root);
	printf(YELLOW"Print in order -> "DEFAULT);
	PrintInOrder(tree);
	printf(YELLOW"Is Empty = "BLUE"%d"YELLOW", BSTSize = "BLUE"%lu\n"DEFAULT,BSTIsEmpty(tree),BSTSize(tree) );
	puts("");

/****************************************************************************/
	printf(GREEN"Find and remove begin and last valid member\n"DEFAULT);

	iter = BSTBegin(tree);
	printf(YELLOW"Begin is = "BLUE"%d\n"DEFAULT, *((int *)BSTGetData(iter)));
	BSTRemove(iter);

	iter = BSTPrev(BSTEnd(tree));
	printf(YELLOW"Last valid member is = "BLUE"%d\n"DEFAULT, *((int *)BSTGetData(iter)));
	BSTRemove(iter);

	printf(YELLOW"Print in order -> "DEFAULT);
	PrintInOrder(tree);

	printf(YELLOW"Is Empty = "BLUE"%d"YELLOW", BSTSize = "BLUE"%lu\n"DEFAULT,BSTIsEmpty(tree),BSTSize(tree) );
	puts("");
/****************************************************************************/
	printf(GREEN"Find and remove three certian places\n"DEFAULT);

	to_find = 1 + for_each_plus;
	iter = BSTFind(tree, (void*)(&to_find));
	printf(YELLOW"first is = "BLUE"%d\n"DEFAULT, *((int *)BSTGetData(iter)));
	BSTRemove(iter);

	to_find = 50 + for_each_plus;
	iter = BSTFind(tree, (void*)(&to_find));
	printf(YELLOW"second is = "BLUE"%d\n"DEFAULT, *((int *)BSTGetData(iter)));
	BSTRemove(iter);

	to_find = 34 + for_each_plus;
	iter = BSTFind(tree, (void*)(&to_find));
	printf(YELLOW"third is = "BLUE"%d\n"DEFAULT, *((int *)BSTGetData(iter)));
	BSTRemove(iter);

	printf(YELLOW"Print in order -> "DEFAULT);
	PrintInOrder(tree);

	printf(YELLOW"Is Empty = "BLUE"%d"YELLOW", BSTSize = "BLUE"%lu\n"DEFAULT,BSTIsEmpty(tree),BSTSize(tree) );
	puts("");

	BSTDestroy(tree);

	tree = BSTCreate(Compare);

	for(i = 0;i < size2 ;++i)
	{
		BSTInsert(tree, &arr2[i]);
	}

	printf("is tree perfert : %d\n",IsPerfect(tree));

	BSTDestroy(tree);


	printf ("%s*****************************************\n",WHITE);
	printf ("%s---------------Test ended----------------\n",WHITE);
	printf ("%s*****************************************\n",WHITE);

	return 0;
}



int Compare(const void *lhs,const void *rhs)
{
	return (*((int *)(lhs)) - *((int *)(rhs)));
}

void PrintInOrder(const bst_t *tree)
{
	bst_iterator_t iter = BSTBegin(tree);
	bst_iterator_t end = BSTEnd(tree);

	while (!BSTIsEqualIterator(end, iter))
	{
		printf(BLUE"%d "DEFAULT, *((int *)BSTGetData(iter)));
		iter = BSTNext(iter);
	}
	puts("");
}

void PrintInReverseOrder(const bst_t *tree)
{
	bst_iterator_t iter = BSTBegin(tree);
	bst_iterator_t end = BSTEnd(tree);

	while (!BSTIsEqualIterator(end, BSTNext(iter)))
	{
		iter = BSTNext(iter);
	}

	while (!BSTIsEqualIterator(end, iter))
	{
		printf(BLUE"%d "DEFAULT, *((int *)BSTGetData(iter)));
		iter = BSTPrev(iter);
	}
	puts("");
}

static int PlusNum(void *target, void *parameters)
{
	*((int *)target) += (size_t)parameters;
	return SUCCESS;
}



