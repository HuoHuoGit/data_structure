#ifndef _HASH_QUAD_H_
#define _HASH_QUAD_H_

struct hash_tbl;

struct hash_tbl* init_table(int table_size);
void destory_table(struct hash_tbl* h);
unsigned int find(int key, struct hash_tbl* h);
void insert(int key, struct hash_tbl* h);
int retrieve(unsigned int p, struct hash_tbl* h);
struct hash_tbl* rehash(struct hash_tbl* h);

#endif