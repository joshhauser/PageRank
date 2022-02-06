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
 * @brief Display matrix infp
 * 
 * @param matrix the matrix to display
 */
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

/**
 * @brief Divide vector's components by a double
 * 
 * @param vector a pointer on the vector to divide
 * @param x the divisor
 */
void double_divide_vector(Vector *vector, double x) {
	int i;

	for (i = 0; i < vector->length; i++)
		vector->array[i] /= x;
}

/**
 * @brief Write vector components to a file
 * 
 * @param vector the vector to write in a file
 * @param file_path the path of the file to write
 * @return int that is -1 for error, otherwise
 * number of written chars
 */
int vector_to_file(Vector vector, char *file_path) {
	FILE *file_pointer = fopen(file_path, "w");
	int written_chars_count = 0;

	if (file_pointer == NULL)
	{
		printf("Impossible d'ouvrir le fichier %s\n", file_path);
		exit(EXIT_FAILURE);
	}

	int i;
	for (i = 0; i < vector.length; i++)
		written_chars_count = fprintf(file_pointer, "%.10lf\n", vector.array[i]);

	fclose(file_pointer);

	return written_chars_count;
}

/**
 * @brief Write matrix components to a file
 * 
 * @param matrix the matrix to write in a file
 * @param file_path the path of the file to write
 * @return int that is -1 for error, otherwise
 * number of written chars
 */
int matrix_to_file(Matrix matrix, char *file_path) {
	FILE *file_pointer = fopen(file_path, "w");
	int written_chars_count = 0;

	if (file_pointer == NULL)
	{
		printf("Impossible d'ouvrir le fichier %s\n", file_path);
		exit(EXIT_FAILURE);
	}

	int i, j;
	for (i = 0; i < matrix.lines_number; i++) {
		for (j = 0; j < matrix.colums_number; j++) {
			fprintf(file_pointer, "%lf", matrix.array[i][j]);
			if (j < matrix.colums_number - 1)
				fputs(" ", file_pointer);
		}

		fputs("\n", file_pointer);
	}

	fclose(file_pointer);

	return written_chars_count;
}

/**
 * @brief Multiply a vector by a matrix,
 * using a list of triplets to represent
 * a hollow matrix
 * 
 * @param triplets the list of tripleys
 * @param vector the vector
 * @param triplets_count the number of triplets
 * @return Vector that is vector * triplets
 */
Vector matrix_dot_vector(double** triplets, Vector vector, int triplets_count) {
	int i;
	Vector result;
	result.length = vector.length;
	allocate_vector(&result);
	
	// Fill the result vector with zeros
	for (i = 0; i < result.length; i++) result.array[i] = 0.0;

	for (i = 0; i < triplets_count; i++) {
		result.array[(int) triplets[i][0]] += (triplets[i][2] * vector.array[(int) triplets[i][1]]);
	}

	return result;
}

/**
 * @brief Transform a graph to an
 * array of triplets [dest, src, probability]
 * 
 * @param graph the graph to transform
 * @param triplets_count the number of triplets
 * @return a double** variable which is the matrix
 */
double** graph_to_matrix(Graph graph, int* triplets_count) {
  int array_size = 0;
  double** triplets = (double**) malloc(array_size * sizeof(double*));
  int i, j;

  for (i = 0; i < graph.vertices_count; i++) {
    for (j = 0; j < graph.vertices[i].neighbours_count; j++) {

      if (j < graph.vertices[i].neighbours_count) { 
        array_size++;
        triplets = (double**) realloc(triplets, array_size * sizeof(double*));
      }

			// Dynamic allocation
      triplets[array_size - 1] = (double*) malloc(2 * sizeof(double));
			// Destionation
      triplets[array_size - 1][0] = (double) graph.vertices[i].neighbours[j];
			// Source
      triplets[array_size - 1][1] = (double) graph.vertices[i].label;
			// Probability to go from source to destination
      triplets[array_size - 1][2] = 1.0 / graph.vertices[i].neighbours_count;
    }
  }


	*triplets_count = array_size;

  return triplets;
}

/**
 * @brief Free an array of triplets
 * 
 * @param triplets the matrix to free
 * @param triplets_count the length of the matrix
 */
void free_triplets(double** triplets, int triplets_count) {
	for (int i = 0; i < triplets_count; i++) {
		free(triplets[i]);
	}

	free(triplets);
}