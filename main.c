#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "./headers/matrix.h"
#include "./headers/graph.h"
#include "./headers/utils.h"
#include "./headers/pagerank.h"


int main(int argc, char *argv[]) {
  // Default parameters
  char *file_path = NULL;
  double epsilon = 0.000001;
  double damping_factor = 0.85;
  int max_iterations = 100;
  int iterations_count = 0;
  clock_t begin, end;
  double elapsed_time = 0.0;
  int vertices_count = 0;
  // 0 if the array of eigen values should be sorted, otherwise 1
  int sort_array = -1;

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
  vertices_count = graph.vertices_count;
  qsort(graph.vertices, graph.vertices_count, sizeof(Vertice), compare_vertices_label);
  normalize_graph(&graph);
  //display_graph(graph);

  int triplets_count = 0;
  double** triplets = graph_to_matrix(graph, &triplets_count);

  begin = clock();
  Vector eigen_vector = apply_pagerank(triplets_count, graph.vertices_count, triplets, damping_factor, epsilon, max_iterations, &iterations_count);
  end = clock();

  elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
  write_perf(damping_factor, elapsed_time, vertices_count);

  if (sort_array > 0) {
    qsort(eigen_vector.array, eigen_vector.length, sizeof(double), compare_doubles);
    printf("\e[93m[PageRank]\e[39m DONE - Maximum range is %lf\n", eigen_vector.array[0]);
  }
  else {
    printf("\e[93m[PageRank]\e[39m DONE\n");
  }

  vector_to_file(eigen_vector, "output/eigen_vector.txt");
  free(eigen_vector.array);
  return 0;
}