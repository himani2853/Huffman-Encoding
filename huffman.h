#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct node
{
    int frequency;
    char alphabet;
    struct node *left;
    struct node *right;
};
typedef struct node *Node;

struct node_heap
{
    int node_heap_size;
    int node_heap_capacity;
    Node *array;
};
typedef struct node_heap *Node_Heap;

Node new_node(int frequency, char alphabet);

Node_Heap create_heap(int totalsize);

int parent(int i);

int lchild(int i);

int rchild(int i);

void swap_nodes(Node *a, Node *b);

void minheapify(int index, Node_Heap heap);

Node extractmin(Node_Heap heap);

void mininsertkey(Node_Heap heap, Node insert_node);

void build_the_heap(Node_Heap heap);

Node_Heap creating_building_heap(int freq[], char letter[], int size);

Node huffman_tree(char letter[], int freq[], int size);

void final_codes(Node final, int *output, int index);

void Huffman_encoding(char letter[], int freq[], int totalsize);