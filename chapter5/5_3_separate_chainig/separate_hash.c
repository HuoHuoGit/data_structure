#include "separate_hash.h"
#include "..\..\chapter3\3_2_4_List\list.h"
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

static int hash(int key, int tabl_size)//dummy function
{
    unsigned int hash_val = 0;

    //while()

    return key;
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

struct list_node* find(int key, struct hash_tbl *h)
{
    struct list_node *p = NULL;
    struct list_node *l = NULL;

    l = h->list[hash(key, h->table_size)];
    p = l->next;
    while (!p && p->element!=key)
        p = p->next;

    return p;
}

void insert(int key, struct hash_tbl *h)
{
    struct list_node *p=NULL, *new_cell=NULL, *l=NULL;

    p = find(key, h);
    if(!p) {
        new_cell = malloc(sizeof(struct list_node));
        if(!new_cell) {
            printf("Out of space\n");
            return;
        }
        l = h->list[hash(key, h->table_size)];
        new_cell->next = l->next;//把新插入的元素放在列表的前端
        new_cell->element = key;
        l->next = new_cell;
    }
}

int retrieve(struct list_node *p);