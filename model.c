#include <stdlib.h>

#include "vector.h"
#include "matrix.h"

#include "model.h"

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
apply_change_model(model *m)
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
apply_different_change_model(model *m, model *n)
{
	int i, N;
	int err = 0;

	N = m->N;
	/* input weight */
	err |= mul_vector(m->delta[0], m->input, n->weight_delta[0]);
	err |= mul_matrix_scalar(n->learning_rate, n->weight_delta[0], n->weight_delta[0]);
	err |= add_matrix(n->weight[0], n->weight_delta[0], n->weight[0]);
	/* input bias */
	err |= mul_vector_scalar(n->learning_rate, m->delta[0], n->delta[0]);
	err |= add_vector(m->bias[0], n->delta[0], n->bias[0]);
	for (i = 1;i < N;i++) {
		/* hidden weight */
		err |= mul_vector(m->delta[i], m->hidden[i - 1], n->weight_delta[i]);
		err |= mul_matrix_scalar(n->learning_rate, n->weight_delta[i], n->weight_delta[i]);
		err |= add_matrix(n->weight[i], n->weight_delta[i], n->weight[i]);
		/* hidden bias */
		err |= mul_vector_scalar(n->learning_rate, m->delta[i], n->delta[i]);
		err |= add_vector(m->bias[i], n->delta[i], n->bias[i]);
	}
	return err;
}
