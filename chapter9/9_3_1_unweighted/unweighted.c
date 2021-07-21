#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct list {
    int element;
    struct list *next;
};

struct vertex {
    int v;
    int known;
    int dis;
    int path;
    struct list *l;
};

struct graph {
    int capacity;
    int *indegree;
    struct vertex *vertex;
};

void list_insert(struct list *l, int element)
{
    while(l) {
        l = l->next;
    }
    l = malloc(sizeof(struct list));
    if(!l) {
        printf("Out of space\n");
        return;
    }
    l->element = element;
    l->next = NULL;
}

void init(struct graph *g)
{
    struct list *tmp;
    int i = 0;

    g->vertex[1].v = 1;
    g->vertex[1].known = 0;
    g->vertex[1].dis = INT_MAX;
    g->vertex[1].path = 0;
    list_insert(g->vertex[1].l, 2);
    list_insert(g->vertex[1].l, 4);

    g->vertex[2].v = 2;
    g->vertex[2].known = 0;
    g->vertex[2].dis = INT_MAX;
    g->vertex[2].path = 0;
    list_insert(g->vertex[2].l, 4);
    list_insert(g->vertex[2].l, 5);

    g->vertex[3].v = 3;
    g->vertex[3].known = 1;//Start vertex
    g->vertex[3].dis = 0;
    g->vertex[3].path = 0;
    list_insert(g->vertex[3].l, 1);
    list_insert(g->vertex[3].l, 6);

    g->vertex[4].v = 4;
    g->vertex[4].known = 0;
    g->vertex[4].dis = INT_MAX;
    g->vertex[4].path = 0;
    list_insert(g->vertex[4].l, 3);
    list_insert(g->vertex[4].l, 5);
    list_insert(g->vertex[4].l, 6);
    list_insert(g->vertex[4].l, 7);

    g->vertex[5].v = 5;
    g->vertex[5].known = 0;
    g->vertex[5].dis = INT_MAX;
    g->vertex[5].path = 0;
    list_insert(g->vertex[5].l, 7);

    g->vertex[6].v = 6;
    g->vertex[6].known = 0;
    g->vertex[6].dis = INT_MAX;
    g->vertex[6].path = 0;

    g->vertex[7].v = 7;
    g->vertex[7].known = 0;
    g->vertex[7].dis = INT_MAX;
    g->vertex[7].path = 0;
    list_insert(g->vertex[7].l, 6);

    g->indegree = malloc((g->capacity+1)*sizeof(int));
    if(!g->indegree) {
        printf("%s: %d, out of space\n", __FUNCTION__, __LINE__);
        return;
    }
    memset(g->indegree, 0, g->capacity+1);
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

void dump_graph(struct graph *g)
{
    int i = 0;
    struct list *tmp;

    for(i=1; i<g->capacity+1; i++) {
        tmp = g->vertex[i].l;
        while (tmp){
            printf("%d\t", tmp->element);
            tmp = tmp->next;
        }
        printf("\n");
    }

#if 0
    printf("Indegree: ");
    for(i=1; i<g->capacity+1; i++) {
        printf("%d: %d\t", i, g->indegree[i]);
    }
    printf("\n");
#endif
}

int main(void)
{
    struct graph g;
    g.capacity = 7;
    g.vertex = malloc(sizeof(struct vertex)*(g.capacity+1));
    if(!g.vertex) {
        printf("%s: %d, out of space\n", __FUNCTION__, __LINE__);
    }
    memset(g.vertex, 0, sizeof(struct vertex)*(g.capacity+1));
    init(&g);
    dump_graph(&g);

    return 0;
}