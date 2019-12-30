#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "vector.h"

struct Matrix {
	int size;
	int length;
	float *value;
};

struct Matrix *allocate_matrix(int size, int length);
void free_matrix(struct Matrix *m);
void randomize_matrix(struct Matrix *m);
void copy_matrix(struct Matrix *a, struct Matrix *out);
void add_matrix(struct Matrix *a, struct Matrix *b, struct Matrix *out);
void sub_matrix(struct Matrix *a, struct Matrix *b, struct Matrix *out);
void mul_scalar_matrix(float l, struct Matrix *b, struct Matrix *out);
void mul_hadamard_matrix(struct Matrix *a, struct Matrix *b, struct Matrix *out);
void div_hadamard_matrix(struct Matrix *a, struct Matrix *b, struct Matrix *out);
void mul_matrix_vector(struct Matrix *m, struct Vector *in, struct Vector *out);
void mul_matrix_vector_reverse(struct Matrix *m, struct Vector *out, struct Vector *in);
void mul_vector(struct Vector *a, struct Vector *b, struct Matrix *out);

#endif /* MATRIX_H */
