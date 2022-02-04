#ifndef MATRIX_H
#define MATRIX_H

#include "../headers/graph.h"


typedef struct t_matrix Matrix;
struct t_matrix {
	double** array;
	int lines_number;
	int colums_number;
};

typedef struct t_vector Vector;
struct t_vector {
	double* array;
	int length;
};

double compute_norm(Vector vector);
void allocate_matrix(Matrix* matrix);
void allocate_vector(Vector* vector);
void allocate_array(double*** array, int lines_number, int colums_number);
void callocate_array(double*** array, int lines_number, int colums_number);
void free_array(double** array, int lines_number);
void free_matrix(Matrix* matrix);
void display_matrix(Matrix matrix);
void double_divide_vector(Vector *vector, double x);
Matrix dot_matrices(Matrix matrix1, Matrix matrix2);
Matrix graph_to_matrix(Graph graph);
Vector matrix_dot_vector(Matrix matrix, Vector vector);
Vector matrix_dot_vector_2(double** reduced_matrix, Vector vector, int matrix_length);
int vector_to_file(Vector vector, char *file_path);
int matrix_to_file(Matrix matrix, char *file_path);

#endif