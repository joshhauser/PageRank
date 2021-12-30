#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "parser.h"
#include "utils.h"
#include "graph.h"

int main() {
  Graph graph = get_graph_from_file("test.txt", 17);
  /**
   * TODO:
   * - use args instead of hard coded path
   * - remove vertices_count and compute it when reading the file
   */
}