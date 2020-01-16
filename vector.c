#include "vector.h"

/* Precondition:
	size > 0
   Postcondition:
	allocated struct Vector
*/
struct Vector *
allocate_vector(int size)
{
	struct Vector *new;

	new = malloc(sizeof(*new));
	new->size = size;
	new->value = malloc(sizeof(float) * size);
	return new;
}

/* Precondition:
	previously allocated vector
   Postcondition:
	free's allocated Vector vector
*/
void
free_vector(struct Vector *vector)
{
	free(vector->value);
	free(vector);
	return;
}

/* Precondition:
	previously allocated vector
   Postcondition:
	vector->value[i] == random_value, for i in [0..vector->size - 1]
*/
void
randomize_vector(struct Vector *vector)
{
	float *result, *last;

	result = vector->value;
	last = vector->value + vector->size;
	for (;result < last;result++)
		*result = (float) rand() / ((float) RAND_MAX) * 2.0f - 1.0f;
	return;
}


/* Precondition:
	previously allocated source and destination
	destination->size == source->size
   Postcondition:
	destination->value[i] == source->value[i], for i in [0..destination->size - 1]
*/
void
copy_vector(struct Vector *source, struct Vector *destination)
{
	float *first, *result, *last;

	first = source->value;
	result = destination->value;
	last = destination->value + destination->size;
	for (;result < last;result++, first++)
		*result = *first;
	return;
}

/* Precondition:
	previously allocated first_summand, second_summand and sum
	first_summand->size == second_summand->size == sum->size
   Postcondition:
	sum->value[i] == first_summand->value[i] + second_summand->value[i], for i in [0, sum->size - 1]
*/
void
add_vector(struct Vector *first_summand, struct Vector *second_summand, struct Vector *sum)
{
	float *first, *second, *result, *last;

	first = first_summand->value;
	second = second_summand->value;
	result = sum->value;
	last = sum->value + sum->size;
	for (;result < last;result++, first++, second++)
		*result = *first + *second;
	return;
}

/* Precondition:
	previously allocated minuend, subtrahend and difference
	minuend->size == subtrahend->size == difference->size
   Postcondition:
	difference->value[i] == minuend->value[i] - subtrahend->value[i], for i in [0..difference->size - 1]
*/
void
subtract_vector(struct Vector *minuend, struct Vector *subtrahend, struct Vector *difference)
{
	float *first, *second, *result, *last;

	first = minuend->value;
	second = subtrahend->value;
	result = difference->value;
	last = difference->value + difference->size;
	for (;result < last;result++, first++, second++)
		*result = *first - *second;
	return;
}

/* Precondition:
	previously allocated vector and scaled_vector
	vector->size == scaled_vector->size
   Postcondition:
	scaled_vector->value[i] == scalar * vector->value[i], for i in [0..scaled_vector->size - 1]
*/
void
scale_vector(float scalar, struct Vector *vector, struct Vector *scaled_vector)
{
	float *first, *result, *last;

	first = vector->value;
	result = scaled_vector->value;
	last = scaled_vector->value + scaled_vector->size;
	for (;result < last;result++, first++)
		*result = scalar * *first;
	return;
}

/* Precondition:
	previously allocated first_factor, second_factor and product
	first_factor->size == second_factor->size == product->size
   Postcondition:
   	product->value[i] == first_factor->value[i] * second_factor->value[i], for i in [0..product->size - 1]
*/
void
multiply_vector_entrywise(struct Vector *first_factor, struct Vector *second_factor, struct Vector *product)
{
	float *first, *second, *result, *last;

	first = first_factor->value;
	second = second_factor->value;
	result = product->value;
	last = product->value + product->size;
	for (;result < last;result++, first++, second++)
		*result = *first * *second;
	return;
}

/* Precondition:
	previously allocated dividend, divisor and quotient
	dividend->size == divisor->size == quotient->size
   Postcondition:
	quotient->value[i] == dividend->value[i] / divisor->value[i], for i in [0..quotient->size - 1]
*/
void
divide_vector_entrywise(struct Vector *dividend, struct Vector *divisor, struct Vector *quotient)
{
	float *first, *second, *result, *last;

	first = dividend->value;
	second = divisor->value;
	result = quotient->value;
	last = quotient->value + quotient->size;
	for (;result < last;result++, first++, second++)
		*result = *first / *second;
	return;
}

/* Precondition:
	previously allocated input and output
	input->size == output->size
   Postcondition:
	output->value[i] == function(input->value[i]), for i in [0..output->size - 1]
*/
void
apply_function_on_vector(struct Vector *input, float (*function)(float), struct Vector *output)
{
	float *first, *result, *last;

	first = input->value;
	result = output->value;
	last = output->value + output->size;
	for (;result < last;result++, first++)
		*result = function(*first);
	return;
}

/* Precondition:
	previously allocated vector
   Postcondition:
	i, with max(vector->value[i]), for in vector->value in [0..vector->size - 1]
*/
int
search_max_element(struct Vector *vector)
{
	float *index, *last, *maximum;

	maximum = vector->value;
	index = vector->value + 1;
	last = vector->value + vector->size;
	for (;index < last;index++) {
		if (*index > *maximum)
			maximum = index;
	}
	return maximum - vector->value;
}

/* Precondition:
	previously allocated vector
   Postcondition:
	max(vector->value[i]), for i in [0..vector->size - 1]
*/
float
search_max_value(struct Vector *vector)
{
	float *index, *last, *maximum;

	maximum = vector->value;
	index = vector->value + 1;
	last = vector->value + vector->size;
	for (;index < last;index++) {
		if (*index > *maximum)
			maximum = index;
	}
	return *maximum;
}

/* Precondition:
	previously allocated vector
   Postcondition:
	vector->value[i] == 0.0f, for i in [0..vector->size - 1]
*/
void
set_vector_zero(struct Vector *vector)
{
	float *result, *last;

	result = vector->value;
	last = vector->value + vector->size;
	for(;result < last;result++)
		*result = 0.0f;
	return;
}
