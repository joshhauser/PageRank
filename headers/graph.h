#ifndef GRAPH_H
#define GRAPH_H

typedef struct t_vertice Vertice;
struct t_vertice {
  int label;
  int *neighbours;
  int neighbours_count;
};

typedef struct t_graph Graph;
struct t_graph {
	Vertice *vertices;
  int vertices_count;
  int edges_count;
};

Graph get_graph_from_file(char *file_path);
void normalize_graph(Graph *graph);
void display_graph(Graph graph);
int graph_to_file(Graph graph, char *file_path);
int compare_vertices_label(const void* first, const void* second);
void free_graph(Graph* graph);
#endif