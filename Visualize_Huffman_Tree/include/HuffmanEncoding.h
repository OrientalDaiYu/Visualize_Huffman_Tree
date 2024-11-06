#ifndef HuffmanTREE_H
#define HuffmanTREE_H

#include "MinHeap.h"
#include "Visualization.h"

HuffmanTree BuildHuffmanTree(ElementType *data, int *weight, int size);
void PrintCode(HuffmanTree treeNode, int *code, int depth, int *WPL, int *weight);
void HuffmanEncoding(ElementType *data, int *weight, int size);
void ProcessFileAndEncode(const char *filePath);

#endif