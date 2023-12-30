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
    struct node **array;
};
typedef struct node_heap *Node_Heap;

Node new_node(int frequency, char alphabet)
{
    Node temp = (Node)malloc(sizeof(struct node));
    temp->alphabet = alphabet;
    temp->frequency = frequency;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Node_Heap create_heap(int totalsize)
{
    Node_Heap heap = (Node_Heap)malloc(sizeof(struct node_heap));
    heap->node_heap_capacity = totalsize;
    heap->node_heap_size = 0;
    heap->array = (Node *)malloc((heap->node_heap_capacity) * (sizeof(struct node)));
    return heap;
}

int parent(int i)
{
    return ((i - 1) / 2);
}

int lchild(int i)
{
    return (2 * i + 1);
}

int rchild(int i)
{
    return (2 * i + 2);
}

void swap_nodes(Node *a, Node *b){
    Node temp = *a;
    *a=*b;
    *b=temp;
}

void minheapify(int index, Node_Heap heap)
{
    int l = lchild(index);
    int r = rchild(index);
    if (l > heap->node_heap_size)
    {
        return;
    }
    if (r > heap->node_heap_size)
    {
        return;
    }
    int smallest = index;
    if (l < heap->node_heap_size && heap->array[l]->frequency < heap->array[r]->frequency)
    {
        smallest = l;
    }
    if (r < heap->node_heap_size && heap->array[r]->frequency < heap->array[smallest]->frequency)
    {
        smallest = r;
    }
    if (smallest != index)
    {
        swap_nodes(&(heap->array[index]), &(heap->array[smallest]));
        minheapify(smallest, heap);
    }
}

bool size_one(Node_Heap heap)
{
    if (heap->node_heap_size == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Node extractmin(Node_Heap heap)
{
    // if(heap->node_heap_size==0){
    //     return;

    // }
    if (heap->node_heap_size == 1)
    {
        heap->node_heap_size--;
        return heap->array[0];
    }

    Node temp = heap->array[0];
    heap->array[0] = heap->array[(heap->node_heap_size) - 1];
    heap->node_heap_size--;
    minheapify(0, heap);
    return temp;
}

void mininsertkey(Node_Heap heap, Node insert_node)
{
    if (heap->node_heap_size == heap->node_heap_capacity)
    {
        return;
    }

    heap->node_heap_size++;
    int i = heap->node_heap_size - 1;

    while (i != 0 && heap->array[parent(i)]->frequency > insert_node->frequency)
    {
        // swap(&(heap->arr[i]),&(heap->array[parent(i)]));
        heap->array[i] = heap->array[parent(i)];
        i = parent(i);
    }
    heap->array[i] = new_node(insert_node->frequency, insert_node->alphabet);

    // heap->array[i] = insert_node;
}

void build_the_heap(Node_Heap heap)
{
    int n = heap->node_heap_size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        minheapify(i, heap);
    }
}

bool is_the_node_leaf(Node to_check)
{
    if (to_check->left == NULL && to_check->right == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Node_Heap creating_building_heap(int freq[], char letter[], int size)
{
    Node_Heap heap = create_heap(size);
    for (int i = 0; i < size; i++)
    {
        heap->array[i] = new_node(freq[i], letter[i]);
    }
    heap->node_heap_size = size;
    build_the_heap(heap);
    return heap;
}

Node huffman_tree(char letter[], int freq[], int size)
{
    Node internal_left, internal_right, internal_node;
    Node_Heap heap = creating_building_heap(freq, letter, size);
    while (size_one(heap) != true)
    {
        internal_left = extractmin(heap);
        internal_right = extractmin(heap);
        internal_node = new_node(internal_left->frequency + internal_right->frequency, ' ');
        internal_node->left = internal_left;
        internal_node->right = internal_right;
        mininsertkey(heap, internal_node);
    }
    return extractmin(heap);
}

void final_codes(Node final, int output[], int index)
{
    int i = index;
    if (final->left != NULL)
    {
        output[i] = 0;
        final_codes(final->left, output, i + 1);
    }

    if (final->right != NULL)
    {
        output[i] = 1;
        final_codes(final->right, output, i + 1);
    }

    if (is_the_node_leaf(final) == true)
    {
        printf("%c", final->alphabet);
        for (int k = 0; k < i; k++)
        {
            printf("%d", output[k]);
        }
        printf("\n");
    }
}


void Huffman_encoding(char letter[], int freq[], int totalsize)
{
    Node answer = huffman_tree(letter, freq, totalsize);
    int output[1000];
    int index = 0;
    final_codes(answer, output,index);
}

int main()
{
    int size;
    scanf("%d",&size);
    int input_freq[size];
    char input_alpha[size];
    for(int i =0; i<size; i++)
    {
        scanf(" %c %d",&input_alpha[i],&input_freq[i]);
    }
    Huffman_encoding(input_alpha,input_freq,size);

    return 0;
}
