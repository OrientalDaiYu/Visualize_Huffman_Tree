#include "../include/HuffmanEncoding.h"

// Main function to read input and perform Huffman encoding
int main()
{   
    /* Input data and frequency manually */
    // int n; 
    // // Read the number of elements
    // printf("Input the number of characters you want to encode:\n");
    // scanf("%d", &n); 

    // // Allocate arrays for data and weights
    // ElementType data[n];
    // int weight[n];

    // // Read the data and weights
    // printf("Input the characters and their frequency(weight) in pairs each line: \n");
    // for (int i = 0; i < n; i++)
    //     scanf(" %c %d", &data[i], &weight[i]);
    
    // // Perform Huffman encoding
    // HuffmanEncoding(data, weight, n);

    /* test for processing a `.txt` file */
    const char *filePath = "../text_for_demo/Moving forward through THE EPIC ROAD.txt";
    ProcessFileAndEncode(filePath);

    return 0;
}