/****************************************************************************
* FILE: bst.c  Purpose: library for avl data structure
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Nitzan Holmes  			STATUS: ImpTested
*
****************************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*asserts*/

#include "avl.h" /*my current lib*/
#include "utl.h"

#define TRAVERSE 3
/****************************************************************************
*                     Typedefs
****************************************************************************/
typedef struct avl_node avl_node_t;

typedef int(*traverse_func_t)(avl_node_t *root,avl_operation_func_t callback,
                                                                void *param);


/****************************************************************************
*                     Structs and enums
****************************************************************************/
enum children
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
};

struct avl_node
{
	void *data;
	avl_node_t *child[NUM_OF_CHILDREN];
	size_t height;
};

struct avl
{
	avl_node_t *root;
	avl_compare_func_t compare_func;
};
/****************************************************************************
*                     Traverse functions
****************************************************************************/
static int InOrder(avl_node_t *root, avl_operation_func_t callback, void *param);
static int PreOrder(avl_node_t *root, avl_operation_func_t callback, void *param);
static int PostOrder(avl_node_t *root, avl_operation_func_t callback, void *param);
/****************************************************************************
*                     Helper Functions
****************************************************************************/
/*destroyer*/
static void AVLDestroyHelper(avl_node_t* node);
/*insertion*/
static avl_node_t *AVLInsertHelper(avl_t *tree,avl_node_t *node,avl_node_t *new_node);
/*funder*/
static const void *AVLFindHelper(const avl_t *tree, const avl_node_t *node, const void *data);
/*removers*/
static avl_node_t *AVLFindNodeToRemove(avl_t *tree,avl_node_t *node, void *data);
avl_node_t *FindSuccessor(avl_node_t *node);
/****************************************************************************
*                     Utilities functions
****************************************************************************/
static int AvlNodeCount(void *target, void *parameters);
static void UpdateHeight(avl_node_t *node);
static avl_node_t * CreateNode(void *data);
static int HowManyChilds(const avl_node_t *target);
/****************************************************************************
*                     Rotations and balance functions
****************************************************************************/
static avl_node_t *LeftRotate( avl_node_t *old_root);
static avl_node_t *RightRotate( avl_node_t *old_root);
static avl_node_t *LeftRightRotate( avl_node_t *bad_node);
static avl_node_t *RightLeftRotate( avl_node_t *bad_node);

static int BalanceFactor( avl_node_t *node);
static avl_node_t *NodeBalancing(avl_node_t *bad_node);

