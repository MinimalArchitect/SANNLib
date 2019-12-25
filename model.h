#include <stdlib.h>

#include "vector.h"
#include "matrix.h"

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

model *init_model(int N, float learning_rate, int *layer_size, float (**function) (float), float (**derivative) (float));
void random_weights_model(model *m);
int compute_model(model *m);
int train_model(model *m);
int apply_change_model(model *m);
int apply_different_change_model(model *m, model *n);

/* TODO */

int fetch_state_model();
int load_state_model();
