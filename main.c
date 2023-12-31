#include"huffman.h"

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

