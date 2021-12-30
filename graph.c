#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "utils.h"

/**
 * @brief Get the graph from file object
 * 
 * @param file_path the path of the file to read
 * @param vertices_count the number of vertices, used to allcate
 * the vertices array
 * @return Graph extracted from file
 */
Graph get_graph_from_file(char *file_path, int vertices_count) {
  FILE *fp;
  char *line = NULL;
  Graph graph;
  size_t length = 0;
  ssize_t read = 0;
  int i = 0;
  int value;
  Vertice from;
  Vertice to;

  // Open graph file
  fp = fopen(file_path, "r");
  if (fp == NULL) {
    printf("Fichier introuvable.");
    exit(EXIT_FAILURE);
  }

  // Allocate graph
  graph.vertices = (Vertice*) malloc(vertices_count * sizeof(Vertice));
  
  // Read graph file
  while ((read = getline(&line, &length, fp)) != -1) {
    // Scan first vertice label
    sscanf(&line[0], "%d", &value);
    int from_index = index_in_array(graph.vertices, vertices_count, value);
    
    // FIRST VERTICE
    if (from_index == -1) {
      from.label = value;
      from.neighbours_count = 1;
      from.neighbours = (Vertice *) malloc(sizeof(Vertice));
      from_index = i;
    }
    else {
      from = graph.vertices[from_index];
      from.neighbours_count++;
      from.neighbours = (Vertice *) realloc(from.neighbours, from.neighbours_count);
    }

    // Get index of blank space that separates vertices in current line
    int bs_index = (int)(strchr(line, ' ') - line);
    
    // Scan second vertice label
    sscanf(&line[bs_index+1], "%d", &value);
    int to_index = index_in_array(graph.vertices, vertices_count, value);

    // SECOND VERTICE
    if (to_index == -1) {
      to.label = value;
      to.neighbours_count = 1;
      to.neighbours = (Vertice *) malloc(sizeof(Vertice));
      to_index = i;
    }
    else {
      to = graph.vertices[to_index];
      to.neighbours_count++;
      to.neighbours = (Vertice *) realloc(to.neighbours, to.neighbours_count);
    }

    // Add neighbours
    from.neighbours[from.neighbours_count - 1] = to;
    to.neighbours[to.neighbours_count - 1] = from;

    // Add or update first vertice
    graph.vertices[from_index] = from;

    // Add or update second vertice
    graph.vertices[to_index] = to;

    i++;
  }

  return graph;
}

/**
 * @brief Normalize a graph to get
 * label to be from 0 to vertices_count.
 * Ex : 0, 1, 2,...,vertices_count
 * 
 * @param graph the graph to normalise
 * @param vertices_count the number of vertices in the graph
 */
void normalize_graph(Graph *graph, int vertices_count) {
  int i, j, k, old_label;
  Vertice vertice;

  for (i = 0; i < vertices_count; i++) {
    old_label = graph[i].vertices->label;
    graph->vertices[i].label = i;

    // Search and replace all occurrences of old_label
    for (j = 0; j < vertices_count; i++) {
      for (k = 0; k < graph->vertices[i].neighbours_count; k++) {
        vertice = graph->vertices[j].neighbours[k];
        if (vertice.label == old_label) vertice.label = i;
      }
    }
  }
}