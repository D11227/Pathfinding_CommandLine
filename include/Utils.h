#ifndef __UTILS__
#define __UTILS__

#include "Node.h"

float heuristic(Node start, Node end);
bool find_node(Node arr[], Node node, unsigned int* length);

void push_node(Node arr[], Node node, unsigned int* length);
void remove_node(Node arr[], Node node, unsigned int* length);

#endif
