#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./headers/matrix.h"
#include "./headers/graph.h"
#include "./headers/utils.h"

int main(int argc, char *argv[]) {
  char *file_path = NULL;
  /* int epsilon = 0.0000001;
  int damping_factor = 0.85; */

  if (argc > 1) {
    file_path = argv[1];
  }
  else {
    file_path = "./graphs/Wiki-Vote.txt";
  }

  Graph graph = get_graph_from_file(file_path);
  normalize_graph(&graph);
  //display_graph(graph);
  Matrix matrix = graph_to_matrix(graph);
  display_matrix(matrix);

  return 0;
}