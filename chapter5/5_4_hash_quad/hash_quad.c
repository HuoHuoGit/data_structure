#include "hash_quad.h"
#include <stdlib.h>
#include <stdbool.h>

#define MIN_TABLE_SIZE 10

enum kind_entry{
    LEGITIMATE,
    EMPTY,
    DELETED
};

struct hash_entry {
    int element;
    enum kind_entry info;
};

struct hash_tbl {
    int table_size;
    struct hash_entry *cells;
};

static bool check_prime(int x)
{
    if((x+1)%6 == 0 || (x-1)%6 == 0)
        return true;

    return false;
}

static int next_prime(int x)
{
    while (!check_prime(x)) {
        x++;
    }
    
    return x;
}

struct hash_tbl* init_table(int table_size)
{
    struct hash_tbl *h;
    int i = 0;

    if(table_size < MIN_TABLE_SIZE) {
        printf("Table size too small\n");
        return NULL;
    }

    h = malloc(sizeof(struct hash_tbl));
    if(!h) {
        printf("Out of space\n");
        return NULL;
    }

    h->table_size = next_prime(table_size);
    h->cells = malloc(sizeof(struct hash_entry)*h->table_size);
    if(!h->cells) {
        printf("Out of space\n");
        return NULL;
    }
    for(i=0; i<h->table_size; i++)
        h->cells[i].info = EMPTY;

    return h;
}

void destory_table(struct hash_tbl* h);

static unsigned int hash(int key, int size)
{
    return key;
}

unsigned int find(int key, struct hash_tbl* h)
{
    unsigned int current_pos = 0;
    int collision_num = 0;

    current_pos = hash(key, h->table_size);
    while(h->cells[current_pos].info!=EMPTY && h->cells[current_pos].element!=key) {
        current_pos += 2 * ++collision_num -1;
        if(current_pos >= h->table_size)
            current_pos -= h->table_size;
    }

    return current_pos;
}

void insert(int key, struct hash_tbl* h)
{
    unsigned int pos;

    pos = find(key, h);
    if(h->cells[pos].info != LEGITIMATE) {
        h->cells[pos].info = LEGITIMATE;
        h->cells[pos].element = key;
    }
}

int retrieve(unsigned int p, struct hash_tbl* h);

struct hash_tbl* rehash(struct hash_tbl* h)
{
    int i = 0;
    int old_size = h->table_size;
    struct hash_entry *old_cell = h->cells;

    h = init_table(2*old_size);

    for(i=0; i<old_size; i++) {
        if(old_cell[i].info == LEGITIMATE)
            insert(old_cell[i].element, h);
    }
    free(old_cell);

    return h;
}