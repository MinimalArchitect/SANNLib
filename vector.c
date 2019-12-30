#include "vector.h"

/* Precondition:
	size > 0
   Sideeffect:
	None
   Postcondition:
	allocated Vector
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
	previously allocated Vector v
   Sideeffect:
	free's allocated Vector v
   Postcondition:
	None
*/
void
free_vector(struct Vector *v)
{
	free(v->value);
	free(v);
	return;
}

/* Precondition:
	previously allocated Vector v
   Sideeffect:
	v->value[i] == random_value, for i in [0, v->size)
   Postcondition:
	None
*/
void
randomize_vector(struct Vector *v)
{
	int i, N;

	N = v->size;
	for (i = 0;i < N;i++)
		v->value[i] = (float) rand() / ((float) RAND_MAX);
	return;
}


/* Precondition:
	previously allocated Vector a and out
	a->size == out->size
   Sideeffect:
	a->value[i] == out->value, for i in [0, a->size)
   Postcondition:
	None
*/
void
copy_vector(struct Vector *a, struct Vector *out)
{
	int i, N;

	N = a->size;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i];
	return;
}

/* Precondition:
	previously allocated Vector a, b and out
	a->size == b->size
	b->size == out->size
   Sideeffect:
	out->value[i] == a->value[i] + b->value[i], for i in [0, a->size)
   Postcondition:
	None
*/
void
add_vector(struct Vector *a, struct Vector *b, struct Vector *out)
{
	int i, N;

	N = a->size;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i] + b->value[i];
	return;
}

/* Precondition:
	previously allocated Vector a, b and out
	a->size == b->size
	b->size == out->size
   Sideeffect:
	out->value[i] == a->value[i] - b->value[i], for i in [0, a->size)
   Postcondition:
	None
*/
void
sub_vector(struct Vector *a, struct Vector *b, struct Vector *out)
{
	int i, N;

	N = a->size;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i] - b->value[i];
	return;
}

/* Precondition:
	previously allocated Vector a and out
	a->size == out->size
   Sideeffect:
	out->value[i] == l * a->value[i], for i in [0, a->size)
   Postcondition:

   None
*/
void
mul_scalar_vector(float l, struct Vector *a, struct Vector *out)
{
	int i, N;

	N = a->size;
	for (i = 0;i < N;i++)
		out->value[i] = l * a->value[i];
	return;
}

/* Precondition:
	previously allocated Vector a, b and out
	a->size == b->size
	b->size == out->size
   Sideeffect:
   	out->value[i] == a->value[i] * b->value[i], for i in [0, a->size)
   Postcondition:
	None
*/
void
mul_hadamard_vector(struct Vector *a, struct Vector *b, struct Vector *out)
{
	int i, N;

	N = a->size;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i] * b->value[i];
	return;
}

/* Precondition:
	previously allocated Vector a, b and out
	a->size == b->size
	b->size == out->size
   Sideeffect:
	out->value[i] == a->value[i] / b->value[i], for i in [0, a->size)
   Postcondition:
	None
*/
void
div_hadamard_vector(struct Vector *a, struct Vector *b, struct Vector *out)
{
	int i, N;

	N = a->size;
	for (i = 0;i < N;i++)
		out->value[i] = a->value[i] / b->value[i];
	return;
}

/* Precondition:
	previously allocated Vector a and out
	a->size == out->size
   Sideeffect:
	out->value[i] == function(a->value[i]), for i in [0, a->size)
   Postcondition:
	None
*/
void
function_vector(struct Vector *a, float (*function)(float), struct Vector *out)
{
	int i, N;

	N = a->size;
	for (i = 0;i < N;i++)
		out->value[i] = function(a->value[i]);
	return;
}

/* Precondition:
	previously allocated Vector v
   Sideeffect:
	None
   Postcondition:
	index of maximal element in v-value in [0, v->size)
*/
int
max_element(struct Vector *v)
{
	int i, N, max;

	N = v->size;
	max = 0;
	for (i = 1;i < N;i++) {
		if (v->value[i] > v->value[max])
			max = i;
	}
	return max;
}

/* Precondition:
	previously allocated Vector v
   Sideeffect:
	None
   Postcondition:
	value of maximal element in v-value in [0, v->size)
*/
float
max_value(struct Vector *v)
{
	int i, N;
	float max;

	N = v->size;
	max = v->value[0];
	for (i = 1;i < N;i++) {
		if (v->value[i] > max)
			max = v->value[i];
	}
	return max;
}
