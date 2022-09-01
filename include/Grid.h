#ifndef __GRID__
#define __GRID__

#include <stdio.h>
#include "Node.h"

typedef struct Grid {
        struct Node *values;
        unsigned int width;
        unsigned int height;
} Grid;

Grid grid;

Node get_node(unsigned int x, unsigned int y);
void get_size_grid(FILE* file);
void read_file_grid(FILE *file);
void write_file_grid(char output[]);
void free_grid();
void set_parent(Node child, Node parent);

#endif
