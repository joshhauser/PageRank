#ifndef GRAPH_H
#define GRAPH_H

typedef struct t_vertice Vertice;
struct t_vertice {
  int label;
  Vertice *neighbours;
  int neighbours_count;
};

typedef struct t_graph Graph;
struct t_graph {
	Vertice *vertices;
};

Graph get_graph_from_file(char *file_path, int vertices_count);
void normalize_graph(Graph *graph, int vertices_count);

#endif