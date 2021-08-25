#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

struct huffman_node {
    char c;
    int count;
    struct huffman_node *left;
    struct huffman_node *right;
};


#endif