#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/matrix.h"

/**
 * @brief Compute the norm of a vector
 * 
 * @param vector the vector
 * @return the norm of the vector
 */
double compute_norm(Vector vector) {
  double component_sum = 0.0;

  int i;

  for (i = 0; i < vector.length; i++) component_sum += pow(vector.array[i], 2.0);

  return sqrt(component_sum);
}

/**
 * @brief Dynamic allocation for a matrix
 * 
 * @param matrix the matrix to allocate
 */
void allocate_matrix(Matrix* matrix) {
	callocate_array(&matrix->array, matrix->lines_number, matrix->colums_number);
}

/**
 * @brief Dynamic allocation for a vector
 * 
 * @param vector the vector to allocate
 */
void allocate_vector(Vector* vector) {
	vector->array = (double*) malloc(vector->length * sizeof(double));
}

/**
 * @brief Dynamic allocation for array
 * 
 * @param array the array to allocate
 * @param lines_number the lines count
 * @param colums_number the columns count
 */
void allocate_array(double*** array, int lines_number, int colums_number) {
	int i;

	*array = (double**) malloc(lines_number * sizeof(double*));

	for (i = 0; i < lines_number; i++) {
		(*array)[i] = (double*) malloc(colums_number * sizeof(double));
	}
}

/**
 * @brief Dynamic allocation for array using calloc
 * 
 * @param array the array to allocate
 * @param lines_number the lines count
 * @param colums_number the columns count
 */
void callocate_array(double*** array, int lines_number, int colums_number) {
	int i;

	*array = (double**) malloc(lines_number * sizeof(double*));

	for (i = 0; i < lines_number; i++) {
		(*array)[i] = (double*) calloc(colums_number, sizeof(double));
	}
}


/**
 * @brief Free an array
 * 
 * @param array the array to free
 * @param lines_number the lines count
 */
void free_array(double** array, int lines_number) {
	int i;

	for (i = 0; i < lines_number; i++) {
		free(array[i]);
	}

	free(array);
}

/**
 * @brief Free a matrix
 * 
 * @param matrix the matrix to free
 */
void free_matrix(Matrix* matrix) {
	free_array(matrix->array, matrix->lines_number);
}

/**
 * @brief Multiply two matrices
 * 
 * @param matrix1 
 * @param matrix2 
 * @return Matrix 
 */
Matrix dot_matrices(Matrix matrix1, Matrix matrix2) {
	/* Condition: la première matrice doit avoir un nombre de colonnes égal
	au nombre de lignes de la 2e matrice */
	Matrix result;
	int i, j, k;
	double val = 0;

	if (matrix1.colums_number != matrix2.lines_number)
	printf("Impossible d'effectuer le produit\n");

	result.lines_number = matrix1.lines_number;
	result.colums_number = matrix2.colums_number;
	allocate_matrix(&result);

	for (i = 0; i < matrix2.colums_number; i++) {
		for (k = 0; k < matrix1.lines_number; k++) {
			for (j = 0; j < matrix1.colums_number; j++) {
				val += matrix1.array[i][j] * matrix2.array[j][k];
				result.array[i][k] = val;
			}
			val = 0;
		}
	}

	return result;
}

Vector matrix_dot_vector(Matrix matrix, Vector vector) {
	Vector result;
	int i, j;
	double val = 0;

	if (matrix.colums_number != vector.length) printf("Impossible d'effectuer le produit.\n");

	result.length = vector.length;

	allocate_vector(&result);

	for (i = 0; i < matrix.colums_number; i++) {
		for (j = 0; j < vector.length; j++) {
			val += matrix.array[i][j] * vector.array[j];
		}

		result.array[i] = val;
		val = 0;
	}

	return result;
}

/**
 * @brief 
 * 
 */
Matrix graph_to_matrix(Graph graph) {
	Matrix matrix;
  matrix.colums_number = matrix.lines_number = graph.vertices_count;
  allocate_matrix(&matrix);

	int i, j;
	for (i = 0; i < graph.vertices_count; i++) {
		for (j = 0; j < graph.vertices[i].neighbours_count; j++) {
			matrix.array[graph.vertices[i].neighbours[j].label][i] = 1.0 / (double) graph.vertices[i].neighbours_count;
		}
	}

	return matrix;
}

// Display matrices
void display_matrix(Matrix matrix) {
	int i, j;

	for (i = 0; i < matrix.lines_number; i++) {
		for (j = 0; j < matrix.colums_number; j++) {
			if (j == 0) printf("(");
			printf("%.2f", matrix.array[i][j]);
			if (j == (matrix.colums_number - 1)) printf(")");
			else printf("   ");
		}
		printf("\n");
	}
}
