#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "vector.h"

#ifndef REAL
#define REAL
typedef float real;
#endif /* REAL */

struct Matrix {
	int size;
	int length;
	real *value;
};

struct Matrix *allocate_matrix(int size, int length);
void free_matrix(struct Matrix *matrix);
void randomize_matrix(struct Matrix *matrix);
void copy_matrix(struct Matrix *source, struct Matrix *destination);
void add_matrix(struct Matrix *first_summand, struct Matrix *second_summand, struct Matrix *sum);
void subtract_matrix(struct Matrix *minuend, struct Matrix *subtrahend, struct Matrix *difference);
void scale_matrix(real scalar, struct Matrix *matrix, struct Matrix *scaled_matrix);
void multiply_matrix_entrywise(struct Matrix *first_factor, struct Matrix *second_factor, struct Matrix *product);
void divide_matrix_entrywise(struct Matrix *dividend, struct Matrix *divisor, struct Matrix *quotient);
void multiply_matrix_vector(struct Matrix *matrix, struct Vector *vector, struct Vector *product);
void multiply_transformed_matrix_vector(struct Matrix *matrix, struct Vector *vector, struct Vector *product);
void multiply_vector(struct Vector *second_factor, struct Vector *first_factor, struct Matrix *product);

#endif /* MATRIX_H */
