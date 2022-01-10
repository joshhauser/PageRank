#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/utils.h"
#include "../headers/graph.h"
#include "../headers/utils.h"

/**
 * @brief Get the graph from file object
 * 
 * @param file_path the path of the file to read
 * @return Graph extracted from file
 */
Graph get_graph_from_file(char *file_path) {
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
    printf("Fichier introuvable.\n");
    exit(EXIT_FAILURE);
  }

  graph.vertices_count = 0;
  // Allocate graph
  graph.vertices = (Vertice*) malloc(0);
  
  // Read graph file
  while ((read = getline(&line, &length, fp)) != -1) {
    // Scan first vertice label
    sscanf(&line[0], "%d", &value);
    int from_index = index_in_vertices_array(graph.vertices, graph.vertices_count, value);
    
    // FIRST VERTICE
    if (from_index == -1) {
      from.label = value;
      from.neighbours_count = 1;
      from.neighbours = (Vertice*) malloc(sizeof(Vertice));
      from_index = i;
      i++;
      graph.vertices_count++;
      graph.vertices = (Vertice*) realloc(graph.vertices, graph.vertices_count * sizeof(Vertice));
    }
    else {
      from = graph.vertices[from_index];
      from.neighbours_count++;
      from.neighbours = (Vertice*) realloc(from.neighbours, from.neighbours_count * sizeof(Vertice));
    }

    // Get index of blank space that separates vertices in current line
    int bs_index = (int)(strchr(line, ' ') - line);
    // Scan second vertice label
    sscanf(&line[bs_index+1], "%d", &value);

    int to_index = index_in_vertices_array(graph.vertices, graph.vertices_count, value);
    
    // SECOND VERTICE
    if (to_index == -1) {
      to.label = value;
      to.neighbours_count = 0; // The graph is supposed to be oriented
      to.neighbours = (Vertice*) malloc(0);
      to_index = i;
      i++;
      graph.vertices_count++;
      graph.vertices = (Vertice*) realloc(graph.vertices, graph.vertices_count * sizeof(Vertice));
      // Add or update second vertice
      graph.vertices[to_index] = to;
    }
    else {
      to = graph.vertices[to_index];
    }

    // Add neighbours
    from.neighbours[from.neighbours_count - 1] = to;
    // Add or update first vertice
    graph.vertices[from_index] = from;
  }

  fclose(fp);

  return graph;
}

/**
 * @brief Normalize a graph to get
 * label to be from 0 to vertices_count.
 * Ex : 0, 1, 2,...,vertices_count
 * 
 * @param graph the graph to normalise
 */
void normalize_graph(Graph *graph) {
  int i, j, k, old_label;
  int *updated_vertices = (int*) malloc(graph->vertices_count * sizeof(int));

  for (i = 0; i < graph->vertices_count; i++) {
    old_label = graph->vertices[i].label;
    graph->vertices[i].label = i;
    updated_vertices[i] = old_label;
  }

  for (i = 0; i < graph->vertices_count; i++) {
    for (j = 0; j < graph->vertices[i].neighbours_count; j++) {
      k = index_in_int_array(updated_vertices, graph->vertices_count, graph->vertices[i].neighbours[j].label);
      graph->vertices[i].neighbours[j].label = k;
    }
  }
} 

/**
 * @brief Display graph info 
 * - label
 * - number of neighbours
 * - neighbours list
 * 
 * @param graph the graph to display
 */
void display_graph(Graph graph) {
  int i, j;

  printf("Nodes count: %d\n", graph.vertices_count);

  for (i = 0; i < graph.vertices_count; i++) {
    printf("Vertice n°%d\n", graph.vertices[i].label);
    printf("------------\n");
    printf("Neighbours count: %d\n", graph.vertices[i].neighbours_count);
    
    if (graph.vertices[i].neighbours_count > 0) {
      printf("Neighbours list : ");

      for (j = 0; j < graph.vertices[i].neighbours_count; j++) {
        printf("%d ", graph.vertices[i].neighbours[j].label);
      }
      
      printf("\n");
    }

    printf("-------------------------------------------------------\n");
  }
}

/**
 * @brief Write graph data in a file
 * 
 * @param graph the graph used to write the file
 * @param file_path the path of the file to write
 * @return int that is -1 for error, otherwise
 * number of written chars
 */
int graph_to_file(Graph graph, char *file_path) {
  int i, j, written_chars_count;
  FILE *file_pointer = fopen(file_path, "w");

  if (file_pointer == NULL) {
    printf("Impossible d'ouvrir le fichier %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < graph.vertices_count; i++) {
    fprintf(file_pointer, "Vertice N°%d\n", graph.vertices[i].label);
    fputs("---------------\n", file_pointer);
    fprintf(file_pointer, "Neighbours count: %d\n", graph.vertices[i].neighbours_count);
    fputs("Neighbours list: ", file_pointer);
    
    for (j = 0; j < graph.vertices[i].neighbours_count; j++) {
      written_chars_count = fprintf(file_pointer, "%d", graph.vertices[i].neighbours[j].label);
      if (j < graph.vertices[i].neighbours_count - 1)
        fputs(" ", file_pointer);
    } 

    fputs("\n__________________________\n", file_pointer);
  }
 

  fclose(file_pointer);

  return written_chars_count;
}

void sort_graph_vertices_list(Graph* graph) {
  Vertice tmp;
  Vertice vertice_to_move;

  int i;

  for (i = 0; i < graph->vertices_count; i++) {
    if (graph->vertices[i].label != i) {
      vertice_to_move = graph->vertices[i];
      tmp = graph->vertices[vertice_to_move.label];
      graph->vertices[vertice_to_move.label] = vertice_to_move;
      graph->vertices[i] = tmp;
    }
  }
}


int compare_vertices_label(const void* first, const void* second) {
  Vertice first_vertice = * (const Vertice*) first;
  Vertice second_vertice = * (const Vertice*) second;

  return (first_vertice.label - second_vertice.label);
}