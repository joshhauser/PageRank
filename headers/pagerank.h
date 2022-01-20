#ifndef PAGERANK_H
#define PAGERANK_H

#include "../headers/matrix.h"

Vector apply_pagerank(Matrix matrix, double d, double epsilon, int max_iterations, int *iterations_count);
int write_perf(double damping_factor, double elapsed_time, int nodes_count);
#endif