#include <math.h>
#include "../headers/pagerank.h"

Vector apply_pagerank(Matrix matrix, double d, double epsilon, int max_iterations) {
  int nodes_count = matrix.colums_number;
  // Initial vector
  Vector v, previous_v;
  v.length = nodes_count;
  allocate_vector(&v);
  int converge = -1;
  int err;
  int i,j;
  double norm;
  

  Matrix transition_matrix = matrix;

  for (i = 0; i < nodes_count; i++) {
    for (j = 0; j < nodes_count; j++) {
      transition_matrix.array[i][j] *= d + ((1.0 - d) / (double) nodes_count);
    }
  }

  /**
   * TODO:
   * - add computing method for matrices/vector addition
   * 
   */
  for (i = 0; i < max_iterations; i++) {
    previous_v = v;
    v = matrix_dot_vector(transition_matrix, v);
    norm = compute_norm(v);
    double_divide_vector(&v, norm);
    
    err = 0;

    for (j = 0; j < nodes_count; j++)
      err += fabs(v.array[j] - previous_v.array[j]);

    if (err < epsilon) return v;
  }

  return v;
}