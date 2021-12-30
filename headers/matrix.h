#ifndef MATRIX_H
#define MATRIX_H

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
void free_array(double** array, int lines_number);
void free_matrix(Matrix* matrix);
Matrix dot_matrices(Matrix matrix1, Matrix matrix2);
Vector dot(Matrix matrix, Vector vector);

#endif