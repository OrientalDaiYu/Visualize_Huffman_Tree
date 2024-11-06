#include "../include/HuffmanEncoding.h"

// Function to build the Huffman Tree from given data and weights
HuffmanTree BuildHuffmanTree(ElementType *data, int *weight, int size)
{
    HuffmanTree left, right, combine;
    MinHeap minHeap = CreateAndBuildMinHeap(data, weight, size);

    while (minHeap->Size != 1) {
        left = ExtractMin(minHeap); // Extract the minimum element (node) from the heap
        right = ExtractMin(minHeap); // Extract the next minimum element (node) from the heap

        combine = NewNode('$', left->Weight + right->Weight); // Create a new internal node with combined weight
        combine->Left = left; // Set the left child
        combine->Right = right; // Set the right child

        InsertMinHeap(minHeap, combine); // Insert the new node back into the heap
    }

    return ExtractMin(minHeap); // The last remaining node is the root of the Huffman Tree
}

// Function to print the Huffman codes for each character in the tree
void PrintCode(HuffmanTree treeNode, int *code, int depth, int *WPL, int *weight)
{
    if (treeNode->Left) {
        code[depth] = 0; // Set the current bit to 0 for the left child
        PrintCode(treeNode->Left, code, depth + 1, WPL, weight); // Recursively print the left subtree
    }

    if (treeNode->Right) {
        code[depth] = 1; // Set the current bit to 1 for the right child
        PrintCode(treeNode->Right, code, depth + 1, WPL, weight); // Recursively print the right subtree
    }

    if (IsLeaf(treeNode)) { // If the current node is a leaf node
        if (treeNode->Data == '\n' || treeNode->Data == ' ') {
            char *special = (treeNode->Data == '\n' ? "nl" : "sp");
            printf("%s ", special);
        } 
        else 
            printf("%c ", treeNode->Data); // Print the character

        for (int i = 0; i < depth; i++) printf("%d", code[i]); // Print the Huffman code
        printf("\n");

        *WPL += depth * treeNode->Weight; // Calculate the Weighted Path Length (WPL)
    }
}

// Function to perform Huffman encoding and print the results
void HuffmanEncoding(ElementType *data, int *weight, int size) 
{
    HuffmanTree root = BuildHuffmanTree(data, weight, size); // Build the Huffman Tree
    int code[MAX_CODE_LENGTH]; // Array to store the Huffman code
    int depth = 0; // Initial depth
    int WPL = 0; // Weighted Path Length (WPL)

    printf("Result after Huffman encoding: \n");
    PrintCode(root, code, depth, &WPL, weight); // Print the Huffman codes and calculate WPL
    printf("Weighted Path Length (WPL): %d\n", WPL); // Print the WPL

    WriteDotFile(root); // Generate and save the DOT file for visualization
}

// Function to deal with a .txt file 
void ProcessFileAndEncode(const char *filePath) {
    FILE *file = fopen(filePath, "r"); // Open the file
    if (file == NULL) {
        printf("Failed to open the file: %s\n", filePath);
        return;
    }

    int freq[MAX_CHARS] = {0}; // Initialize the character frequency array
    int n = 0; // Count the number of unique characters

    // Read characters from the file and count their frequencies
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        freq[ch]++; // Count the occurrence of each character
    }

    // Close the file after reading
    fclose(file);

    // Prepare data and frequency arrays
    char data[MAX_CHARS];
    int weight[MAX_CHARS];

    // Populate the data and weight arrays with characters and their frequencies
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) { // Only process characters that appeared in the file
            data[n] = (char)i;  // Store the character
            weight[n] = freq[i]; // Store the frequency
            n++;
        }
    }

    // Perform Huffman encoding
    if (n > 0) {
        HuffmanEncoding(data, weight, n);
    } else {
        printf("No characters to encode.\n");
    }
}