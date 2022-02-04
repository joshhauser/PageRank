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

  Matrix matrix = graph_to_matrix(graph);
  //free_graph(&graph);

  /*********************************************************************************/
  int array_size = 0;
  double** triplets = (double**) malloc(array_size * sizeof(double*));
  int i, j;

  for (i = 0; i < graph.vertices_count; i++) {
    for (j = 0; j < graph.vertices[i].neighbours_count; j++) {

      if (j < graph.vertices[i].neighbours_count) { 
        array_size++;
        triplets = (double**) realloc(triplets, array_size * sizeof(double*));
      }

      triplets[array_size-1] = (double*) malloc(2 * sizeof(double));
      triplets[array_size-1][0] = (double) graph.vertices[i].neighbours[j];
      triplets[array_size - 1][1] = (double) graph.vertices[i].label;
      triplets[array_size-1][2] = 1.0 / graph.vertices[i].neighbours_count;
    }
  }

  begin = clock();
  Vector eigen_vector = pg(array_size, graph.vertices_count, triplets, damping_factor, epsilon, max_iterations, &iterations_count);
  //Vector eigen_vector = apply_pagerank(matrix, damping_factor, epsilon, max_iterations, &iterations_count);
  
  end = clock();
  
 /*  for (i = 0; i < graph.vertices_count; i++) {
    free(triplets[i]);
  } */

  //free(triplets);

  elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
  
  write_perf(damping_factor, elapsed_time, vertices_count);

  vector_to_file(eigen_vector, "output/eigen_vector.txt");
  free(eigen_vector.array);
  /*********************************************************************************/
  return 0;
  //display_matrix(matrix);
/* 
  begin = clock();
  Vector eigen_vector = apply_pagerank(matrix, damping_factor, epsilon, max_iterations, &iterations_count);
  end = clock();

  free_matrix(&matrix);
  
  vector_to_file(eigen_vector, "output/eigen_vector.txt");
  free(eigen_vector.array);

  elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
  
  write_perf(damping_factor, elapsed_time, vertices_count);

  //for (i = 0; i < eigen_vector.length; printf("eigen vector value n°%d: %lf\n", i, eigen_vector.array[i++]));

  return 0; */
}