#include "separate_hash.h"
#include <stdlib.h>
#include <stdbool.h>

#define MIN_TABLE_SIZE 10

struct list_node {
    int element;
    struct list_node *next;
};

struct hash_tbl {
    int table_size;
    struct list_node **list;
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
    struct hash_tbl *h = NULL;
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

    h->list = malloc(sizeof(struct list_node*) * h->table_size);
    if(!h->list) {
        printf("Out of space\n");
        return NULL;
    }

    for(i=0; i<h->table_size; i++) {
        h->list[i] = malloc(sizeof(struct list_node));
        if(!h->list[i]) {
            printf("Out of space\n");
            return NULL;
        }
        h->list[i]->next =  NULL;
    }

    return h;
}
void destroy_table(struct hash_tbl *h);

struct list_node* find(int key, struct hash_tbl *h);
void insert(int key, struct hash_tbl *h);
int retrieve(struct list_node *p);