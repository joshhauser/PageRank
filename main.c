#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "./headers/matrix.h"
#include "./headers/graph.h"
#include "./headers/utils.h"
#include "./headers/pagerank.h"

/**
 * TODO:
 * - add more comments
 * - check for docstrings
 * - clean the code
 */

int main(int argc, char *argv[]) {
  char *file_path = NULL;
  double epsilon = 0.000001;
  double damping_factor = 0.85;
  int max_iterations = 100;

  if (argc == 4) {
    file_path = argv[1];
    damping_factor = atof(argv[2]);
    max_iterations = atoi(argv[3]);

    printf("\e[93m[PageRank]\e[39m graph: %s, epsilon: %lf, damping_factor: %lf, max iterations: %d\n", file_path, epsilon, damping_factor, max_iterations);
  }
  else {
    file_path = "./graphs/Wiki-Vote.txt";
  }

  Graph graph = get_graph_from_file(file_path);
  normalize_graph(&graph);
  graph_to_file(graph, "output/normalized_graph.txt");

  Matrix matrix = graph_to_matrix(graph);
  matrix_to_file(matrix, "output/matrix.txt");

  Vector eigen_vector = apply_pagerank(matrix, damping_factor, epsilon, max_iterations);
  vector_to_file(eigen_vector, "output/eigen_vector.txt");

  int i;
  for (i = 0; i < eigen_vector.length; printf("eigen vector value n°%d: %lf\n", i, eigen_vector.array[i++]));

  return 0;
}