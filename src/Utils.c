#include <math.h>
#include <stdlib.h>

#include "Node.h"

float heuristic(Node start, Node target) {
        return hypotf(target.x - start.x, target.y - start.y);
}

bool find_node(Node arr[], Node node, unsigned int* length) {
        for (int i = 0; i < (*length); ++i)
                if (compare_equal(&arr[i], &node))
                        return true;
        return false;
}

void push_node(Node arr[], Node node, unsigned int* length) {
        arr[(*length)] = node;
        (*length)++;
}

void remove_node(Node arr[], Node node, unsigned int* length) {
        int index = -1;
        for (int i = 0; i < (*length); ++i)
                if (compare_equal(&arr[i], &node))
                        index = i;
        if (index == -1)
                return;
        clear_node(&arr[index]);
        for(int i = index; i < (*length) - 1; ++i)
                arr[i] = arr[i + 1];
        (*length)--;
}
