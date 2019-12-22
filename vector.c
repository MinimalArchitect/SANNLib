#include <stdlib.h>

#include "vector.h"

vector *
init_vector(int _size)
{
	vector *new;

	new = (vector *) malloc(sizeof(vector));
	new->size = _size;
	new->value = (float *) malloc(sizeof(float) * _size);
	return new;
}

void
free_vector(vector *v)
{
	free(v->value);
	free(v);
	return;
}

void
random_vector(vector *v)
{
	int i, N;

	N = v->size;
	for (i = 0;i < N;i++)
		v->value[i] = (float) rand() / ((float) RAND_MAX);
	return;
}

int
add_vector(vector *a, vector *b, vector *o)
{
	int i, N;

	if (a->size != b->size
	|| a->size != o->size)
		return EXIT_FAILURE;
	N = a->size;
	for (i = 0;i < N;i++)
		o->value[i] = a->value[i] + b->value[i];
	return EXIT_SUCCESS;
}

int
sub_vector(vector *a, vector *b, vector *o)
{
	int i, N;

	if (a->size != b->size
	|| a->size != o->size)
		return EXIT_FAILURE;
	N = a->size;
	for (i = 0;i < N;i++)
		o->value[i] = a->value[i] - b->value[i];
	return EXIT_SUCCESS;
}

int
mul_vector_scalar(float l, vector *a, vector *o)
{
	int i, N;

	if (a->size != o->size)
		return EXIT_FAILURE;
	N = a->size;
	for (i = 0;i < N;i++)
		o->value[i] = l * a->value[i];
	return EXIT_SUCCESS;
}

int
mul_vector_had(vector *a, vector *b, vector *o)
{
	int i, N;

	if (a->size != b->size
	|| a->size != o->size)
		return EXIT_FAILURE;
	N = a->size;
	for (i = 0;i < N;i++)
		o->value[i] = a->value[i] * b->value[i];
	return EXIT_SUCCESS;
}

int
div_vector_had(vector *a, vector *b, vector *o)
{
	int i, N;

	if (a->size != b->size
	|| a->size != o->size)
		return EXIT_FAILURE;
	N = a->size;
	for (i = 0;i < N;i++)
		o->value[i] = a->value[i] / b->value[i];
	return EXIT_SUCCESS;
}

int function_vector(vector *a, float (*func)(float), vector *o)
{
	int i, N;

	if (a->size != o->size)
		return EXIT_FAILURE;
	N = a->size;
	for (i = 0;i < N;i++)
		o->value[i] = func(a->value[i]);
	return EXIT_SUCCESS;
}
