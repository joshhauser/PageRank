#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "graph.h"
#include "utils.h"

int main() {
  Graph graph = get_graph_from_file("Wiki-Vote.txt");
  printf("nodes : %d\n", graph.vertices_count);
  /**
   * TODO:
   * - use args instead of hard coded path
   * - remove vertices_count and compute it when reading the file
   */
}