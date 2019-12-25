#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"
#include "matrix.h"
#include "model.h"

typedef struct experiences {
	int N;
	vector **state;
	int action;
	float reward;
	vector **state_prediction;
} experience;

int init_experience(experience *e, model *m);

void
print_vector(vector *v)
{
	int i, N;

	N = v->size;
	for (i = 0;i < N;i++)
		printf("%f, ", v->value[i]);
	printf("\n");
	return;
}

void
print_matrix(matrix *m)
{
	int i, j, N, M;

	M = m->size;
	N = m->length;
	for (j = 0;j < M;j++) {
		for (i = 0;i < N;i++)
			printf("%f, ", m->value[j * N + i]);
		printf("\n");
	}
	return;
}


float sigmoid(float v)
{
	return 1.0f / (1.0f + exp(-v));
}

float Dsigmoid(float v)
{
	return (1.0f - v) * v;
}

int
main(int argc, char *argv[])
{
	int t, N = 2;
	float learning_rate = 0.1;
	int layer_size[] = {2, 3, 1};
	float (*function_array[]) (float) = {sigmoid, sigmoid};
	float (*derivative_array[]) (float) = {Dsigmoid, Dsigmoid};

	model *m = init_model(N, learning_rate, layer_size, function_array, derivative_array);

	random_weights_model(m);
	for (t = 0;t < 100;t++) {
		m->input->value[0] = 0.0;
		m->input->value[1] = 0.0;
		compute_model(m);

		m->target->value[0] = 1.0f;
		train_model(m);
		apply_change_model(m);

//		print_vector(m->hidden[N - 1]);
	}
	exit(EXIT_SUCCESS);
}
