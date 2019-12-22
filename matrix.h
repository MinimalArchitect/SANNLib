#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
typedef struct matrices {
	int size;
	int length;
	float *value;
} matrix;

#include "vector.h"

matrix *init_matrix();
void free_matrix(matrix *);
void random_matrix(matrix* m);
int add_matrix(matrix *a, matrix *b, matrix *o);
int sub_matrix(matrix *a, matrix *b, matrix *o);
int mul_matrix_scalar(float l, matrix *b, matrix *o);
int mul_matrix_had(matrix *a, matrix *b, matrix *o);
int div_matrix_had(matrix *a, matrix *b, matrix *o);
int mul_matrix_vector(matrix *m, vector *v, vector *o);
int mul_matrix_vector_rev(matrix *m, vector *v, vector *o);
int mul_vector(vector *a, vector *b, matrix *m);

#endif /* MATRIX_H */
