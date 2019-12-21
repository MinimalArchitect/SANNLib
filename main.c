#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"
#include "matrix.h"


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
	int i;
	const int N = 2;

	float learning_rate = 0.5;

	vector *input, *hidden[N], *temp[N];
	vector *target, *delta[N];

	matrix *weight[N];
	matrix *weight_delta[N];

	/* computing */
	mul_matrix_vector(weight[0], input, hidden[0]);
	function_vector(hidden[0], sigmoid, hidden[0]);
	for (i = 1;i < N;i++) {
		mul_matrix_vector(weight[i], hidden[i - 1], hidden[i]);
		function_vector(hidden[i], sigmoid, hidden[i]);
	}

	/* learning */
	/* output layer delta */
	sub_vector(hidden[N - 1], target, delta[N - 1]);
	function_vector(hidden[N - 1], Dsigmoid, temp[N - 1]);
	mul_vector_had(delta[N - 1], temp[N - 1], delta[N - 1]);

	/* hidden layer delta */
	for (i = N - 2;i >= 0;i--) {
		mul_matrix_vector_rev(weight[i + 1], delta[i + 1], delta[i]);
		function_vector(hidden[i], Dsigmoid, temp[i]);
		mul_vector_had(delta[i], temp[i], delta[i]);
	}

	/* adjusting */
	mul_vector(delta[0], input, weight_delta[0]);
	add_matrix(weight[0], weight_delta[0], weight[0]);

	for (i = 1;i < N;i++) {
		mul_vector(delta[i], hidden[i - 1], weight_delta[i]);
		mul_matrix_scalar(learning_rate, weight_delta[i], weight_delta[i]);
		add_matrix(weight[i], weight_delta[i], weight[i]);
	}

	exit(EXIT_SUCCESS);
}
