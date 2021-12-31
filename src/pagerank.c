#include "../headers/matrix.h"


Vector apply_pagerank(Matrix matrix, int d, int epsilon) {
  int nodes_count = matrix.colums_number;
  // Initial vector
  Vector v;
  v.length = nodes_count;
  allocate_vector(&v);
  int converge = -1;

  int i;

  Vector damping_vector;
  damping_vector.length = nodes_count;
  allocate_vector(&damping_vector);

  for (i = 0; i < nodes_count; i++) {
    v.array[i] = 1/v.length;
    damping_vector.array[i] = d;
  }

  /**
   * TODO:
   * - add computing method for matrices/vector addition
   * 
   */
  // while (!converge) {
  //   v = matrix_dot_vector(matrix, v);
  //   /**
  //    * TODO:
  //    * - compute norm then do v/norm
  //    * 
  //    */

  // }

  return v;
}