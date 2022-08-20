#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "Grid.h"
#include "Node.h"

void initialize_grid() {
        const char* name_file = "files/input.txt";

        FILE* file = fopen(name_file, "r");

        get_size_grid(file);
        read_file_grid(file);

        fclose(file);
}

int main(int argc, char const *argv[]) {
        initialize_grid();

        Node open[grid.width * grid.height];
        Node closed[grid.width * grid.height];
        Node path[grid.width * grid.height];

        int open_size = 0, closed_size = 0, path_size = 0;
        bool startFinding = true;

        while (open_size > 0 || startFinding) {
                Node current = open[0];
                for (int i = 1; i < open_size; ++i)
                        if (open[i].f < current.f)
                                current = open[i];

                if (compare_equal(&current, &target)) {
                        current = get_node(target.x, target.y);

                        while (!compare_equal(&current, &start)) {
                                push_node(path, current, &path_size);
                                current = get_node(current.parentX, current.parentY);
                        }

                        startFinding = false;
                        break;
                }

                if (open_size != 0) remove_node(open, current, &open_size);
                push_node(closed, current, &closed_size);

                Node neighbors[8]; // 8 directions
                int neighbors_size = 0;

                for (int y = -1; y <= 1; ++y) {
                        for (int x = -1; x <= 1; ++x) {
                                if (x == 0 && y == 0) continue;

                                int checkX = current.x + x;
                                int checkY = current.y + y;

                                if (checkX >= 0 && checkX < grid.width && checkY >= 0 && checkY < grid.height)
                                        push_node(neighbors, get_node(checkX, checkY), &neighbors_size);
                        }
                }

                for (int i = 0; i < neighbors_size; ++i) {
                        Node neighbor = neighbors[i];
                        if (neighbor.isWall || find_node(closed, neighbor, &closed_size))
                                continue;

                        int newCost = current.g + heuristic(current, neighbor);
                        if (newCost < neighbor.g || !find_node(open, neighbor, &open_size)) {
                                neighbor.g = newCost;
                                neighbor.h = heuristic(neighbor, target);
                                neighbor.f = neighbor.g + neighbor.h;

                                set_parent(neighbor, current);

                                if (!find_node(open, neighbor, &open_size))
                                        push_node(open, neighbor, &open_size);
                        }
                }
        }

        char output_file[grid.width * grid.height];

        for (int y = 0; y < grid.height; ++y) {
                for (int x = 0; x < grid.width; ++x) {
                        output_file[y * grid.width + x] = (get_node(x, y).isWall)
                                                          ? '1' : '0';
                }
        }

        for (int i = 0; i < path_size; ++i)
                output_file[path[i].y * grid.width + path[i].x] = '#';

        output_file[start.y * grid.width + start.x] = 'S';
        output_file[target.y * grid.width + target.x] = 'T';

        for (int y = 0; y < grid.height; ++y) {
                for (int x = 0; x < grid.width; ++x) {
                        char c = output_file[y * grid.width + x];
                        printf("%s%c\033[0m", (
                                (c == '#')
                                ? "\033[1;31m"
                                : (c == 'S')
                                ? "\033[1;32m"
                                : (c == 'T')
                                ? "\033[1;36m"
                                : (c == '1')
                                ? "\033[1;35m"
                                : "\033[1;m"
                        ), c);
                }
                printf("\n");
        }

        write_file_grid(output_file);

        free_grid();

        const char string[] = "Pathfinding in C commandline, Written by SilverbossTD (Thanh Duy)\n";
        const unsigned int string_size = sizeof(string);
        unsigned ret;
        asm volatile
        (
                "movl $1, %%eax\n\t"
                "movl $1, %%edi\n\t"
                "movq %1, %%rsi\n\t"
                "movl %2, %%edx\n\t"
                "syscall"
                : "=&a"(ret)
                : "g"(string), "g"(string_size)
                : "%rdi", "%rsi", "%rdx", "%rcx", "%r11"
        );
        return 0;
}
