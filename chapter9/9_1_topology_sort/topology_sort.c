#include <stdio.h>
#include <stdlib.h>

struct list {
    int element;
    struct list *next;
};

struct graph {
    int capacity;
    struct list *l;
};

void list_insert(struct list *l, int element)
{
    if(!l) {
        printf("List is null\n");
        return;
    }

    while(l->next) {
        l = l->next;
    }
    l->next = malloc(sizeof(struct list));
    if(!l->next) {
        printf("Out of space\n");
        return;
    }
    l->next->element = element;
    l->next->next = NULL;
}

void init(struct graph *g)
{
    g->l[0].element = 1;
    g->l[0].next = NULL;
    list_insert(&g->l[0], 2);
    list_insert(&g->l[0], 3);
    list_insert(&g->l[0], 4);

    g->l[1].element = 2;
    g->l[1].next = NULL;
    list_insert(&g->l[1], 4);
    list_insert(&g->l[1], 5);

    g->l[2].element = 3;
    g->l[2].next = NULL;
    list_insert(&g->l[2], 6);

    g->l[3].element = 4;
    g->l[3].next = NULL;
    list_insert(&g->l[3], 3);
    list_insert(&g->l[3], 6);
    list_insert(&g->l[3], 7);

    g->l[4].element = 5;
    g->l[4].next = NULL;
    list_insert(&g->l[4], 4);
    list_insert(&g->l[4], 7);

    g->l[5].element = 6;
    g->l[5].next = NULL;

    g->l[6].element = 7;
    g->l[6].next = NULL;
    list_insert(&g->l[6], 6);
}

void dump_graph(struct graph *g)
{
    int i = 0;
    struct list *tmp;

    for(i=0; i<g->capacity; i++) {
        tmp = &g->l[i];
        while (tmp){
            printf("%d\t", tmp->element);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

int main(void)
{
    struct graph g;
    g.capacity = 7;
    g.l = malloc(sizeof(struct graph)*7);
    if(!g.l) {
        printf("%s: %d, out of space\n", __FUNCTION__, __LINE__);
    }
    init(&g);
    dump_graph(&g);

    return 0;
}