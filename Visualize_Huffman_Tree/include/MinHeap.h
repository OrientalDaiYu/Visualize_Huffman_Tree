#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARS 128
#define MAX_CODE_LENGTH 100

typedef char ElementType;
typedef struct HTNode * HuffmanTree;
struct HTNode {
    ElementType Data;
    int Weight;
    HuffmanTree Left, Right;
};

typedef struct HNode * MinHeap;
struct HNode {
    HuffmanTree *Array;
    int Capacity;
    int Size;
};

HuffmanTree NewNode(ElementType data, int weight);
MinHeap CreateMinHeap(int capacity);
void BuildMinHeap(MinHeap minHeap);
void InsertMinHeap(MinHeap minHeap, HuffmanTree treeNode);
HuffmanTree ExtractMin(MinHeap minHeap);
void SwapHuffmanTreeNode(HuffmanTree *a, HuffmanTree *b);
void PercolateDown(MinHeap minHeap, int index);
MinHeap CreateAndBuildMinHeap(ElementType *data, int *weight, int size);
int IsLeaf(HuffmanTree treeNode);

#endif