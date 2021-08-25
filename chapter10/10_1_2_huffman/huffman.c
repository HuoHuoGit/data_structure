#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "huffman.h"
#include "binheap.h"

void init(struct huffman_node **h, int size)
{
    h[0]->c = 'a';
    h[0]->count = 10;

    h[1]->c = 'e';
    h[1]->count = 15;

    h[2]->c = 'i';
    h[2]->count = 12;

    h[3]->c = 's';
    h[3]->count = 3;

    h[4]->c = 't';
    h[4]->count = 4;

    h[5]->c = ' ';
    h[5]->count = 13;

    h[6]->c = '\n';
    h[6]->count = 1;
}

struct huffman_node *union_huffman(struct huffman_node *a, struct huffman_node *b)
{
    struct huffman_node *parent = malloc(sizeof(struct huffman_node));
    if(!parent) {
        printf("Out of space\n");
    }
    parent->c = '*';
    parent->left = a;
    parent->right = b;
    parent->count = a->count + b->count;

    return parent;
}

void printf_huffman(struct huffman_node *node, int code)
{
    if(!node)
        return;

    //if(!node->left && !node->right) {
    //    printf("character: %c, count %d, code: %d\n", node->c, node->count);
    //    return;
    //}

    if(node->left)
        printf_huffman(node->left, code*2);
    if(node->right)
        printf_huffman(node->right, (code*2)+1);

    printf("character: %c, count %d, code: 0x%x\n", node->c, node->count, code);
}

int main(void)
{
    struct huffman_node *h[7];
    struct huffman_node *tmp = NULL;
    int i = 0;
    PriorityQueue Queue = Initialize(15);

    for(i=0; i<7; i++) {
        h[i] = malloc(sizeof(struct huffman_node));
        if(h[i])
            memset(h[i], 0, sizeof(struct huffman_node));
    }
    init(h, 7);

    for(i=0; i<7; i++) {
        Insert(h[i], Queue);
    }

    for(i=0; i<7; i++) {
        printf("character: %c, count:%d\n", Queue->Elements[i+1]->c, Queue->Elements[i+1]->count);
    }
    struct huffman_node *tmp_a = NULL;
    struct huffman_node *tmp_b = NULL;
    while(Queue->Size > 1) {
        tmp_a = DeleteMin(Queue);
        tmp_b = DeleteMin(Queue);
        tmp = union_huffman(tmp_a, tmp_b);
        Insert(tmp, Queue);
    }
    //tmp = DeleteMin(queue);
    printf("------------------------\n");
    int a = 1;
    printf_huffman(Queue->Elements[1], 0);


#if 0
    for(i=0; i<7; i++) {
        tmp = DeleteMin(queue);
        if(tmp) {
            printf("character: %c, count:%d\n", tmp->c, tmp->count);
        }
    }
#endif

    memset(h, 0, 7*sizeof(struct huffman_node));
}