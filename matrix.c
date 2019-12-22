#include "matrix.h"

matrix *
init_matrix(int _size, int _length)
{
	matrix *new;

	new = (matrix *) malloc(sizeof(matrix));
	new->size = _size;
	new->length = _length;
	new->value = (float *) malloc(sizeof(int) * (_length * _size));
	return new;
}

void
free_matrix(matrix *m)
{
	free(m->value);
	free(m);
}

void
random_matrix(matrix *m)
{
	int i, N;

	N = m->size * m->length;
	for (i = 0;i < N;i++)
		m->value[i] = (float) rand() / ((float) RAND_MAX);
	return;
}

int
add_matrix(matrix *a, matrix *b, matrix *o)
{
	int i, N;

	if (a->size != b->size || a->length != b->length
	|| a->size != o->size || a->length != o->length)
		return EXIT_FAILURE;
	N = a->size * a->length;
	for (i = 0;i < N;i++)
		o->value[i] = a->value[i] + b->value[i];
	return EXIT_SUCCESS;
}

int
sub_matrix(matrix *a, matrix *b, matrix *o)
{
	int i, N;

	if (a->size != b->size || a->length != b->length
	|| a->size != o->size || a->length != o->length)
		return EXIT_FAILURE;
	N = a->size * a->length;
	for (i = 0;i < N;i++)
		o->value[i] = a->value[i] - b->value[i];
	return EXIT_SUCCESS;
}

int
mul_matrix_scalar(float l, matrix *a, matrix *o)
{
	int i, N;

	if (a->size != o->size || a->length != o->length)
		return EXIT_FAILURE;
	N = a->size * a->length;
	for (i = 0;i < N;i++)
		o->value[i] = l * a->value[i];
	return EXIT_SUCCESS;
}

int
mul_matrix_had(matrix *a, matrix *b, matrix *o)
{
	int i, N;

	if (a->size != b->size || a->length != b->length
	|| a->size != o->size || a->length != o->length)
		return EXIT_FAILURE;
	N = a->size * a->length;
	for (i = 0;i < N;i++)
		o->value[i] = a->value[i] * b->value[i];
	return EXIT_SUCCESS;
}

int
div_matrix_had(matrix *a, matrix *b, matrix *o)
{
	int i, N;

	if (a->size != b->size || a->length != b->length
	|| a->size != o->size || a->length != o->length)
		return EXIT_FAILURE;
	N = a->size * a->length;
	for (i = 0;i < N;i++)
		o->value[i] = a->value[i] / b->value[i];
	return EXIT_SUCCESS;
}

int
mul_matrix_vector(matrix *m, vector *v, vector *o)
{
	int i, j, N, M;

	if (m->size != o->size
	|| m->length != v->size)
		return EXIT_FAILURE;
	M = o->size;
	N = v->size;
	for (j = 0;j < M;j++) {
		o->value[j] = 0.0f;
		for (i = 0;i < N;i++)
			o->value[j] += m->value[j * N + i] * v->value[i];
	}
	return EXIT_SUCCESS;
}

int
mul_matrix_vector_rev(matrix *m, vector *o, vector *v)
{
	int i, j, N, M;

	if (m->size != o->size
	|| m->length != v->size)
		return EXIT_FAILURE;
	M = o->size;
	N = v->size;
	for (i = 0;i < N;i++) {
		v->value[i] = 0.0f;
		for (j = 0;j < M;j++)
			v->value[i] += o->value[j] * m->value[j * N + i];
	}
	return EXIT_SUCCESS;
}

int
mul_vector(vector *a, vector *b, matrix *m)
{
	int i, j, N, M;

	if (a->size != m->size
	|| b->size != m->length)
		return EXIT_FAILURE;
	N = a->size;
	M = b->size;
	for (j = 0;j < M;j++)
		for (i = 0;i < N;i++)
			m->value[j * N + i] = b->value[j] * a->value[i];
	return EXIT_SUCCESS;
}
