#include "../include/Visualization.h"

// Function to generate the DOT representation of the Huffman Tree
void GenerateDotFile(HuffmanTree root, FILE *dotFile, char *path) {
    if (!root) return;

    // Add label to each node (character + frequency for leaf nodes, frequency for internal nodes)
    if (IsLeaf(root)) {
        // Personalize leaf nodes
        if (root->Data == '\n' || root->Data == ' ') {
            char *special = (root->Data == '\n' ? "nl" : "sp");
            fprintf(dotFile, "\"%p\" [label=< <B><font color=\"red\">%s</font></B><br/>"
                    "<B><font color=\"purple\">%d</font></B><br/>"
                    "<B><font color=\"black\">%s</font></B> >, shape=box];\n",
                    root, special, root->Weight, path);
        }
        else
            fprintf(dotFile, "\"%p\" [label=< <B><font color=\"red\">%c</font></B><br/>"
                    "<B><font color=\"purple\">%d</font></B><br/>"
                    "<B><font color=\"black\">%s</font></B> >, shape=box];\n",
                    root, root->Data, root->Weight, path);
    } else {
        // Set the label for internal nodes                       
        fprintf(dotFile, "    \"%p\" [label=\"%d\", shape=circle];\n", root, root->Weight);
    }

    // Output edges to left and right children, and display the path
    if (root->Left) {
        fprintf(dotFile, "    \"%p\" -> \"%p\" [label=\"0\"];\n", root, root->Left); // Label left child with 0
        char leftPath[MAX_CODE_LENGTH];
        snprintf(leftPath, sizeof(leftPath), "%s0", path); // Append 0 to the path
        GenerateDotFile(root->Left, dotFile, leftPath); // Recursive call for left subtree
    }
    if (root->Right) {
        fprintf(dotFile, "    \"%p\" -> \"%p\" [label=\"1\"];\n", root, root->Right); // Label right child with 1
        char rightPath[MAX_CODE_LENGTH];
        snprintf(rightPath, sizeof(rightPath), "%s1", path); // Append 1 to the path
        GenerateDotFile(root->Right, dotFile, rightPath); // Recursive call for right subtree
    }
}

// Function to write the DOT file for the Huffman Tree
void WriteDotFile(HuffmanTree root) {
    FILE *dotFile = fopen("../Huffman_tree_pictures/Huffman_tree.dot", "w"); // Overwrite existing file
    if (!dotFile) {
        perror("Error opening DOT file");
        return;
    }
    fprintf(dotFile, "digraph G {\n"); // Start of Graphviz graph definition
    char initialPath[MAX_CODE_LENGTH] = ""; // Initialize path as empty
    GenerateDotFile(root, dotFile, initialPath); // Generate DOT content for the tree
    fprintf(dotFile, "}\n"); // End of Graphviz graph definition
    fclose(dotFile);

    printf("Huffman tree visualized as Graphviz DOT file: Huffman_tree.dot\n");
    // Call Graphviz to generate an image from the DOT file
    system("dot -Tpng ../Huffman_tree_pictures/Huffman_tree.dot -o ../Huffman_tree_pictures/Huffman_tree.png");
    system("dot -Tsvg ../Huffman_tree_pictures/Huffman_tree.dot -o ../Huffman_tree_pictures/Huffman_tree.svg");
    system("dot -Tpdf ../Huffman_tree_pictures/Huffman_tree.dot -o ../Huffman_tree_pictures/Huffman_tree.pdf");
}