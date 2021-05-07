#include "search_tree.h"
#include <stdlib.h>

struct tree_node {
    int element;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node* make_empty(struct tree_node *t)
{
    if(t) {
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
    if(t)
        while (t->right) {
            t = t->right;
        }

    return t;
}

struct tree_node* insert(int x, struct tree_node *t)
{
    if(!t) {
        t = malloc(sizeof(struct tree_node));
        if(!t) {
            printf("Out of space\n");
            return NULL;
        };

        t->element = x;
        t->left = NULL;
        t->right = NULL;
    } else {
        if(x < t->element)
            t->left = insert(x, t->left);
        else if(x > t->element)
            t->right = insert(x, t->right);
    }

    return t;
}

struct tree_node* delete(int x, struct tree_node *t)
{
    struct tree_node *tmp = NULL;

    if(!t) {
        printf("Element not found\n");
        return NULL;
    }

    if(x < t->element)
        t->left = delete(x, t->left);
    else if(x > t->element)
        t->right = delete(x, t->right);
    else if(t->left && t->right){
        tmp = find_min(t->right);
        t->element = tmp->element;
        t->right = delete(tmp->element, t->right);
    } else {
        tmp = t;
        if(t->left)
            t = t->left;
        else
            t = t->right;
        free(tmp);
    }

    return t;
}

int retrieve(struct tree_node *t);