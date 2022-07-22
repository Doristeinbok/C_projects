#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include "bst.h"


static int HasRightChild(bst_iter_t iter);
static int HasLeftChild(bst_iter_t iter);
static int IsLeftChild(bst_iter_t iter);
static int IsRightChild(bst_iter_t iter);
static bst_iter_t IterRight(bst_iter_t iter);
static bst_iter_t IterLeft(bst_iter_t iter);
static bst_iter_t IterParent(bst_iter_t iter);
static bst_iter_t IterRoot(bst_iter_t iter);
static int IsRoot(bst_iter_t iter);
static int IsLeaf(bst_iter_t iter);
static bst_node_t *CreateEmptyNode();


struct BST
{
    bst_node_t *root;
    bst_node_t *end;
    compare_func_t compare_func;
    void *param;
};

struct BSTNode
{
    void *data;
    bst_node_t *left;
    bst_node_t *right;
    bst_node_t *parent;
};



bst_t *BstCreate(compare_func_t cmp_func, const void *param)
{
    bst_t *new_bst = NULL;
    bst_node_t *dummy = NULL;

    new_bst = (bst_t*)malloc(sizeof(bst_t));
    if (NULL == new_bst)
    {
        return NULL;
    }
    dummy = CreateEmptyNode();

    new_bst->root = dummy; 
    new_bst->end = dummy;
    new_bst->compare_func = cmp_func;
    new_bst->param = (void*)param;

    return new_bst;
}


void BstDestroy(bst_t *bst)
{
    bst_iter_t iter = BstBegin(bst);

    for(; !BstIsEmpty(bst); iter = BstBegin(bst))
    {
        BstRemove(iter);        
    }
}


size_t BstSize(bst_t *bst)
{
    size_t count = 1;
    bst_iter_t from = BstBegin(bst);
    bst_iter_t to = BstEnd(bst);

    if (BstIsEmpty(bst))
    {
        return 0;
    }
    
    for(; !BstIterIsEqual(from, to); from = BstIterNext(from))
    {
        ++count;
    }
    return count;
}


int BstIsEmpty(bst_t *bst)
{
/* check if root pointing to NULL data */
    if (bst->end == bst->root)
    {
        return 1;
    }
    return 0;
}


bst_iter_t BstInsert(bst_t *bst, const void *data)
{
    /* crete node with data */
    bst_node_t *new_node = CreateEmptyNode();
    bst_iter_t iter;
    
    new_node->data = (void*)data;
    iter.bst = bst;
    iter.node = new_node;

    /* check if bst is empty */
    if (bst->root == bst->end)
    {
        bst->root = new_node;
        new_node->right = bst->end;
        new_node->left = NULL;
        bst->end->parent = new_node;

        return iter;
    }

    iter = IterRoot(iter);

    while (iter.node != NULL)
    {

        /* check if new_node is bigger than current node */
                
        if (1 == bst->compare_func(new_node->data, iter.node->data, (void*)data))
        {
            if (iter.node->right == iter.bst->end)
            {
                /* It's dummy */
                new_node->right = iter.node->right;
                new_node->parent = iter.node;

                iter.node->right->parent = new_node;

                iter.node->right = new_node;
                new_node->left = NULL;
                return IterRight(iter);
            }

            else if (NULL == iter.node->right)
            {
                iter.node->right = new_node;
                new_node->parent = iter.node;
                return IterRight(iter);
            }
            
            else 
            {
                iter = IterRight(iter);
            }   
        }

        else if (-1 == bst->compare_func(new_node->data, iter.node->data, (void*)data))
        {
            if (NULL == iter.node->left)
            {
                iter.node->left = new_node;
                new_node->parent = iter.node;
                return IterLeft(iter);
            }

            else
            {
                iter = IterLeft(iter);
            }
        }
    }
    return BstEnd(bst);
}

void BstRemove(bst_iter_t iter)
{
    /* option 1: no children */
    if (IsLeaf(iter))
    {
        if(IsRoot(iter))
        {
            iter.bst->end->parent = NULL;
            iter.bst->root = iter.bst->end;
        }
        else if(1 == IsLeftChild(iter))
        {
            iter.node->parent->left = NULL;
        }

        else if(1 == IsRightChild(iter))
        {
            iter.node->parent->right = NULL;
        }
        iter.node->parent = NULL;
    }

    /* option 2: one child */

    else if(HasLeftChild(iter))
    {
        if(IsRoot(iter))
        {
            iter.node->left->parent = NULL;                        
        }
        else
        {
            iter.node->left->parent = iter.node->parent;
            iter.node->parent->left = iter.node->left;
        }
    }

    else if(HasRightChild(iter))
    {
        if(IsRoot(iter))
        {
            iter.node->right->parent = NULL;
        }

        else if(IsRightChild(iter))
        {
            iter.node->parent->right = iter.node->right;
        }

        else if(IsLeftChild(iter))
        {
            iter.node->parent->left = iter.node->right;
        }

        iter.node->right->parent = iter.node->parent;
    }

    /* option 3: 2 children */

    else if(HasRightChild(iter) && HasLeftChild(iter))
    {
        bst_iter_t leftest;

        /* right node replace the deleted node */

        if(IsRoot(iter))
        {
            iter.node->right->parent = NULL;
        }

        else
        {
            iter.node->right->parent = iter.node->parent;
            iter.node->parent->right = iter.node->right;
        }

        /* left child of deleted node will be now the child of the leftest children of right node */
        /* step 1: find the leftest child of the right node */

        for(leftest = IterRight(iter); HasLeftChild(leftest); leftest = IterLeft(iter))
        {}
        
        /* step 2: attach it to be parent of left son of the deleted node */

        leftest.node->left = iter.node->left;
        iter.node->left->parent = leftest.node;
    }
    free(iter.node);
}

