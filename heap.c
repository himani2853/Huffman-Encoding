#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INT_MIN -1
#define INT_MAX 100000


struct heap{
    int *arr;
    int capacity;
    int heapsize;
};
typedef struct heap *Heap;

void swap(int *a, int *b){
    int temp = *a;
    *a=*b;
    *b=temp;
}

Heap create(int totalsize){
    Heap heap = (Heap)malloc(sizeof(struct heap));
    heap->arr = (int *)malloc(sizeof(int));
    heap->capacity  =totalsize;
    heap->heapsize=0;
    return heap;
}

int parent(int i){
    return ((i-1)/2);
}

int lchild(int i){
    return (2*i+1);
}

int rchild(int i){
    return (2*i+2);
}

void mininsertkey(Heap heap, int element){
    if(heap->heapsize==heap->capacity){
    return;
    }
    heap->heapsize++;
    int i = heap->heapsize-1;
    heap->arr[i]=element;

    while(i!=0 && heap->arr[parent(i)]>heap->arr[i]){
    swap(&(heap->arr[i]),&(heap->arr[parent(i)]));
    i = parent(i);
    }
}

// 5 

void minheapify(int i,Heap heap){
    int l = lchild(i);
    int r = rchild(i);
    if(l>heap->heapsize){
        return;
    }
    if(r>heap->heapsize){
        return;
    }
    int smallest = i;
    if(l<heap->heapsize && heap->arr[l]<heap->arr[i]){
        smallest = l;
    }
    if(r<heap->heapsize && heap->arr[r]<heap->arr[smallest]){
    smallest = r;
    }
    if(smallest!=i){
        swap(&(heap->arr[i]),&(heap->arr[smallest]));
        minheapify(smallest,heap);
    }
}

void extractmin(Heap heap){
    if(heap->heapsize==0){
        return;
        // return INT_MIN;
    }
    if(heap->heapsize==1){
        heap->heapsize--;
        return;
        // return heap->arr[0];
    }
    int root= heap->arr[0];
    heap->arr[0]=heap->arr[(heap->heapsize)-1];
    heap->heapsize--;
    minheapify(0,heap);
    return ;
}


void decreasekey(Heap heap, int i, int newvalue){
        // KEY SHOULD EXIST
    heap->arr[i]=newvalue;
    while(i!=0 && heap->arr[parent(i)]>heap->arr[i]){
    swap(&(heap->arr[i]),&(heap->arr[parent(i)]));
    i=parent(i);
    }
}


int getmin(Heap heap){
    // KEY SHOULD EXIST
    return heap->arr[0];
}


void deletekeymin(Heap heap,int i){
    // KEY SHOULD EXIST
    decreasekey(heap,i,INT_MIN);
    extractmin(heap);
}


int main(){
    Heap heap = (Heap)malloc(sizeof(struct heap));
    int capacity;
    printf("Enter capacity of heap: ");
    scanf("%d",&capacity);
    heap = create(capacity);
    int A[capacity];
    for(int i=0; i<capacity; i++){
    scanf("%d",&A[i]);
    mininsertkey(heap,A[i]);
    }
    for(int i=0 ;i<capacity; i++){
        printf("%d ",heap->arr[i]);
    }
    printf("\n");
    // int k = getmin(heap);
    // printf("%d\n",k);

    extractmin(heap);
    for(int i=0 ;i<heap->heapsize; i++){
        printf("%d ",heap->arr[i]);
    }
    printf("\n");
    // printf("%d\n",extractmin(heap));
    // decreasekey(heap,2,6);
    deletekeymin(heap,2);
    for(int i=0 ;i<heap->heapsize; i++){
        printf("%d ",heap->arr[i]);
    }
    printf("\n");
        return 0;
}