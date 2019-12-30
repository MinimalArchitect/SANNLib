#include <stdlib.h>
#include <stdio.h>

#include "model.h"

void
init_model(struct Model *model)
{
	int a = rand() % 4;

	switch(a) {
	case 0:
		model->input->value[0] = 0.0f;
		model->input->value[1] = 0.0f;
		model->target->value[0] = 0.0f;
		break;
	case 1:
		model->input->value[0] = 0.0f;
		model->input->value[1] = 1.0f;
		model->target->value[0] = 0.0f;
		break;
	case 2:
		model->input->value[0] = 1.0f;
		model->input->value[1] = 0.0f;
		model->target->value[0] = 0.0f;
		break;
	case 3:
		model->input->value[0] = 1.0f;
		model->input->value[1] = 1.0f;
		model->target->value[0] = 1.0f;
		break;
	}
	return;
}

float ReLu(float value)
{
	return (value > 0.0f)?value:0.01f * value;
}

float DReLu(float value)
{
	return (value > 0.0f)?1.0f:-0.01f;
}

int main(int argc, char *argv[])
{
	int depth = 3;
	float learning_rate = 0.001;

	int layer_size[] = {2, 2, 2, 1};

	float (*function_array[]) (float) = {ReLu, ReLu, ReLu};
	float (*derivative_array[]) (float) = {DReLu, DReLu, DReLu};

	struct Model *model = allocate_model(depth, learning_rate, layer_size, function_array, derivative_array);

	randomize_model(model);

	int t;

	for (t = 0;t < 1000;t++) {
		init_model(model);
		compute_model(model);

		train_model(model);
		apply_change_to_model(model);

		printf("%f - %f\n", model->hidden[depth - 1]->value[0], model->target->value[0]);
	}

	exit(EXIT_SUCCESS);
}
