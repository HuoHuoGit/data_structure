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
    struct list l;
};

struct graph {
    int capacity;
    int *indegree;
    struct vertex *vertex;
};

void list_insert(struct list *l, int element)
{
    if(!l) {
        printf("%s: %d, list is NULL\n", __FUNCTION__, __LINE__);
    }

    while(l->next) {
        l = l->next;
    }
    l->next = malloc(sizeof(struct list));
    if(!l) {
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

    g->vertex[1].v = 1;
    g->vertex[1].known = 0;
    g->vertex[1].dis = INT_MAX;
    g->vertex[1].path = 0;
    g->vertex[1].l.element = 2;
    g->vertex[1].l.next = NULL;
    list_insert(&g->vertex[1].l, 4);

    g->vertex[2].v = 2;
    g->vertex[2].known = 0;
    g->vertex[2].dis = INT_MAX;
    g->vertex[2].path = 0;
    g->vertex[2].l.element = 4;
    g->vertex[2].l.next = NULL;
    list_insert(&g->vertex[2].l, 5);

    g->vertex[3].v = 3;
    g->vertex[3].known = 0;
    g->vertex[3].dis = 0;//Start vertex
    g->vertex[3].path = 0;
    g->vertex[3].l.element = 1;
    g->vertex[3].l.next = NULL;
    list_insert(&g->vertex[3].l, 6);

    g->vertex[4].v = 4;
    g->vertex[4].known = 0;
    g->vertex[4].dis = INT_MAX;
    g->vertex[4].path = 0;
    g->vertex[4].l.element = 3;
    g->vertex[4].l.next = NULL;
    list_insert(&g->vertex[4].l, 5);
    list_insert(&g->vertex[4].l, 6);
    list_insert(&g->vertex[4].l, 7);

    g->vertex[5].v = 5;
    g->vertex[5].known = 0;
    g->vertex[5].dis = INT_MAX;
    g->vertex[5].path = 0;
    g->vertex[5].l.element = 7;
    g->vertex[5].l.next = NULL;

    g->vertex[6].v = 6;
    g->vertex[6].known = 0;
    g->vertex[6].dis = INT_MAX;
    g->vertex[6].path = 0;
    g->vertex[6].l.element = 0;
    g->vertex[6].l.next = NULL;

    g->vertex[7].v = 7;
    g->vertex[7].known = 0;
    g->vertex[7].dis = INT_MAX;
    g->vertex[7].path = 0;
    g->vertex[7].l.element = 6;
    g->vertex[7].l.next = NULL;

    g->indegree = malloc((g->capacity+1)*sizeof(int));
    if(!g->indegree) {
        printf("%s: %d, out of space\n", __FUNCTION__, __LINE__);
        return;
    }
    memset(g->indegree, 0, g->capacity+1);
}

void dump_graph(struct graph *g)
{
    int i = 0;
    struct list *tmp;

    for(i=1; i<g->capacity+1; i++) {
        printf("vertext: %d->\t", g->vertex[i].v);
        tmp = &g->vertex[i].l;
        while (tmp){
            printf("%d\t", tmp->element);
            tmp = tmp->next;
        }
        printf("\n");
        printf("konw: %d\ndis: %d\npath: %d\n", g->vertex[i].known, g->vertex[i].dis, g->vertex[i].path);
        printf("***************\n");
    }
}

void unweighted(struct graph *g)
{
    int curr_dis = 0;
    int i = 1;
    struct list *tmp;

    for(curr_dis=0; curr_dis<g->capacity; curr_dis++) {
        for(i=1; i<g->capacity; i++) {
            if(!g->vertex[i].known && g->vertex[i].dis==curr_dis) {
                g->vertex[i].known = 1;
                tmp = &g->vertex[i].l;
                while (tmp)
                {
                    //if(tmp->element == 0)
                    //    continue;
                    if(g->vertex[tmp->element].dis == INT_MAX) {
                        g->vertex[tmp->element].dis = curr_dis+1;
                        g->vertex[tmp->element].path = g->vertex[i].v;
                    }
                    tmp = tmp->next;
                }
            }
        }
    }
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
    unweighted(&g);
    printf("\n++++++++++++++++\n");
    dump_graph(&g);

    return 0;
}