#ifndef PAGERANK_H
#define PAGERANK_H

#include "../headers/matrix.h"

int write_perf(double damping_factor, double elapsed_time, int nodes_count);
Vector apply_pagerank(int triplets_count, int nodes_count, double** triplets, double damping_factor, double epsilon, int max_iterations, int *iterations_count);

#endif