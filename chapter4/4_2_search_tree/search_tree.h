#ifndef _SEARCH_TREE_H_
#define _SEARCH_TREE_H_

struct tree_node;

struct tree_node* make_empty(struct tree_node *t);
struct tree_node* find(int x, struct tree_node *t);
struct tree_node* find_min(struct tree_node *t);
struct tree_node* find_max(struct tree_node *t);

struct tree_node* insert(int x, struct tree_node *t);
struct tree_node* delete(int x, struct tree_node *t);
int retrieve(struct tree_node *t);

#endif