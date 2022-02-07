#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/pagerank.h"


/**
 * @brief Write the number of iterations
 * necessary to find the eigen vector
 * for a given damping factor
 * 
 * @param damping_factor the damping factor used for
 * pagerank algorithm
 * @param elapsed_time the time between beginning
 * and ending of the PageRank algorithm execution
 * @param nodes_count the number of nodes for
 * the graph used in the current execution
 * @return int -1 in case of errors, otherwise the
 * number of written characcters
 */
int write_perf(double damping_factor, double elapsed_time, int nodes_count) {
  char *file_path = "output/performance.txt";
  FILE *file_pointer = fopen(file_path, "a");
  int written_chars_count = 0;

  if (file_pointer == NULL) {
    printf("Impossible d'ouvrir le fichier %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  written_chars_count = fprintf(file_pointer, "%d; %lf; %lf\n", nodes_count, damping_factor, elapsed_time);
  fclose(file_pointer);

  return written_chars_count;
}

/**
 * @brief Apply PageRank algorithm
 * 
 * @param triplets_count the number of triplets
 * @param nodes_count the number of nodes for the graph
 * on which PageRank is applied
 * @param triplets a list of triplets
 * used to represent a hollow matrix,
 * each triplet has this shape: [column, line, value]
 * @param damping_factor the damping factor used for PageRank
 * @param epsilon the maximum gap between to iterations,
 * which defines the stability of the eigen vector
 * @param max_iterations the maximum iterations
 * @param iterations_count the number of passed iterations
 * @return Vector the eigen vector
 */
Vector apply_pagerank(int triplets_count, int nodes_count, double** triplets, double damping_factor, double epsilon, int max_iterations, int *iterations_count) {
  Vector eigen_vector, previous_ev, zeros;
  double err;
  int i,j;

  eigen_vector.length = zeros.length = nodes_count;
  allocate_vector(&eigen_vector);
  allocate_vector(&zeros);

  for (i = 0; i < eigen_vector.length; i++)
    eigen_vector.array[i] = 1.0 / (double) nodes_count;

  for (j = 0; j < max_iterations; j++) {
    previous_ev = eigen_vector;
    eigen_vector = matrix_dot_vector(triplets, eigen_vector, triplets_count);

    err = 0.0;
    for (i = 0; i < nodes_count; i++) {
      eigen_vector.array[i] = eigen_vector.array[i] * damping_factor + (1.0 - damping_factor) / (double) nodes_count;
      err += fabs(eigen_vector.array[i] - previous_ev.array[i]);
    }

    *iterations_count = j;
    if (err < epsilon) return eigen_vector;
  }

  free(previous_ev.array);

  return eigen_vector;
}