#include "matrix.h"

/* Precondition:
	size > 0
	length > 0
   Postcondition:
	allocated struct Matrix
*/
struct Matrix *
allocate_matrix(int size, int length)
{
	struct Matrix *new;

	new = malloc(sizeof(*new));
	new->size = size;
	new->length = length;
	new->value = malloc(sizeof(real) * length * size);
	return new;
}

/* Precondition:
	previously allocated matrix
   Postcondition:
	free's allocated matrix
*/
void
free_matrix(struct Matrix *matrix)
{
	free(matrix->value);
	free(matrix);
}

/* Precondition:
	previously allocated matrix
   Postcondition:
	matrix->value[i] == random_value, for i in [0..matrix->size * matrix->length - 1]
*/
void
randomize_matrix(struct Matrix *matrix)
{
	real *result, *last;

	result = matrix->value;
	last = matrix->value + matrix->size * matrix->length;
	for (;result < last;result++)
		*result = (real) rand() / ((real) RAND_MAX) * 2.0f - 1.0f;
	return;
}

/* Precondition:
	previously allocated source and destination
	source->size == destination->size
	source->length == destination->length
   Postcondition:
	destination->value[i] == source->value[i], for i in [0..a->size * a->length - 1]
*/
void
copy_matrix(struct Matrix *source, struct Matrix *destination)
{
	real *first, *result, *last;

	first = source->value;
	result = destination->value;
	last = destination->value + destination->size * destination->length;
	for (;result < last;result++, first++)
		*result = *first;
	return;
}

/* Precondition:
	previously allocated first_summand, second_summand and sum
	first_summand->size == second_summand->size == sum->size
	first_summand->length == second_summand->length == sum->length
   Postcondition:
	sum->value[i] == first_summand->value[i] + second_summand->value[i], for i in [0..sum->size * sum->length - 1]
*/
void
add_matrix(struct Matrix *first_summand, struct Matrix *second_summand, struct Matrix *sum)
{
	real *first, *second, *result, *last;

	first = first_summand->value;
	second = second_summand->value;
	result = sum->value;
	last = sum->value + sum->size * sum->length;
	for (;result < last;result++, first++, second++)
		*result = *first + *second;
	return;
}

/* Precondition:
	previously allocated minuend, subtrahend and difference
	minuend->size == subtrahend->size == difference->size
	minuend->length == subtrahend->length == difference->length
   Postcondition:
	difference->value[i] == minuend->value[i] - subtrahend->value[i], for i in [0..difference->size * difference->length - 1]
*/
void
subtract_matrix(struct Matrix *minuend, struct Matrix *subtrahend, struct Matrix *difference)
{
	real *first, *second, *result, *last;

	first = minuend->value;
	second = subtrahend->value;
	result = difference->value;
	last = difference->value + difference->size * difference->length;
	for (;result < last;result++, first++, second++)
		*result = *first - *second;
	return;
}

/* Precondition:
	previously allocated Matrix matrix and scaled_matrix
	matrix->size == scaled_matrix->size
	matrix->length == scaled_matrix->length
   Postcondition:
	scaled_matrix->value[i] == scalar * matrix->value[i], for i in [0..scaled_matrix->size * scaled_matrix->length - 1]
*/
void
scale_matrix(real scalar, struct Matrix *matrix, struct Matrix *scaled_matrix)
{
	real *first, *result, *last;

	first = matrix->value;
	result = scaled_matrix->value;
	last = scaled_matrix->value + scaled_matrix->size * scaled_matrix->length;
	for (;result < last;result++, first++)
		*result = scalar * *first;
	return;
}

/* Precondition:
	previously allocated Matrix first_factor, second_factor and product
	first_factor->size == second_factor->size == product->size
	first_factor->length == second_factor->length == product->length
   Postcondition:
	product->value[i] == first_factor->value[i] * second_factor->value[i], for i in [0..product->size * product->length - 1]
*/
void
multiply_matrix_entrywise(struct Matrix *first_factor, struct Matrix *second_factor, struct Matrix *product)
{
	real *first, *second, *result, *last;

	first = first_factor->value;
	second = second_factor->value;
	result = product->value;
	last = product->value + product->size * product->length;
	for (;result < last;result++, first++, second++)
		*result = *first * *second;
	return;
}

/* Precondition:
	previously allocated Matrix dividend, divisor and quotient
	dividend->size == divisor->size == quotient->size
	dividend->length == divisor->length == quotient->length
   Postcondition:
	quotient->value[i] == dividend->value[i] / divisor->value[i], for i in [0..quotient->size * quotient->length - 1]
*/
void
divide_matrix_entrywise(struct Matrix *dividend, struct Matrix *divisor, struct Matrix *quotient)
{
	real *first, *second, *result, *last;

	first = dividend->value;
	second = divisor->value;
	result = quotient->value;
	last = quotient->value + quotient->size * quotient->length;
	for (;result < last;result++, first++, second++)
		*result = *first / *second;
	return;
}

/* Precondition:
	previously allocated matrix, vector and product
	matrix->size == product->size
	matrix->length == vector->size
   Postcondition:
	product->value[j] == sum of (matrix->value[j * vector->size + i] * vector->value[i]) over i, for i in [0..vector->size - 1] and j in [0..product->size - 1]
*/
void
multiply_matrix_vector(struct Matrix *matrix, struct Vector *vector, struct Vector *product)
{
	real *first, *second, *result, *N, *M;

	first = matrix->value;
	N = vector->value + vector->size;
	M = product->value + product->size;
	for (result = product->value;result < M;result++) {
		*result = 0.0f;
		for (second = vector->value;second < N;second++, first++)
			*result += *first * *second;
	}
	return;
}

/* Precondition:
	previously allocated matrix, vector, product
	matrix->size == vector->size
	matrix->length == product->length
   Postcondition:
	product->value[j] == sum of (vector->value[i] * matrix->value[i * vector->size + j] over i, for i in [0..vector->size - 1] and j in [0..product->size - 1]
*/
void
multiply_transformed_matrix_vector(struct Matrix *matrix, struct Vector *vector, struct Vector *product)
{
	real *first, *second, *result, *N, *M;
	int j, size;

	second = matrix->value;
	M = vector->value + vector->size;
	N = product->value + product->size;
	size = product->size;
	for (result = product->value;result < N;result++, second++) {
		*result = 0.0f;
		for (first = vector->value, j = 0;first < M;first++, j += size)
			*result += *first * *(second + j);
	}
	return;
}

/* Precondition:
	previously allocated first_factor, second_factor, product
	product->size == second_factor->size
	product->length == first_factor->size
   Postcondition:
	product->value[j * product->length + i] == second_factor->value[j] * first_factor->value[i], for i in [0, first_factor->size - 1] and j in [0..second_factor->size - 1]
*/
void
multiply_vector(struct Vector *first_factor, struct Vector *second_factor, struct Matrix *product)
{
	real *first, *second, *result, *N, *M;

	result = product->value;
	N = first_factor->value + first_factor->size;
	M = second_factor->value + second_factor->size;
	for (second = second_factor->value;second < M;second++) {
		for (first = first_factor->value;first < N;first++, result++)
			*result = *second * *first;
	}
	return;
}
