#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>

#include "vector.h"
#include "matrix.h"

struct Model
{
	int depth;
	float learning_rate;

	struct Vector *input;

	struct Vector **hidden;
	struct Vector **temp;
	struct Vector **delta;
	struct Vector **bias;

	struct Vector *target;

	struct Matrix **weight;
	struct Matrix **weight_delta;

	float (**function) (float);
	float (**derivative) (float);
};

struct Model *allocate_model(int depth, float learning_rate, int *layer_size, float (**function) (float), float (**derivative) (float));
void free_model(struct Model *m);
void randomize_model(struct Model *m);
void copy_model(struct Model *m, struct Model *n);
void compute_model(struct Model *m);
void train_model(struct Model *m);
void apply_change_to_model(struct Model *m);
void apply_change_to_different_model(struct Model *m, struct Model *n);
void fetch_state_from_model(struct Model *m, struct Vector **state);
void load_state_onto_model(struct Model *m, struct Vector **state);

#endif /* MODEL_H */
