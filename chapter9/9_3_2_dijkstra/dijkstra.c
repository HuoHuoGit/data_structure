#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct list {
    int element;
    int val;
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

void list_insert(struct list *l, int element, int val)
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
    l->next->val = val;
    l->next->next = NULL;
}

void init(struct graph *g)
{
    struct list *tmp;
    int i = 0;

    g->vertex[1].v = 1;
    g->vertex[1].known = 0;
    g->vertex[1].dis = 0;//Start vertex
    g->vertex[1].path = 0;
    g->vertex[1].l.element = 2;
    g->vertex[1].l.val = 2;
    g->vertex[1].l.next = NULL;
    list_insert(&g->vertex[1].l, 4, 1);

    g->vertex[2].v = 2;
    g->vertex[2].known = 0;
    g->vertex[2].dis = INT_MAX;
    g->vertex[2].path = 0;
    g->vertex[2].l.element = 4;
    g->vertex[2].l.val = 3;
    g->vertex[2].l.next = NULL;
    list_insert(&g->vertex[2].l, 5, 10);

    g->vertex[3].v = 3;
    g->vertex[3].known = 0;
    g->vertex[3].dis = INT_MAX;
    g->vertex[3].path = 0;
    g->vertex[3].l.element = 1;
    g->vertex[3].l.val = 4;
    g->vertex[3].l.next = NULL;
    list_insert(&g->vertex[3].l, 6, 5);

    g->vertex[4].v = 4;
    g->vertex[4].known = 0;
    g->vertex[4].dis = INT_MAX;
    g->vertex[4].path = 0;
    g->vertex[4].l.element = 3;
    g->vertex[4].l.val = 2;
    g->vertex[4].l.next = NULL;
    list_insert(&g->vertex[4].l, 5, 2);
    list_insert(&g->vertex[4].l, 6, 8);
    list_insert(&g->vertex[4].l, 7, 4);

    g->vertex[5].v = 5;
    g->vertex[5].known = 0;
    g->vertex[5].dis = INT_MAX;
    g->vertex[5].path = 0;
    g->vertex[5].l.element = 7;
    g->vertex[5].l.val = 6;
    g->vertex[5].l.next = NULL;

    g->vertex[6].v = 6;
    g->vertex[6].known = 0;
    g->vertex[6].dis = INT_MAX;
    g->vertex[6].path = 0;
    g->vertex[6].l.element = 0;
    g->vertex[6].l.val = 0;
    g->vertex[6].l.next = NULL;

    g->vertex[7].v = 7;
    g->vertex[7].known = 0;
    g->vertex[7].dis = INT_MAX;
    g->vertex[7].path = 0;
    g->vertex[7].l.element = 6;
    g->vertex[7].l.val = 1;
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
        printf("\n\t\t");
        tmp = &g->vertex[i].l;
        while (tmp){
            printf("%d\t", tmp->val);
            tmp = tmp->next;
        }
        printf("\n");
        printf("konw: %d\ndis: %d\npath: %d\n", g->vertex[i].known, g->vertex[i].dis, g->vertex[i].path);
        printf("***************\n");
    }
}

void print_path(struct graph *g, int v)
{
    if(g->vertex[v].path != 0) {
        print_path(g, g->vertex[v].path);
        printf(" to ");
    }
    printf("%d", v);
}

int find_smallest_dist(struct graph *g)
{
    int i = 1;
    int smallest_dist = -1;
    int smallest_v = 0;
    for(i=1; i<=g->capacity; i++) {
        if(g->vertex[i].known)
            continue;

        if(smallest_dist==-1 || g->vertex[i].dis<smallest_dist) {
            smallest_dist = g->vertex[i].dis;
            smallest_v = i;
        }
    }

    return smallest_v;
}

void dijkstra(struct graph *g)
{
    int v, w;
    struct list *tmp;

    while (1){
        v = find_smallest_dist(g);
        if(v == 0)
            break;

        g->vertex[v].known = 1;
        tmp = &g->vertex[v].l;
        while(tmp) {
            if(g->vertex[tmp->element].known == 0) {
                if(g->vertex[v].dis + tmp->val < g->vertex[tmp->element].dis) {
                    g->vertex[tmp->element].dis = g->vertex[v].dis + tmp->val;
                    g->vertex[tmp->element].path = v;
                }
            }
            tmp = tmp->next;
        }
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
    int i = 0;

    g.capacity = 7;
    g.vertex = malloc(sizeof(struct vertex)*(g.capacity+1));
    if(!g.vertex) {
        printf("%s: %d, out of space\n", __FUNCTION__, __LINE__);
    }
    memset(g.vertex, 0, sizeof(struct vertex)*(g.capacity+1));
    init(&g);
    dump_graph(&g);
    //unweighted(&g);
    dijkstra(&g);
    //printf("\n++++++++++++++++\n");
    dump_graph(&g);
    printf("Test PRINT:\n");
    for(i=0; i<=g.capacity; i++) {
        print_path(&g, i);
        printf("\n");
    }

    return 0;
}