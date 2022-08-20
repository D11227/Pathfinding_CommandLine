#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

void clear_node(Node* node) {
        node->isWall = false;
        node->x = -1;
        node->y = -1;
        node->g = 0;
        node->f = 0.0f;
        node->h = 0.0f;
        node->parentX = -1;
        node->parentY = -1;
}

Node create_node(int x, int y, bool isWall) {
        Node node;
        clear_node(&node);
        node.x = x;
        node.y = y;
        node.isWall = isWall;

        return node;
}

bool compare_equal(Node* a, Node* b) {
        return (a->x == b->x && a->y == b->y);
}
