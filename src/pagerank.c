#include <math.h>
#include <stdio.h>
#include <string.h>
#include "../headers/pagerank.h"

Vector apply_pagerank(Matrix matrix, double d, double epsilon, int max_iterations) {
  int nodes_count = matrix.colums_number;
  // Initial vector
  Vector v, previous_v;
  double err;

  v.length = nodes_count;
  allocate_vector(&v);
  int i,j;
  double norm;
  
  Matrix transition_matrix = matrix;

  for (i = 0; i < nodes_count; i++) {
    v.array[i] = 1.0 / nodes_count;

    for (j = 0; j < nodes_count; j++) {
      transition_matrix.array[i][j] = transition_matrix.array[i][j] * d + ((1.0 - d) / (double) matrix.colums_number);
    }
  }

  
  for (i = 0; i < max_iterations; i++) {
    previous_v = v;
    v = matrix_dot_vector(transition_matrix, v);
    norm = compute_norm(v);
    double_divide_vector(&v, norm);
    err = 0;

    for (j = 0; j < nodes_count; j++)
      err += fabs(v.array[j] - previous_v.array[j]);
      
    if (err < epsilon) return previous_v;
  }

  return v;
}