bst_iter_t BstIterNext(bst_iter_t iter)
{
    const void* data = BstIterGetData(iter);

    /* if right exists, go right and then left all the way*/

    if(HasRightChild(iter))
    {
        iter = IterRight(iter);
        while(HasLeftChild(iter))
        {
            iter = IterLeft(iter);
        }
        return iter;
    }


    /* if right is NULL, go to parent */

    while(iter.node)
    {
        iter = IterParent(iter);
        if(1 == iter.bst->compare_func(iter.node->data, data, iter.bst->param))
        {
            return iter;
        }
    }
    return iter;
}


bst_iter_t BstIterPrev(bst_iter_t iter)
{
    bst_iter_t iter_original;
    iter_original.bst = iter.bst;
    iter_original.node = iter.node;

    /* if you have left => go left and than right all the way */

    if(IterLeft(iter).node)
    {
        iter = IterLeft(iter);
        for(; IterRight(iter).node; iter = IterRight(iter))
        {}

        return iter;
    }


    /* if you don't have left => go up until you find parent smaller than you */

    else
    {
        while(IterParent(iter).node)
        {
            if(IterParent(iter).node->data < iter_original.node->data)
            {
                return IterParent(iter);
            }
        }
    }

    return iter_original;
}


bst_iter_t BstBegin(bst_t *bst)
{
    bst_iter_t iter;
    iter.bst = bst;
    iter.node = bst->root;

    while (NULL != iter.node->left)
    {
        iter = IterLeft(iter);;
    }
    
    return iter;
}


bst_iter_t BstEnd(bst_t *bst)
{
    bst_iter_t iter;
    iter.node = bst->end->parent;
    iter.bst = bst;
    
    return iter;
}


int BstIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
    if(iter1.node == iter2.node)
    {
        return 1;
    }
    return 0;
}


void *BstIterGetData(bst_iter_t iter)
{
    return iter.node->data;
}


bst_iter_t BstFind(bst_t *bst, const void *data)
{
    bst_iter_t from = BstBegin(bst);
    bst_iter_t to = BstEnd(bst);

    for(; !BstIterIsEqual(from, to); BstIterNext(from))
    {
        if(data == from.node->data)
        {
            return from;
        }
    }  
    return BstEnd(bst);
}


int BstForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func, const void *param)
{
    for(; !BstIterIsEqual(from, to); from = BstIterNext(from))
    {
        action_func(from.node->data, param);
    }

    action_func(from.node->data, param);

    return 0;
}



/****************************** Helpers Functions ******************************/



int HasRightChild(bst_iter_t iter)
{
    if (iter.node->right)
    {
        return 1;
    }
    return 0;
}

int HasLeftChild(bst_iter_t iter)
{
    if (iter.node->left)
    {
        return 1;
    }
    return 0;
}

int IsLeftChild(bst_iter_t iter)
{
    if(iter.node->parent->left == iter.node)
    {
        return 1;
    }
    return 0;
}

int IsRightChild(bst_iter_t iter)
{
    if(iter.node->parent->right == iter.node)
    {
        return 1;
    }
    return 0;
}

bst_iter_t IterRight(bst_iter_t iter)
{
    iter.node = iter.node->right;
    return iter;
}


bst_iter_t IterLeft(bst_iter_t iter)
{
    iter.node = iter.node->left;
    return iter;
}

bst_iter_t IterParent(bst_iter_t iter)
{
    iter.node = iter.node->parent;
    return iter;
}

bst_iter_t IterRoot(bst_iter_t iter)
{
    bst_iter_t iter_root;
    iter_root.bst = iter.bst; 
    iter_root.node = iter.bst->root;
    return iter_root;
}

static int IsRoot(bst_iter_t iter)
{
    if (NULL == iter.node->parent)
    {
        return 1;
    }
    return 0;
}

static int IsLeaf(bst_iter_t iter)
{
    if (NULL == iter.node->left && NULL == iter.node->right)
    {
        return 1;
    }
    return 0;
}

bst_node_t *CreateEmptyNode()
{
    bst_node_t *new_node = NULL;
    new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    if (!new_node)
    {
        return NULL;
    }

    new_node->data = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    return new_node;
}