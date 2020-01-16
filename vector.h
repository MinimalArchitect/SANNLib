#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

struct Vector {
	float *value;
	int size;
};

struct Vector *allocate_vector(int size);
void free_vector(struct Vector *vector);
void randomize_vector(struct Vector *vector);
void copy_vector(struct Vector *source, struct Vector *destination);
void add_vector(struct Vector *first_summand, struct Vector *second_summand, struct Vector *sum);
void subtract_vector(struct Vector *minuend, struct Vector *subtrahend, struct Vector *difference);
void scale_vector(float scalar, struct Vector *vector, struct Vector *scaled_vector);
void multiply_vector_entrywise(struct Vector *first_factor, struct Vector *second_factor, struct Vector *product);
void divide_vector_entrywise(struct Vector *dividend, struct Vector *divisor, struct Vector *quotient);
void apply_function_on_vector(struct Vector *input, float (*function)(float), struct Vector *output);
int search_max_element(struct Vector *vector);
float search_max_value(struct Vector *vector);
void set_vector_zero(struct Vector *vector);

#endif /* VECTOR_H */
