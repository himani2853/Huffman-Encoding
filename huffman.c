#include"huffman.h"
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
    heap->array = (Node *)malloc((heap->node_heap_capacity) * (sizeof(Node)));
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

void swap_nodes(Node *a, Node *b)
{
    Node temp = *a;
    *a=*b;
    *b=temp;
}

void minheapify(int index, Node_Heap heap)
{
    int l = lchild(index);
    int r = rchild(index);
    int smallest = index;
    if (l < heap->node_heap_size && heap->array[l]->frequency < heap->array[smallest]->frequency)
    {
        smallest = l;
    }
    if (r < heap->node_heap_size && heap->array[r]->frequency < heap->array[smallest]->frequency)
    {
        smallest = r;
    }
    if (smallest != index)
    {
        swap_nodes(&(heap->array[smallest]), &(heap->array[index]));
        minheapify(smallest, heap);
    }
}


Node extractmin(Node_Heap heap)
{

    Node temp = heap->array[0];
    heap->array[0] = heap->array[(heap->node_heap_size) - 1];
    heap->node_heap_size--;
    minheapify(0, heap);
    return temp;
}

void mininsertkey(Node_Heap heap, Node insert_node)
{

    heap->node_heap_size++;
    int i = heap->node_heap_size - 1;
    while (i != 0 && heap->array[parent(i)]->frequency > insert_node->frequency)
    {
        heap->array[i] = heap->array[parent(i)];
        i = parent(i);
    }

    heap->array[i] = insert_node;
}

void build_the_heap(Node_Heap heap)
{
    int n = heap->node_heap_size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        minheapify(i, heap);
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
    while(heap->node_heap_size!=1)
    {
        internal_left = extractmin(heap);
        internal_right = extractmin(heap);
        internal_node = new_node(internal_left->frequency + internal_right->frequency, '?');
        internal_node->left = internal_left;
        internal_node->right = internal_right;
        mininsertkey(heap, internal_node);
    }
    return extractmin(heap);
}

void final_codes(Node final, int *output, int index)
{
    if (final->left != NULL)
    {
        output[index] = 0;
        final_codes(final->left, output, index + 1);
    }

    if (final->right != NULL)
    {
        output[index] = 1;
        final_codes(final->right, output, index + 1);
    }

    if(final->left==NULL && final->right==NULL)
    {
        printf("%c maps to: ", final->alphabet);
        for (int k = 0; k < index; k++)
        {
            printf("%d", output[k]);
        }
        printf("\n");
    }
}


void Huffman_encoding(char letter[], int freq[], int totalsize)
{
    Node answer = huffman_tree(letter, freq, totalsize);
    int *output = (int *)malloc(1000*sizeof(int));
    int index = 0;
    final_codes(answer, output,index);
    free(output);
    
}
