#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"
#include "matrix.h"

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

typedef struct models
{
	int N;
	float learning_rate;

	vector *input;

	vector **hidden;
	vector **temp;
	vector **delta;
	vector **bias;

	vector *target;

	matrix **weight;
	matrix **weight_delta;

	float (**function) (float);
	float (**derivative) (float);
} model;

model *
init_model(int N, float learning_rate, int *layer_size, float (**function) (float), float (**derivative) (float))
{
	model *new;
	int i;

	new = (model *) malloc(sizeof(model));
	new->N = N;
	new->learning_rate = learning_rate;
	new->hidden = (vector **) malloc(sizeof(vector *) * N);
	new->temp   = (vector **) malloc(sizeof(vector *) * N);
	new->delta  = (vector **) malloc(sizeof(vector *) * N);
	new->bias   = (vector **) malloc(sizeof(vector *) * N);
	new->weight       = (matrix **) malloc(sizeof(matrix *) * N);
	new->weight_delta = (matrix **) malloc(sizeof(matrix *) * N);
	new->input = init_vector(layer_size[0]);
	for (i = 0;i < N;i++) {
		new->hidden[i] = init_vector(layer_size[i + 1]);
		new->temp[i]   = init_vector(layer_size[i + 1]);
		new->delta[i]  = init_vector(layer_size[i + 1]);
		new->bias[i]   = init_vector(layer_size[i + 1]);
		new->weight_delta[i] = init_matrix(layer_size[i + 1], layer_size[i]);
		new->weight[i]       = init_matrix(layer_size[i + 1], layer_size[i]);
	}
	new->target = init_vector(layer_size[N]);
	new->function   = malloc(sizeof(float (*)(float)) * N);
	new->derivative = malloc(sizeof(float (*)(float)) * N);
	for (i = 0;i < N;i++) {
		new->function[i]   = function[i];
		new->derivative[i] = derivative[i];
	}
	return new;
}

void
random_weights_model(model *m)
{
	int i, N;

	N = m->N;
	for (i = 0;i < N;i++) {
		random_matrix(m->weight[i]);
		random_vector(m->bias[i]);

	}
	return;
}

int
compute_model(model *m)
{
	int i, N, err = 0;

	N = m->N;
	err |= mul_matrix_vector(m->weight[0], m->input, m->hidden[0]);
	err |= add_vector(m->bias[0], m->hidden[0], m->hidden[0]);
	err |= function_vector(m->hidden[0], m->function[0], m->hidden[0]);
	for (i = 1;i < N;i++) {
		err |= mul_matrix_vector(m->weight[i], m->hidden[i - 1], m->hidden[i]);
		err |= add_vector(m->bias[i], m->hidden[i], m->hidden[i]);
		err |= function_vector(m->hidden[i], m->function[i], m->hidden[i]);
	}
	return err;
}

int
train_model(model *m)
{
	int i, N, err = 0;

	N = m->N;
	/* output layer delta */
	err |= sub_vector(m->target, m->hidden[N - 1], m->delta[N - 1]);
	err |= function_vector(m->hidden[N - 1], m->derivative[N - 1], m->temp[N - 1]);
	err |= mul_vector_had(m->delta[N - 1], m->temp[N - 1], m->delta[N - 1]);
	/* hidden layer delta */
	for (i = N - 2;i >= 0;i--) {
		err |= mul_matrix_vector_rev(m->weight[i + 1], m->delta[i + 1], m->delta[i]);
		err |= function_vector(m->hidden[i], m->derivative[i], m->temp[i]);
		err |= mul_vector_had(m->delta[i], m->temp[i], m->delta[i]);
	}
	return err;
}

int
apply_change(model *m)
{
	int i, N;
	int err = 0;

	N = m->N;
	/* input weight */
	err |= mul_vector(m->delta[0], m->input, m->weight_delta[0]);
	err |= mul_matrix_scalar(m->learning_rate, m->weight_delta[0], m->weight_delta[0]);
	err |= add_matrix(m->weight[0], m->weight_delta[0], m->weight[0]);
	/* input bias */
	err |= mul_vector_scalar(m->learning_rate, m->delta[0], m->delta[0]);
	err |= add_vector(m->bias[0], m->delta[0], m->bias[0]);
	for (i = 1;i < N;i++) {
		/* hidden weight */
		err |= mul_vector(m->delta[i], m->hidden[i - 1], m->weight_delta[i]);
		err |= mul_matrix_scalar(m->learning_rate, m->weight_delta[i], m->weight_delta[i]);
		err |= add_matrix(m->weight[i], m->weight_delta[i], m->weight[i]);
		/* hidden bias */
		err |= mul_vector_scalar(m->learning_rate, m->delta[i], m->delta[i]);
		err |= add_vector(m->bias[i], m->delta[i], m->bias[i]);
	}
	return err;
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
		apply_change(m);

//		print_vector(m->hidden[N - 1]);
	}
	exit(EXIT_SUCCESS);
}
