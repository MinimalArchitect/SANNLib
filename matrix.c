#include "matrix.h"

/* Precondition:
	size > 0
	length > 0
   Sideeffect:
	None
   Postcondition:
	allocated Matrix
*/
struct Matrix *
init_matrix(int size, int length)
{
	struct Matrix *new;

	new = malloc(sizeof(*new));
	new->size = size;
	new->length = length;
	new->value = malloc(sizeof(int) * (length * size));
	return new;
}

/* Precondition:
	previously allocated Matrix m
   Sideeffect:
	free's allocated Matrix m
   Postcondition:
	None
*/
void
free_matrix(struct Matrix *m)
{
	free(m->value);
	free(m);
}

/* Precondition:
	previously allocated Matrix m
   Sideeffect:
	m->value[i] == random_value, for i in [0, m->size * m->length)
   Postcondition:
	None
*/
void
randomize_matrix(struct Matrix *m)
{
	int i, N;

	N = m->size * m->length;
	for (i = 0;i < N;i++)
		m->value[i] = (float) rand() / ((float) RAND_MAX);
	return;
}

/* Precondition:
	previously allocated Matrix a and out
	a->size == out->size
	a->length == out->length
   Sideeffect:
	out->value[i] == a->value[i], for i in [0, a->size * a->length)
   Postcondition:
	None
*/
void
copy_matrix(struct Matrix *a, struct Matrix *out)
{
	int i, N;

	N = a->size * a->length;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i];
	return;
}

/* Precondition:
	previously allocated Matrix a, b and out
	a->size == b->size
	b->size == out->size
	a->length == b->length
	b->length == out->length
   Sideeffect:
	out->value[i] == a->value[i] + b->value[i], for i in [0, a->size * a->length)
   Postcondition:
	None
*/
void
add_matrix(struct Matrix *a, struct Matrix *b, struct Matrix *out)
{
	int i, N;

	N = a->size * a->length;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i] + b->value[i];
	return;
}

/* Precondition:
	previously allocated Matrix a, b and out
	a->size == b->size
	b->size == out->size
	a->length == b->length
	b->length == out->length
   Sideeffect:
	out->value[i] == a->value[i] - b->value[i], for i in [0, a->size * a->length)
   Postcondition:
	None
*/
void
sub_matrix(struct Matrix *a, struct Matrix *b, struct Matrix *out)
{
	int i, N;

	N = a->size * a->length;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i] - b->value[i];
	return;
}

/* Precondition:
	previously allocated Matrix a and out
	a->size == out->size
	a->length == out->length
   Sideeffect:
	out->value[i] == l * a->value[i], for i in [0, a->size * a->length)
   Postcondition:
	None
*/
void
mul_scalar_matrix(float l, struct Matrix *a, struct Matrix *out)
{
	int i, N;

	N = a->size * a->length;
	for (i = 0;i < N;i++)
		out->value[i] = l * a->value[i];
	return;
}

/* Precondition:
	previously allocated Matrix a, b and out
	a->size == b->size
	b->size == out->size
	a->length == b->length
	b->length == out->length
   Sideeffect:
	out->value[i] == a->value[i] * b->value[i], for i in [0, a->size * a->length)
   Postcondition:
	None
*/
void
mul_hadamard_matrix(struct Matrix *a, struct Matrix *b, struct Matrix *out)
{
	int i, N;

	N = a->size * a->length;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i] * b->value[i];
	return;
}

/* Precondition:
	previously allocated Matrix a, b and out
	a->size == b->size
	b->size == out->size
	a->length == b->length
	b->length == out->length
   Sideeffect:
	out->value[i] == a->value[i] / b->value[i], for i in [0, a->size * a->length)
   Postcondition:
	None
*/
void
div_hadamard_matrix(struct Matrix *a, struct Matrix *b, struct Matrix *out)
{
	int i, N;

	N = a->size * a->length;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i] / b->value[i];
	return;
}

/* Precondition:
	previously allocated Matrix m
	previously allocated Vector in and out
	m->size == out->size
	m->length == in->length
   Sideeffect:
	out->value[j] == sum of (m->value[j * in->size + i] * in->value[i]) over i, for i in [0, in->size) and j in [0, out->size)
   Postcondition:
	None
*/
void
mul_matrix_vector(struct Matrix *m, struct Vector *in, struct Vector *out)
{
	int i, j, N, M;

	M = out->size;
	N = in->size;
	for (j = 0;j < M;j++) {
		out->value[j] = 0.0f;
		for (i = 0;i < N;i++)
			out->value[j] += m->value[j * N + i] * in->value[i];
	}
	return;
}

/* Precondition:
	previously allocated Matrix m
	previously allocated Vector in and out
	m->size == out->size
	m->length == in->length
   Sideeffect:
	in->value[i] == sum of (out->value[j] * m->value[j * in->size + i] over j, for i in [0, in->size) and j in [0, out->size)
   Postcondition:
	None
*/
void
mul_matrix_vector_reverse(struct Matrix *m, struct Vector *out, struct Vector *in)
{
	int i, j, N, M;

	M = out->size;
	N = in->size;
	for (i = 0;i < N;i++) {
		in->value[i] = 0.0f;
		for (j = 0;j < M;j++)
			in->value[i] += out->value[j] * m->value[j * N + i];
	}
	return;
}

/* Precondition:
	previously allocated Matrix m
	previously allocated Vector in and out
	m->size == out->size
	m->length == in->length
   Sideeffect:
	m->value[j * a->size = i] == b->value[j] * a->value[i], for i in [0, a->size) and j in [0, b->size)
   Postcondition:
	None
*/
void
mul_vector(struct Vector *a, struct Vector *b, struct Matrix *m)
{
	int i, j, N, M;

	N = a->size;
	M = b->size;
	for (j = 0;j < M;j++) {
		for (i = 0;i < N;i++)
			m->value[j * N + i] = b->value[j] * a->value[i];
	}
	return;
}
