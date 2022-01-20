#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "./headers/matrix.h"
#include "./headers/graph.h"
#include "./headers/utils.h"
#include "./headers/pagerank.h"

/**
 * TODO:
 * - add more comments
 * - clean the code
 * - Make more complete output for performance
 * curves generation
 */

int main(int argc, char *argv[]) {
  // Default parameters
  char *file_path = NULL;
  double epsilon = 0.000001;
  double damping_factor = 0.85;
  int max_iterations = 100;
  int iterations_count = 0;
  clock_t begin, end;
  double elapsed_time = 0.0;

  // Get args from command line
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
  qsort(graph.vertices, graph.vertices_count, sizeof(Vertice), compare_vertices_label);
  normalize_graph(&graph);
  graph_to_file(graph, "output/normalized_graph.txt");
  //display_graph(graph);

  Matrix matrix = graph_to_matrix(graph);
  matrix_to_file(matrix, "output/matrix.txt");
  display_matrix(matrix);

  begin = clock();
  Vector eigen_vector = apply_pagerank(matrix, damping_factor, epsilon, max_iterations, &iterations_count);
  end = clock();
  
  vector_to_file(eigen_vector, "output/eigen_vector.txt");

  elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
  
  write_perf(damping_factor, elapsed_time, graph.vertices_count);

  int i;
  for (i = 0; i < eigen_vector.length; printf("eigen vector value n°%d: %lf\n", i, eigen_vector.array[i++]));

  return 0;
}