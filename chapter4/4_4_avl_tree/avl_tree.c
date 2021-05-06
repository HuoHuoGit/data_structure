#include "avl_tree.h"
#include <stdlib.h>

struct avl_node {
    int element;
    struct avl_node *left;
    struct avl_node *right;
    int height;
};

static int height(struct avl_node *t)
{
    if(!t)
        return -1;

    return t->height;
}

static struct avl_node* single_rotate_left(struct avl_node * k2)
{
    struct avl_node *k1 = NULL;

    if(!k2)
        return NULL;

    k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;

    return k1;
}

static struct avl_node* single_rotate_right(struct avl_node * k2)
{
    struct avl_node *k1 = NULL;

    if(!k2)
        return NULL;

    k1 = k2->right;

    k2->right = k1->left;
    k1->left = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;

    return k1;
}

static struct avl_node* double_rotate_left(struct avl_node *k3)
{
    k3->left = single_rotate_right(k3->left);

    return single_rotate_left(k3);
}

static struct avl_node* double_rotate_right(struct avl_node *k3)
{
    k3->left = single_rotate_left(k3->right);

    return single_rotate_right(k3);
}

struct avl_node* make_empty(struct avl_node *t)
{
    if(t) {
        make_empty(t->left);
        make_empty(t->right);
        free(t);
    }

    return NULL;
}

struct avl_node* find(int x, struct avl_node *t)
{
    if(!t)
        return NULL;

    if(x == t->element)
        return t;

    if(x > t->left->element)
        return find(x, t->left);
    else
        return find(x, t->right);
}

struct avl_node* find_min(struct avl_node *t)
{
    if(!t)
        return NULL;

    while (t->left) {
        t = t->left;
    }
//#if 0
    if(!t)
        return NULL;

    if(t->left)
        return find_min(t->left);

    return t;
//#endif

    return t;
}

struct avl_node* find_max(struct avl_node *t)
{
    if(!t)
        return NULL;

    while (t->right) {
        t = t->right;
    }

    return t;
}

struct avl_node* insert(int x, struct avl_node *t)
{
    if(!t) {
        t = malloc(sizeof(struct avl_node));
        if(!t) {
            printf("Out of space\n");
            return NULL;
        }

        t->element = x;
        t->left = NULL;
        t->right = NULL;
        t->height = 0;
    } else if(x < t->element) {         //左子树
        t->left =  insert(x, t->left);
        if(abs(height(t->left)-height(t->right)) == 2) {
            if(x < t->left->element)            //左子树
                single_rotate_left(t);
            else                                //右子树
                double_rotate_left(t);
        }
    } else if(x > t->element) {         //右子树
        t->right = insert(x, t->right);
        if(abs(height(t->left)-height(t->right)) == 2) {
            if(x < t->right->element)
                single_rotate_right(t);         //右子树
            else
                double_rotate_right(t);         //左子树
        }
    }

    return t;
}

struct avl_node* delete(int x, struct avl_node *t);
int retrieve(struct avl_node *t);