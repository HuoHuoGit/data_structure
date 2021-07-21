#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct list {
    int element;
    struct list *next;
};

struct vertex {
    int known;
    int d;
    int p;
    struct list *l;
};

struct graph {
    int capacity;
    int *indegree;
    struct vertex *v;
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
    struct list *tmp;
    int i = 0;
    g->l[1].element = 1;
    g->l[1].next = NULL;
    list_insert(&g->l[1], 2);
    list_insert(&g->l[1], 4);

    g->l[2].element = 2;
    g->l[2].next = NULL;
    list_insert(&g->l[2], 4);
    list_insert(&g->l[2], 5);

    g->l[3].element = 3;
    g->l[3].next = NULL;
    list_insert(&g->l[3], 6);

    g->l[4].element = 4;
    g->l[4].next = NULL;
    list_insert(&g->l[4], 3);
    list_insert(&g->l[4], 5);
    list_insert(&g->l[4], 6);
    list_insert(&g->l[4], 7);

    g->l[5].element = 5;
    g->l[5].next = NULL;
    list_insert(&g->l[5], 7);

    g->l[6].element = 6;
    g->l[6].next = NULL;

    g->l[7].element = 7;
    g->l[7].next = NULL;
    list_insert(&g->l[7], 6);

    g->indegree = malloc((g->capacity+1)*sizeof(int));
    if(!g->indegree) {
        printf("%s: %d, out of space\n", __FUNCTION__, __LINE__);
        return;
    }
    memset(g->indegree, 0, g->capacity+1);

    for(i=1; i<g->capacity+1; i++) {
        tmp = g->l[i].next;
        while(tmp) {
            g->indegree[tmp->element]++;
            tmp = tmp->next;
        }
    }
}

int find_zero_indegree(struct graph *g)
{
    int i = 0;

    for(i=1; i<g->capacity+1; i++) {
        if(g->indegree[i] == 0)
            return i;
    }

    return -1;
}
void print_indegree(struct graph *g)
{
    int i = 0;
    printf("Indegree: ");
    for(i=1; i<g->capacity+1; i++) {
        printf("%d: %d\t", i, g->indegree[i]);
    }
    printf("\n");
}

void top_sort(struct graph *g)
{
    int counter;
    int v, w;
    struct list *tmp = NULL;

    printf("Top sort: ");
    for(counter=0; counter<g->capacity; counter++) {
        v = find_zero_indegree(g);
        if(v == -1) {
            printf("Graph has a cycle\n");
            return;
        }
        printf("%d\t", v);
        g->indegree[v]--;
        tmp = g->l[v].next;
        while(tmp) {
            g->indegree[tmp->element]--;
            tmp = tmp->next;
        }
        //print_indegree(g);
    }
}

void dump_graph(struct graph *g)
{
    int i = 0;
    struct list *tmp;

    for(i=1; i<g->capacity+1; i++) {
        tmp = &g->l[i];
        while (tmp){
            printf("%d\t", tmp->element);
            tmp = tmp->next;
        }
        printf("\n");
    }

    printf("Indegree: ");
    for(i=1; i<g->capacity+1; i++) {
        printf("%d: %d\t", i, g->indegree[i]);
    }
    printf("\n");
}

int main(void)
{
    struct graph g;
    g.capacity = 7;
    g.l = malloc(sizeof(struct graph)*(g.capacity+1));
    if(!g.l) {
        printf("%s: %d, out of space\n", __FUNCTION__, __LINE__);
    }
    init(&g);
    dump_graph(&g);
    top_sort(&g);

    return 0;
}