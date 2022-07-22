#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avl.h"


typedef struct Node node_t;

struct Node
{
    node_t *right;
    node_t *left;
    size_t height; 
    const void *data;
};

struct AVL
{
    node_t *root;
    compare_func_t comp_func;
    const void *param;
};


static void *AvlFindHelper(avl_t *avl, const void *data, node_t *node);
static node_t *AvlInsertHelper(avl_t *avl, const void *data, node_t *curr_node, node_t *new_node);
static node_t *Crete_Empty_Leaf(void);
static int AvlForEachInOrder(avl_t *avl, action_func_t action_func, const void *param, node_t *curr_node);
static int AvlForEachPreOrder(avl_t *avl, action_func_t action_func, const void *param, node_t *curr_node);
static int AvlForEachPostOrder(avl_t *avl, action_func_t action_func, const void *param, node_t *curr_node);
static int HasLeftChild(node_t *node);
static int HasRightChild(node_t *node);
static int AvlSizeHelper(const avl_t *avl, node_t *curr_node);
static void UpdateHeight(node_t *node);
static int IsBalanced(node_t *node);
static int HeightLeftChild(node_t *node);
static int HeightRightChild(node_t *node);
static node_t *RotateLeft(node_t *node);
static node_t *RotateRight(node_t *node);
static node_t *DoBalancing(node_t *node);
static node_t *AvlRemoveHelper(avl_t *avl, const void *data, node_t *curr_node);
static node_t *AvlNext(node_t *node);
static void AvlDestroyHelper(node_t *curr_node);



avl_t *AvlCreate(compare_func_t cmp_func, const void *param)
{
    avl_t *new_avl = NULL;
    new_avl = (avl_t*)malloc(sizeof(avl_t));
    if(NULL == new_avl)
    {
        return NULL;
    }

    new_avl->comp_func = cmp_func;
    new_avl->param = param;
    new_avl->root = NULL;

    return new_avl;
}


void AvlDestroy(avl_t *avl)
{
    AvlDestroyHelper(avl->root);
    free(avl);
}


size_t AvlSize(const avl_t *avl)
{
    if(NULL == avl->root)
    {
        return 0;
    }

    return AvlSizeHelper(avl, avl->root);
}


size_t AvlHeight(const avl_t *avl)
{
    if(!avl->root)
    {
        return 0;
    }
    return avl->root->height;
}


int AvlIsEmpty(const avl_t *avl)
{
    if(avl->root == NULL)
    {
        return 1;
    }
    return 0;
}


int AvlInsert(avl_t *avl, const void *data)
{
    node_t *new_node = Crete_Empty_Leaf();
    new_node->data = data;

    if(AvlIsEmpty(avl))
    {
        avl->root = new_node;
        new_node->height = 1;
    }

    avl->root = AvlInsertHelper(avl, data, avl->root, new_node);
    return 0;
}


void AvlRemove(avl_t *avl, const void *data)
{
    assert(avl);
    avl->root = AvlRemoveHelper(avl, data, avl->root);

}


const void *AvlFind(avl_t *avl, const void *data)
{
    if (NULL == avl->root)
    {
        return NULL;
    }
    
    return AvlFindHelper(avl, data, avl->root);
}


int AvlForEach(avl_t *avl, action_func_t action_func, const void *param, traversal_t order)
{
    if(IN_ORDER == order)
    {
        AvlForEachInOrder(avl, action_func, param, avl->root);
    }    

    if(PRE_ORDER == order)
    {
        AvlForEachPreOrder(avl, action_func, param, avl->root);
    }  

    if(POST_ORDER == order)
    {
        AvlForEachPostOrder(avl, action_func, param, avl->root);
    }  

    return 0;
}


/* --------------internal functions---------------- */


void AvlDestroyHelper(node_t *curr_node)
{
    if(NULL == curr_node)
    {
        return;
    }

    AvlDestroyHelper(curr_node->right);

    AvlDestroyHelper(curr_node->left);

    free(curr_node);
}


int AvlSizeHelper(const avl_t *avl, node_t *curr_node)
{
    if(NULL == curr_node)
    {
        return 0;
    }

    return AvlSizeHelper(avl, curr_node->right) + AvlSizeHelper(avl, curr_node->left) + 1; 
}


node_t *AvlInsertHelper(avl_t *avl, const void *data, node_t *curr_node, node_t *new_node)
{
    if(NULL == curr_node)
    {
        return new_node;
    }

    if(0 == avl->comp_func(data, curr_node->data, avl->param))
    {
        /* data already exists - return without insersion */
        return curr_node;
    }


    if(1 == avl->comp_func(data, curr_node->data, avl->param))
    {
        /* go right */
        /* actual insersion */
        curr_node->right = AvlInsertHelper(avl, data, curr_node->right, new_node);
    }

    else
    {
        /* go left */
        /* actual insersion */
        curr_node->left = AvlInsertHelper(avl, data, curr_node->left, new_node);
    
    }

    UpdateHeight(curr_node);

    /* balance check */
    if(IsBalanced(curr_node) > 1 || IsBalanced(curr_node) < -1)
    {
        curr_node = DoBalancing(curr_node);
        UpdateHeight(curr_node);
    }
    
    return curr_node;
}


