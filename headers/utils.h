#ifndef UTILS_H
#define UTILS_H

#include "../headers/graph.h"

int index_in_vertices_array(Vertice *array, int array_length, int searched);
int index_in_int_array(int *array, int array_length, int searched);
int compare_doubles(const void* first, const void* second);

#endif