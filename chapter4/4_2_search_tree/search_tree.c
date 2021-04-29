#include "search_tree.h"
#include <stdlib.h>

struct tree_node {
    int element;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node* make_empty(struct tree_node *t)
{
    if(!t) {
        make_empty(t->left);
        make_empty(t->right);
        free(t);
    }

    return NULL;
}

struct tree_node* find(int x, struct tree_node *t)
{
    if(!t)
        return NULL;

    if(x < t->element)
        return find(x, t->left);
    else if(x > t->element)
        return find(x, t->right);
    else
        return t;
}

struct tree_node* find_min(struct tree_node *t)
{
    if(!t)
        return NULL;

    if(!t->left)
        return t;
    else
        return find_min(t->left);
}

struct tree_node* find_max(struct tree_node *t)
{
    if(!t)
        while (t->right) {
            t = t->right;
        }

    return t;
}

struct tree_node* insert(int x, struct tree_node *t);
struct tree_node* delete(int x, struct tree_node *t);
int retrieve(struct tree_node *t);