node_t *AvlRemoveHelper(avl_t *avl, const void *data, node_t *curr_node)
{
    if(NULL == curr_node)
    {
        return NULL;
    }

    if(1 == avl->comp_func(data, curr_node->data, avl->param))
    {
        /* go right */
        curr_node->right = AvlRemoveHelper(avl, data, curr_node->right);
    }

    else if(-1 == avl->comp_func(data, curr_node->data, avl->param))
    {
        /* go left */
        curr_node->left = AvlRemoveHelper(avl, data, curr_node->left);
    }

    else
    {
        /* actual removing */

        if(!HasRightChild(curr_node) && !HeightLeftChild(curr_node))
        {
            /* no children */
            free(curr_node);
            curr_node = NULL;
        }

        else if(HasRightChild(curr_node) && !HasLeftChild(curr_node))
        {
            /* right child only */
            node_t *temp = curr_node->right;
            free(curr_node);
            curr_node = temp;
        }

        else if(!HasRightChild(curr_node) && HasLeftChild(curr_node))
        {
            /* left child only */
            node_t *temp = curr_node->left;
            free(curr_node);
            curr_node = temp;
        }
        
        else 
        {
            /* 2 children */

            curr_node->data = AvlNext(curr_node->right)->data;
            curr_node->right = AvlRemoveHelper(avl, curr_node->data, curr_node->right);
        }
        
    }
    if (curr_node)
    {
        UpdateHeight(curr_node);

        /* balance check */
        if(IsBalanced(curr_node) > 1 || IsBalanced(curr_node) < -1)
        {
            curr_node = DoBalancing(curr_node);
            UpdateHeight(curr_node);
        }
    }
    return curr_node;
}


int AvlForEachInOrder(avl_t *avl, action_func_t action_func, const void *param, node_t *curr_node)
{
    if(!curr_node)
    {
        return 1;
    }

    AvlForEachInOrder(avl, action_func, param, curr_node->left);

    action_func((void*)curr_node->data, param);

    AvlForEachInOrder(avl, action_func, param, curr_node->right);

    return 0;
}


int AvlForEachPreOrder(avl_t *avl, action_func_t action_func, const void *param, node_t *curr_node)
{
    if(!curr_node)
    {
        return 1;
    }

    action_func((void*)curr_node->data, param);

    AvlForEachInOrder(avl, action_func, param, curr_node->left);

    AvlForEachInOrder(avl, action_func, param, curr_node->right);
    return 0;
}


int AvlForEachPostOrder(avl_t *avl, action_func_t action_func, const void *param, node_t *curr_node)
{
    if(!curr_node)
    {
        return 1;
    }

    AvlForEachInOrder(avl, action_func, param, curr_node->left);

    AvlForEachInOrder(avl, action_func, param, curr_node->right);

    action_func((void*)curr_node->data, param);

    return 0;
}



void *AvlFindHelper(avl_t *avl, const void *data, node_t* curr_node)
{
    if(0 == avl->comp_func(data, curr_node->data, avl->param))
    {
        return (void*)curr_node->data;
    } 

    else if(1 == avl->comp_func(data, curr_node->data, avl->param))
    {
        /* go write */
        return AvlFindHelper(avl, data, curr_node->right);
    }

    else
    {
        /* go left */
        return AvlFindHelper(avl, data, curr_node->left);
    }
}


node_t *Crete_Empty_Leaf(void)
{
    node_t *new_node = NULL;
    new_node = (node_t*)malloc(sizeof(node_t));
    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->right = NULL;
    new_node->left = NULL;
    new_node->height = 1;

    return new_node;
}


int HasLeftChild(node_t *node)
{
    if(NULL == node->left)
    {
        return 0;
    }
    return 1;
}


int HasRightChild(node_t *node)
{
    if(NULL == node->right)
    {
        return 0;
    }
    return 1;
}


void UpdateHeight(node_t *node)
{
    int a = 0;
    int b = 0;
    int res = 1;

    if(node->left)
    {
        a = node->left->height;
    }
    
    if(node->right)
    {
        b = node->right->height;
    }

    res += a > b ? a : b;
    node->height = res;
}


int IsBalanced(node_t *node)
{
    int diff = HeightLeftChild(node) - HeightRightChild(node);

    if(diff >= 2)
    {
        return 2;
    }

    else if(diff <= -2)
    {
        return -2;
    }

    else if(diff >= 1)
    {
        return 1;
    }

    else if(diff <= -1)
    {
        return -1;
    }

    return 0;
}


int HeightLeftChild(node_t *node)
{
    if(NULL == node->left)
    {
        return 0;
    }
    return node->left->height;
}


int HeightRightChild(node_t *node)
{
    if(NULL == node->right)
    {
        return 0;
    }
    return node->right->height;
}

    
node_t *DoBalancing(node_t *node)
{
    if(2 == IsBalanced(node))
    {
        /* Left heavy */
        if(IsBalanced(node->left) == -1)
        {
            /* Left-Right heavy - Do left and then right */
            node->left = RotateLeft(node->left);
        }
        return RotateRight(node);
    }

    else if(-2 == IsBalanced(node))
    {
        /* Right heavy */
        if(IsBalanced(node->right) == 1)
        {
            /* Right-Left heavy - Do right and then left */
            node->right = RotateRight(node->right);
        }
        return RotateLeft(node);
    }

    else
    {
        return node;
    }
}


node_t *RotateRight(node_t *node)
{
    node_t *temp = node->left;

    node->left = temp->right;
    temp->right = node;

    UpdateHeight(node);
    UpdateHeight(temp);

    return temp;
}


node_t *RotateLeft(node_t *node)
{
    node_t *temp = node->right;

    node->right = temp->left;
    temp->left = node;

    UpdateHeight(node);
    UpdateHeight(temp);

    return temp;
}


node_t *AvlNext(node_t *curr_node)
{
    if(!curr_node->left)
    {
        return curr_node;
    }

    return AvlNext(curr_node->left);
}