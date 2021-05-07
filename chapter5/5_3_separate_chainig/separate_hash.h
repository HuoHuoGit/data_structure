#ifndef _SEPARATE_HASH_H_
#define _SEPARATE_HASH_H_

struct list_node;
struct hash_tbl;

struct hash_tbl* init_table(int table_size);
void destroy_table(struct hash_tbl *h);
struct list_node* find(int key, struct hash_tbl *h);
void insert(int key, struct hash_tbl *h);
int retrieve(struct list_node *p);

#endif