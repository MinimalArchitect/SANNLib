#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

struct Vector {
	float *value;
	int size;
};

struct Vector *allocate_vector(int size);
void free_vector(struct Vector *v);
void randomize_vector(struct Vector *v);
void copy_vector(struct Vector *a, struct Vector *out);
void add_vector(struct Vector *a, struct Vector *b, struct Vector *out);
void sub_vector(struct Vector *a, struct Vector *b, struct Vector *out);
void mul_scalar_vector(float l, struct Vector *b, struct Vector *out);
void mul_hadamard_vector(struct Vector *a, struct Vector *b, struct Vector *out);
void div_hadamard_vector(struct Vector *a, struct Vector *b, struct Vector *out);
void function_vector(struct Vector *a, float (*function)(float), struct Vector *out);
int max_element(struct Vector *v);
float max_value(struct Vector *v);

#endif /* VECTOR_H */
