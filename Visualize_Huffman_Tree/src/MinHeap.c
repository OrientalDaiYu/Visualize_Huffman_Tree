#include "../include/MinHeap.h"

// Function to create a new Huffman Tree node
HuffmanTree NewNode(ElementType data, int weight) 
{
    // Allocate memory for the new node
    HuffmanTree node = (HuffmanTree)malloc(sizeof(struct HTNode));
    // Initialize the left and right children to NULL
    node->Left = node->Right = NULL;
    // Set the data and weight of the node
    node->Data = data;
    node->Weight = weight;

    return node;
}

// Function to create a new Min Heap with a specified capacity
MinHeap CreateMinHeap(int capacity)
{
    // Allocate memory for the Min Heap structure
    MinHeap minHeap = (MinHeap)malloc(sizeof(struct HNode));
    // Initialize the size to 0 and set the capacity
    minHeap->Size = 0;
    minHeap->Capacity = capacity;
    // Allocate memory for the array of HuffmanTree nodes
    minHeap->Array = (HuffmanTree *)calloc(minHeap->Capacity, sizeof(HuffmanTree));

    return minHeap;
}

// Function to build the Min Heap from the array of elements
void BuildMinHeap(MinHeap minHeap)
{
    // Calculate the last non-leaf node index
    int n = minHeap->Size - 1;
    // Start from the last non-leaf node and percolate down each node
    for (int i = (n - 1) / 2; i >= 0; i--)
        PercolateDown(minHeap, i);
}

// Function to insert a new node into the Min Heap
void InsertMinHeap(MinHeap minHeap, HuffmanTree treeNode)
{
    // Increment the size of the heap and find the insertion point
    int i = ++(minHeap->Size) - 1;
    
    // Percolate up to maintain the heap property
    for (; i && treeNode->Weight < minHeap->Array[(i - 1) / 2]->Weight; i = (i - 1) / 2)
        minHeap->Array[i] = minHeap->Array[(i - 1) / 2];

    // Place the new node at the correct position
    minHeap->Array[i] = treeNode;
}

// Function to extract the minimum element from the Min Heap
HuffmanTree ExtractMin(MinHeap minHeap)
{
    // Store the root node (minimum element)
    HuffmanTree minimum = minHeap->Array[0];
    // Move the last element to the root and reduce the heap size
    minHeap->Array[0] = minHeap->Array[minHeap->Size - 1];
    minHeap->Size--;
    // Percolate down to maintain the heap property
    PercolateDown(minHeap, 0);

    return minimum;
}

// Function to swap two Huffman Tree nodes
void SwapHuffmanTreeNode(HuffmanTree *a, HuffmanTree *b) 
{
    // Temporary variable to hold one of the nodes
    HuffmanTree tmp = *a;
    // Swap the nodes
    *a = *b;
    *b = tmp;
}

// Function to percolate down the element at the specified index in the Min Heap
void PercolateDown(MinHeap minHeap, int index)
{
    /* Non-recursive method */
    int parent, child;
    HuffmanTree tmp;

    // Store the current node to be percolated down
    tmp = minHeap->Array[index];

    // Loop until the current node is in the correct position
    for (parent = index; (parent * 2 + 1) < minHeap->Size; parent = child) {
        // Find the left child index
        child = parent * 2 + 1;
        // If there is a right child and it is smaller than the left child, use the right child
        // If child == minHeap->Size - 1, it means the parent node only has a left child
        if ((child != minHeap->Size - 1) && (minHeap->Array[child]->Weight > minHeap->Array[child + 1]->Weight))
            child++; // Find the minimum between left and right children

        // If the current node is already in the correct position, break the loop
        if (tmp->Weight <= minHeap->Array[child]->Weight) break;
        // Otherwise, move the child node up
        else minHeap->Array[parent] = minHeap->Array[child];
    }
    // Place the current node in the correct position
    minHeap->Array[parent] = tmp;

    // /* Recursive method */
    // int smallest = index;
    // int left = 2 * index + 1;
    // int right = 2 * index + 2;

    // if (left < minHeap->Size && minHeap->Array[left]->Weight < minHeap->Array[smallest]->Weight)
    //     smallest = left;

    // if (right < minHeap->Size && minHeap->Array[right]->Weight < minHeap->Array[smallest]->Weight)
    //     smallest = right;

    // if (smallest != index) {
    //     SwapHuffmanTreeNode(&minHeap->Array[smallest], &minHeap->Array[index]);
    //     PercolateDown(minHeap, smallest);
    // }
}

// Function to create and build a Min Heap from the given data and weights
MinHeap CreateAndBuildMinHeap(ElementType *data, int *weight, int size)
{
    // Create a new Min Heap with the specified size
    MinHeap minHeap = CreateMinHeap(size);
    // Populate the heap array with new nodes
    for (int i = 0; i < size; i++)
        minHeap->Array[i] = NewNode(data[i], weight[i]);

    // Set the size of the heap and build the heap
    minHeap->Size = size;
    BuildMinHeap(minHeap);

    return minHeap;
}

// Function to check if a node is a leaf node
int IsLeaf(HuffmanTree treeNode)
{
    // Return true if the node has no left or right children
    return !(treeNode->Left || treeNode->Right);
}