#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

struct avl_node;

struct avl_node* make_empty(struct avl_node *t);

struct avl_node* find(int x, struct avl_node *t);
struct avl_node* find_min(struct avl_node *t);
struct avl_node* find_max(struct avl_node *t);

struct avl_node* insert(int x, struct avl_node *t);
struct avl_node* delete(int x, struct avl_node *t);
int retrieve(struct avl_node *t);

#endif