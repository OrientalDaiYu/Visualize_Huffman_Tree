#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "MinHeap.h"

void GenerateDotFile(HuffmanTree root, FILE *dotFile, char *path);
void WriteDotFile(HuffmanTree root);

#endif