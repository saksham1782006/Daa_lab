#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Node of Huffman Tree
struct Node {
    char data;
    int freq;

    struct Node *left;
    struct Node *right;
};

// Create a new node
struct Node* createNode(char data, int freq)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->data = data;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Find the two nodes with minimum frequency
void findMinNodes(struct Node* nodes[], int n, int *min1, int *min2)
{
    *min1 = -1;
    *min2 = -1;

    for (int i = 0; i < n; i++) {

        if (nodes[i] == NULL)
            continue;

        if (*min1 == -1 || nodes[i]->freq < nodes[*min1]->freq) {
            *min2 = *min1;
            *min1 = i;
        }
        else if (*min2 == -1 || nodes[i]->freq < nodes[*min2]->freq) {
            *min2 = i;
        }
    }
}

// Generate Huffman Codes
void generateCodes(struct Node* root, char code[], int depth)
{
    if (root == NULL)
        return;

    // Leaf node
    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';

        printf("%c\t%d\t%s\n",
               root->data,
               root->freq,
               code);

        return;
    }

    // Left = 0
    code[depth] = '0';
    generateCodes(root->left, code, depth + 1);

    // Right = 1
    code[depth] = '1';
    generateCodes(root->right, code, depth + 1);
}

// Free Huffman Tree
void freeTree(struct Node* root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

int main()
{
    int n;

    printf("Enter number of characters: ");
    scanf("%d", &n);

    struct Node* nodes[MAX];

    printf("\nEnter character and frequency:\n");

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;

        scanf(" %c %d", &ch, &freq);

        nodes[i] = createNode(ch, freq);
    }

    int count = n;

    // Build Huffman Tree
    while (count > 1) {

        int min1, min2;

        findMinNodes(nodes, count, &min1, &min2);

        struct Node* left = nodes[min1];
        struct Node* right = nodes[min2];

        // Create parent node
        struct Node* parent =
            createNode('$',
                       left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        // Remove the two minimum nodes
        nodes[min1] = parent;

        // Shift remaining nodes
        nodes[min2] = nodes[count - 1];

        count--;
    }

    struct Node* root = nodes[0];

    char code[MAX];

    printf("\nHuffman Codes:\n");
    printf("Character\tFrequency\tCode\n");
    printf("-----------------------------------\n");

    generateCodes(root, code, 0);

    freeTree(root);

    return 0;
}
