#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Grid.h"

Node get_node(unsigned int x, unsigned int y) {
        return grid.values[y * grid.width + x];
}

void get_size_grid(FILE* file) {
        char c = '\0';
        unsigned int width = 0, height = 0;

        for (; (c = fgetc(file)) && (c != '\n' && !feof(file)); ++width);

        rewind(file);

        while ((c = fgetc(file)) && !feof(file))
                if (c == '\n')
                        ++height;
        grid.width = width;
        grid.height = height;
}

void read_file_grid(FILE *file) {
        grid.values = calloc(grid.width * grid.height, sizeof(Node));
        char c = '\0';

        rewind(file);

        for (unsigned int y = 0; y < grid.height; ++y) {
                for (unsigned int x = 0; (c = fgetc(file)) && !feof(file) && x < grid.width; ++x) {
                        if (c == 'S') start = create_node(x, y, false);
                        else if (c == 'T') target = create_node(x, y, false);
                         grid.values[y * grid.width + x] = create_node(x, y, (c == '1') ? true : false);
                }
        }
}

void write_file_grid(char output[]) {
	FILE *file = fopen("files/output.txt", "w");

	for(unsigned int y = 0; y < grid.height; y++) {
		for(unsigned int x = 0; x < grid.width; x++) {
			fputc(output[y * grid.width + x], file);
		}
		fputc('\n', file);
	}

	fclose(file);
}

void free_grid() {
        grid.width = 0;
        grid.height = 0;
        free(grid.values);
}

void set_parent(Node child, Node parent) {
        grid.values[child.y * grid.width + child.x].parentX = parent.x;
        grid.values[child.y * grid.width + child.x].parentY = parent.y;
}