static traverse_func_t g_traverse_lut[TRAVERSE] = {InOrder, PreOrder, PostOrder};
/****************************************************************************
*                     IMplementations
****************************************************************************/
avl_t *AVLCreate(avl_compare_func_t compare_func)
{
    avl_t *avl = NULL;

    assert(compare_func);

    avl = (avl_t*)malloc(sizeof(avl_t));
    if( NULL == avl )
    {
        return NULL;
    }

    avl->compare_func = compare_func;
    avl->root = NULL;

    return avl;
}
/****************************************************************************/
int AVLInsert(avl_t *tree, void *data)
{
    avl_node_t *new_node = NULL;

    assert(tree);

    new_node = CreateNode(data);
    if(NULL == new_node)return FAIL;

    tree->root = AVLInsertHelper(tree, tree->root, new_node);

    tree->root = NodeBalancing(tree->root); /*balancing the tree*/
    UpdateHeight(tree->root); /*updating height*/

    return SUCCESS;
}
/****************************************************************************/
static avl_node_t *AVLInsertHelper(avl_t *tree,avl_node_t *node,avl_node_t *new_node)
{
    int res = 0;

    assert(tree);
    assert(tree->compare_func);

    /*case : inserting root as the first node*/
    if( NULL == node )
    {
       return new_node;
    }

    res = tree->compare_func(new_node->data,node->data );

    /*case : for entering duplicate*/
    if ( 0 == res)
    {
        free(new_node);
        return node;
    }
    /*case : for traversing left*/
    if(0 > res )
    {
       node->child[LEFT] = AVLInsertHelper(tree,node->child[LEFT], new_node);
    }
    /*case : for trasversing right*/
    else if(0 < res)
    {
        node->child[RIGHT] = AVLInsertHelper(tree,node->child[RIGHT], new_node);
    }
    /*balncing tree & updating height*/
    node = NodeBalancing(node);
    UpdateHeight(node);

    return node;
}
/****************************************************************************/
/****************************************************************************/
void AVLRemove(avl_t *tree, void *data)
{
    assert(tree);
    tree->root = AVLFindNodeToRemove(tree,tree->root, data);
}
/****************************************************************************/
static avl_node_t *AVLFindNodeToRemove(avl_t *tree,avl_node_t *node, void *data)
{
    avl_node_t *successor = NULL;
    avl_node_t *child = NULL;

    int res = 0;
    int childs_num = 0;

    assert(tree);

    /*case : for trying remove a an empty list*/
    if( NULL == node )
    {
        return NULL;
    }

    res = tree->compare_func(data,node->data );

    /*case : found node to remove*/
    if( 0 == res )
    {
        childs_num = HowManyChilds(node);

        /*two kids*/
        if( 2 == childs_num )
        {
            successor = FindSuccessor(node->child[RIGHT]);
            node->data = successor->data;

            /*calling remove again on right successor child with successor data
              to remove successor from its subtree*/
            node->child[RIGHT] = AVLFindNodeToRemove(tree,node->child[RIGHT],successor->data);
            node = NodeBalancing(node);
            UpdateHeight(node);
            return node;
        }
        if(2 > childs_num)
        {
            if( NULL != node->child[LEFT] )
            {
                child = node->child[LEFT];
            }
            else if(NULL != node->child[RIGHT])
            {
                child = node->child[RIGHT];
            }
            /*leaf case*/
            if( 0 == childs_num )
            {
                child = NULL;
            }

            node->child[RIGHT] = NULL;
            node->child[LEFT] = NULL;
            node->data = NULL;
            free(node);

            return child;
        }
    }
    /*traversing left or right*/
    if(0 > res )
    {
      node->child[LEFT] = AVLFindNodeToRemove(tree,node->child[LEFT],data);
    }
    else if ( 0 < res )
    {
      node->child[RIGHT] = AVLFindNodeToRemove(tree,node->child[RIGHT],data);
    }
    /* blancing & updating height*/
    node = NodeBalancing(node);
    UpdateHeight(node);
    return node;
}
/****************************************************************************/
avl_node_t *FindSuccessor(avl_node_t *node )
{
    if( NULL == node->child[LEFT] )
    {
        return node;
    }

    return FindSuccessor(node->child[LEFT]);
}
/****************************************************************************/
void AVLDestroy(avl_t *tree)
{
    assert(tree);

    AVLDestroyHelper(tree->root);

    tree->root = NULL;
    tree->compare_func = NULL;
    free(tree);
    return;

}
/****************************************************************************/
void AVLDestroyHelper(avl_node_t* node)
{
    if( NULL == node )
    {
        return;
    }

    AVLDestroyHelper(node->child[LEFT]);
    AVLDestroyHelper(node->child[RIGHT]);

    node->child[LEFT] = NULL;
    node->child[RIGHT] = NULL;
    node->data = NULL;
    free(node);
}
/****************************************************************************/
const void *AVLFind(const avl_t *tree, const void *data)
{
    assert(tree);

    return AVLFindHelper(tree,tree->root, data);
}
/****************************************************************************/
const void *AVLFindHelper(const avl_t *tree ,const avl_node_t *node, const void *data)
{
    int res = 0;

    assert(tree);

    if( NULL == node )
    {
        return NULL;
    }

    res = tree->compare_func(node->data, data);

    if( 0 == res )
    {
        return node->data;
    }

    if( 0 > res )
    {
        return AVLFindHelper(tree, node->child[RIGHT],data);
    }
    else
    {
        return AVLFindHelper(tree, node->child[LEFT],data);
    }
}
/****************************************************************************/
int AVLIsEmpty(const avl_t *tree)
{
    assert(tree);
    return(NULL == tree->root);
}
/****************************************************************************/
int InOrder(avl_node_t *root, avl_operation_func_t callback, void *param)
{
    int status = SUCCESS;

    assert(callback);

    if(NULL == root)
    {
        return SUCCESS;
    }

    status = InOrder(root->child[LEFT], callback, param );
    if(SUCCESS !=  status) return status;

    status = callback(root->data, param);
    if(SUCCESS != status ) return status;

    status = InOrder(root->child[RIGHT], callback, param );
    if(SUCCESS !=  status) return status;

    return SUCCESS;
}
/****************************************************************************/
int PreOrder(avl_node_t *root, avl_operation_func_t callback, void *param)
{
    int status = SUCCESS;

    assert(callback);

    if(NULL == root)
    {
        return SUCCESS;
    }

    status = callback(root->data, param);
    if(SUCCESS !=  status) return status;

    status = PreOrder(root->child[LEFT], callback, param );
    if(SUCCESS !=  status) return status;

    status = PreOrder(root->child[RIGHT], callback, param );
    if(SUCCESS !=  status) return status;

    return status;
}
/****************************************************************************/
int PostOrder(avl_node_t *root, avl_operation_func_t callback, void *param)
{
    int status = SUCCESS;

    assert(callback);

    if(NULL == root)
    {
        return SUCCESS;
    }

    status = PostOrder(root->child[LEFT], callback, param );
    if(SUCCESS !=  status) return status;

    status = PostOrder(root->child[RIGHT], callback, param );
    if(SUCCESS !=  status) return status;

    status = callback(root->data, param);
    if(SUCCESS != status ) return status;

    return status;
}
/****************************************************************************/
int AVLForEach(avl_t *tree, avl_operation_func_t callback,
							void *parameters, traverse_t traverse)
{
    assert(tree);
    assert(callback);

    return (g_traverse_lut[traverse]((void*)(tree->root),callback,parameters));
}
/****************************************************************************/
size_t AVLCount(const avl_t *tree)
{
    size_t count = 0;

    assert(tree);

    AVLForEach((avl_t*)tree, AvlNodeCount,(void*)(&count),IN_ORDER);

    return count;
}
/****************************************************************************/
int AVLHeight(const avl_t *tree)
{
    assert(tree);

    if(NULL == tree->root)
    {
        return -1;
    }

    return(tree->root->height);
}
/****************************************************************************/
static avl_node_t *CreateNode(void *data)
{
    avl_node_t *node = (avl_node_t*)malloc(sizeof(avl_node_t));
    if(NULL == node)return NULL;

    node->child[RIGHT] = NULL;
    node->child[LEFT] = NULL;
    node->data = data;
    node->height = 0;
    return node;
}
/****************************************************************************/
static void UpdateHeight(avl_node_t *node)
{
    int left = -1;
    int right = -1;

    if( node->child[LEFT] )
    {
        left = node->child[LEFT]->height;
    }

    if( node->child[RIGHT] )
    {
        right = node->child[RIGHT]->height;
    }

    node->height = MAX(left, right) + 1;
}
/****************************************************************************/
static int AvlNodeCount(void *target, void *parameters)
{
    (void)target;
    ++(*(size_t*)parameters);
    return SUCCESS;
}
/****************************************************************************/
static int HowManyChilds(const avl_node_t *target)
{
	int counter = 2;
    assert(target);

	if( NULL == ((avl_node_t*)target)->child[LEFT] ) --counter;
	if( NULL == ((avl_node_t*)target)->child[RIGHT] ) --counter;

    return counter;
}
/****************************************************************************/
static avl_node_t *LeftRotate( avl_node_t *root)
{
  avl_node_t *pivot1 = root->child[RIGHT];
  avl_node_t *pivot2 = pivot1->child[LEFT];

  pivot1->child[LEFT] = root;
  root->child[RIGHT] = pivot2;
  UpdateHeight(root);
  UpdateHeight(pivot1);

  return pivot1;
}
/****************************************************************************/
static avl_node_t *RightRotate( avl_node_t *root)
{
    avl_node_t *pivot1 = root->child[LEFT];
    avl_node_t *pivot2 = pivot1->child[RIGHT];

    pivot1->child[RIGHT] = root;
    root->child[LEFT] = pivot2;

    UpdateHeight(root);
    UpdateHeight(pivot1);

    return pivot1;
}
/****************************************************************************/
static avl_node_t *RightLeftRotate( avl_node_t *bad_node)
{
    assert(bad_node);

    bad_node->child[RIGHT] = RightRotate(bad_node->child[RIGHT]);
    bad_node = LeftRotate(bad_node);
    UpdateHeight(bad_node);

    return bad_node;
}
/****************************************************************************/
static avl_node_t *LeftRightRotate( avl_node_t *bad_node)
{
    assert(bad_node);

    bad_node->child[LEFT] = LeftRotate(bad_node->child[LEFT]);
    bad_node = RightRotate(bad_node);
    UpdateHeight(bad_node);

    return bad_node;
}
/****************************************************************************/
static int BalanceFactor( avl_node_t *node)
{
    int left = -1;
    int right = -1;

    if( node->child[LEFT] )
    {
        left = node->child[LEFT]->height;
    }

    if( node->child[RIGHT] )
    {
        right = node->child[RIGHT]->height;
    }

    return right - left;
}
/****************************************************************************/
static avl_node_t *NodeBalancing(avl_node_t *bad_node)
{
    int root_balance  = 0;
    int piv_balance = 0;

    assert(bad_node);

    root_balance = BalanceFactor(bad_node);


    if (root_balance >= -1 && root_balance <= 1) /*if balanced*/
    {
        return bad_node;
    }
    if( 2 <= root_balance ) /*right case*/
    {
       piv_balance = BalanceFactor(bad_node->child[RIGHT]);
       if( 0 <= piv_balance) /*right right case*/
       {
            return LeftRotate(bad_node);
       }
       else
       {
            return RightLeftRotate(bad_node); /*right left case*/
       }

    }
    else if( -2 >= root_balance ) /*left case*/
    {
        piv_balance = BalanceFactor(bad_node->child[LEFT]);

        if( 0 >= piv_balance) /*left left case*/
        {

            return RightRotate(bad_node);
        }
        else
        {
            return LeftRightRotate(bad_node); /*left right case*/
        }
    }
    return bad_node;
}
