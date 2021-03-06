#ifndef PAGERANK_H
#define PAGERANK_H

#include "../headers/matrix.h"

int write_perf(char* graph_name, double damping_factor, double elapsed_time, int nodes_count, int edges_count);
Vector apply_pagerank(int triplets_count, int nodes_count, double** triplets, double damping_factor, double epsilon, int max_iterations, int *iterations_count);

#endif