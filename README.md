# Huffman-Encoding
Huffman encoding is a variable-length prefix coding algorithm used for lossless data compression. It assigns shorter binary codes to more frequently occurring symbols, optimizing the representation of data and reducing overall storage or transmission requirements.

1) Node Structure and Heap Initialization:
    The code defines a struct node to represent nodes of a binary tree used for Huffman coding. Each node contains an alphabet character, frequency, and pointers to left and right children.
    Another structure struct node_heap is defined to represent a min-heap of these nodes. It includes an array of nodes, heap size, and heap capacity.

2) Heap Operations:
    The code implements standard heap operations such as creating a heap, finding parent and child indices, swapping nodes, heapifying (maintaining the heap property), extracting the minimum node from the heap, and inserting a node into the heap.

3) Huffman Tree Construction:
    The huffman_tree function takes arrays of characters and their frequencies, builds a min-heap, and constructs a Huffman tree by repeatedly extracting two nodes with the minimum frequencies, creating a new internal node with a frequency equal to the sum of the extracted nodes, and inserting the new node back into the heap. This process continues until only one node (the root of the Huffman tree) remains in the heap.

4) Code Generation:
    The final_codes function recursively traverses the Huffman tree to generate binary codes for each alphabet character. It prints the mapping of each character to its binary code.

5) Huffman Encoding:
    The Huffman_encoding function orchestrates the Huffman encoding process. It calls huffman_tree to get the root of the Huffman tree and then uses final_codes to print the binary codes for each character.

6) Main Function:
    The main function reads the size of the input, an array of characters, and their frequencies. It then calls Huffman_encoding to print the Huffman codes for each character based on their frequencies.
    In summary, the code demonstrates the construction of a Huffman tree and the generation of Huffman codes for a given set of characters and their frequencies using a min-heap.