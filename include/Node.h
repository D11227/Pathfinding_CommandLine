#ifndef __NODE__
#define __NODE__

#include <stdbool.h>

typedef struct Node {
        bool isWall;
        float f;
        float h;
        int x;
        int y;
        int g;
        int parentX;
        int parentY;
} Node;

Node start, target;
Node create_node(int x, int y, bool isWall);
void clear_node(Node* node);
bool compare_equal(Node* a, Node *b);

#endif
