#include "model.h"


/* Precodnition:
	depth > 0
	learning_rate > 0.0f
	allocated layer_size with individual #depth values
	allocated array of functionpointers function, with #depth values
	allocated array of functionpointers derivative, with #depth values
   Sideeffect:
	None
   Postcondition:
	allocated Model
*/
struct Model *
allocate_model(int depth, float learning_rate, int *layer_size, float (**function) (float), float (**derivative) (float))
{
	struct Model *new;
	int i;

	new = malloc(sizeof(*new));
	new->depth = depth;
	new->learning_rate = learning_rate;
	new->hidden = malloc(sizeof(*new->hidden) * depth);
	new->temp   = malloc(sizeof(*new->temp) * depth);
	new->delta  = malloc(sizeof(*new->delta) * depth);
	new->bias   = malloc(sizeof(*new->bias) * depth);
	new->weight       = malloc(sizeof(*new->weight) * depth);
	new->weight_delta = malloc(sizeof(*new->weight_delta) * depth);
	new->input = allocate_vector(layer_size[0]);
	for (i = 0;i < depth;i++) {
		new->hidden[i] = allocate_vector(layer_size[i + 1]);
		new->temp[i]   = allocate_vector(layer_size[i + 1]);
		new->delta[i]  = allocate_vector(layer_size[i + 1]);
		new->bias[i]   = allocate_vector(layer_size[i + 1]);
		new->weight_delta[i] = allocate_matrix(layer_size[i + 1], layer_size[i]);
		new->weight[i]       = allocate_matrix(layer_size[i + 1], layer_size[i]);
	}
	new->target = allocate_vector(layer_size[depth]);
	new->function   = malloc(sizeof(float (*)(float)) * depth);
	new->derivative = malloc(sizeof(float (*)(float)) * depth);
	for (i = 0;i < depth;i++) {
		new->function[i]   = function[i];
		new->derivative[i] = derivative[i];
	}
	return new;
}

/* Precondition:
	previously allocated Model m
   Sideeffect:
	free's allocated Model m
   Postcondition:
   	None
*/
void
free_model(struct Model *m)
{
	int i, depth;

	depth = m->depth;
	free(m->function);
	free(m->derivative);
	for (i = 0;i < depth;i++) {
		free_vector(m->hidden[i]);
		free_vector(m->temp[i]);
		free_vector(m->delta[i]);
		free_vector(m->bias[i]);
		free_matrix(m->weight[i]);
		free_matrix(m->weight_delta[i]);
	}
	free(m->hidden);
	free(m->temp);
	free(m->delta);
	free(m->bias);
	free(m->weight);
	free(m->weight_delta);
	free_vector(m->input);
	free_vector(m->target);
	free(m);
	return;
}

/* Precodition:
	previously allocated Model m
   Sideeffect:
	m->weight[i] equals random_values, for all i in [0, m->depth)
	m->bias[i] equals random_values, for all i in [0, m->depth)
   Postcondition:
	None
*/
void
randomize_model(struct Model *m)
{
	int i, depth;

	depth = m->depth;
	for (i = 0;i < depth;i++) {
		randomize_matrix(m->weight[i]);
		randomize_vector(m->bias[i]);
	}
	return;
}

/* Precondition:
	previously allocated Model m
	previously allocated Model m
	m->depth == n->depth
	m->weight[i]->size == n->weight[i]->size, for all i in [0, m->depth)
	m->weight[i]->length == n->weight[i]->length, for all i in [0, m->depth)
	m->bias[i]->size == n->bias[i]->size, for all i in [0, m->depth)
   Sideeffect:
	m->weight[i] equals n->weight[i], for all i in [0, m->depth)
	m->bias[i] equals n->bias[i], for all i in [0, m->depth)
   Postcondition:
	None
*/
void
copy_model(struct Model *m, struct Model *n)
{
	int i, depth;

	depth = m->depth;
	for (i = 0;i < depth;i++) {
		copy_matrix(m->weight[i], n->weight[i]);
		copy_vector(m->bias[i], n->bias[i]);
	}
	return;
}

/* Precondition:
	previously allocated Model m
   Sideeffect:
	m->hidden[0] equals m->function[0](m->weight[0] * m->input + m->bias[0])
	m->hidden[i] equals m->function[i](m->weight[i] * m->hidden[i - 1] + m->bias[i]), for all i in [1, m->depth)
   Postcondition:
	None
*/
void
compute_model(struct Model *m)
{
	int i, depth;

	depth = m->depth;
	multiply_matrix_vector(m->weight[0], m->input, m->hidden[0]);
	add_vector(m->bias[0], m->hidden[0], m->hidden[0]);
	apply_function_on_vector(m->hidden[0], m->function[0], m->hidden[0]);
	for (i = 1;i < depth;i++) {
		multiply_matrix_vector(m->weight[i], m->hidden[i - 1], m->hidden[i]);
		add_vector(m->bias[i], m->hidden[i], m->hidden[i]);
		apply_function_on_vector(m->hidden[i], m->function[i], m->hidden[i]);
	}
	return;
}

/* Precondition:
	previously initialized Model m
   Sideeffect:
	m->temp[i] equals m->derivative[i](m->hidden[i]), for all i in [0, m->depth)
	m->delta[m->depth - 1] equals (m->target - m->hidden[depth - 1]) .* m->temp[depth - 1]
	m->delta[i] equals (m->weight[i + 1] * m->delta[i + 1]) .* m->temp[i], for all i in (m->depth - 1, 0]
   Postcondition:
	None
*/
void
train_model(struct Model *m)
{
	int i, depth;

	depth = m->depth;
	/* output layer delta */
	subtract_vector(m->target, m->hidden[depth - 1], m->delta[depth - 1]);
	apply_function_on_vector(m->hidden[depth - 1], m->derivative[depth - 1], m->temp[depth - 1]);
	multiply_vector_entrywise(m->delta[depth - 1], m->temp[depth - 1], m->delta[depth - 1]);
	/* hidden layer delta */
	for (i = depth - 2;i >= 0;i--) {
		multiply_transformed_matrix_vector(m->weight[i + 1], m->delta[i + 1], m->delta[i]);
		apply_function_on_vector(m->hidden[i], m->derivative[i], m->temp[i]);
		multiply_vector_entrywise(m->delta[i], m->temp[i], m->delta[i]);
	}
	return;
}

/* Precondition:
	previously initialized Model m
   Sideeffect:
	m->weight_delta[0] equals m->learning_rate * (m->delta[0] * m->input)
	m->weight_delta[i] equals m->learning_rate * (m->delta[i] * m->hidden[i - 1]), for all i in [1, m->depth)
	m->weight[i] equals m->weight[i] + m->weight_delta[i], for all i in [0, m->depth) and where m->weight[i] is overridden
	m->bias[i] equals m->bias[i] + m->learning_rate * m->delta[i], for all i in [0, m->depth) and where m->bias[i] is overridden
   Postcodnition:
	None
*/
void
apply_change_to_model(struct Model *m)
{
	int i, depth;

	depth = m->depth;
	/* input weight */
	multiply_vector(m->delta[0], m->input, m->weight_delta[0]);
	scale_matrix(m->learning_rate, m->weight_delta[0], m->weight_delta[0]);
	add_matrix(m->weight[0], m->weight_delta[0], m->weight[0]);
	/* input bias */
	scale_vector(m->learning_rate, m->delta[0], m->delta[0]);
	add_vector(m->bias[0], m->delta[0], m->bias[0]);
	for (i = 1;i < depth;i++) {
		/* hidden weight */
		multiply_vector(m->delta[i], m->hidden[i - 1], m->weight_delta[i]);
		scale_matrix(m->learning_rate, m->weight_delta[i], m->weight_delta[i]);
		add_matrix(m->weight[i], m->weight_delta[i], m->weight[i]);
		/* hidden bias */
		scale_vector(m->learning_rate, m->delta[i], m->delta[i]);
		add_vector(m->bias[i], m->delta[i], m->bias[i]);
	}
	return;
}

/* Precondition:
	previously initialized Model m and n
	m->depth == n->depth
	m->input->size == n->input->size
	m->hidden[i]->size == n->hidden[i]->size, for all i in [0, m->depth)
	m->delta[i]->size == n->delta[i]->size, for all i in [0, m->depth)
	m->weight[i]->size == n->weight[i]->size, for all i in [0, m->depth)
	m->weight[i]->length == n->weight[i]->length, for all i in [0, m->depth)
	m->weight_delta[i]->size == n->weight_delta[i]->size, for all i in [0, m->depth)
	m->weight_delta[i]->length == n->weight_delta[i]->length, for all i in [0, m->depth)
	m->bias[i]->size == n->bias[i]->size, for all i in [0, m->depth)
   Sideeffect:
	n->weight_delta[0] equals n->learning_rate * (m->delta[0] * m->input)
	n->weight_delta[i] equals n->learning_rate * (m->delta[i] * m->hidden[i - 1]), for all i in [1, m->depth)
	n->weight[i] equals n->weight[i] + n->weight_delta[i], for all i in [0, m->depth) and where n->weight[i] is overridden
	n->bias[i] equals n->bias[i] + n->learning_rate * m->delta[i], for all i in [0, m->depth) and where n->bias[i] is overridden
   Postcodnition:
	None
*/
void
apply_different_change_model(struct Model *m, struct Model *n)
{
	int i, depth;

	depth = m->depth;
	/* input weight */
	multiply_vector(m->delta[0], m->input, n->weight_delta[0]);
	scale_matrix(n->learning_rate, n->weight_delta[0], n->weight_delta[0]);
	add_matrix(n->weight[0], n->weight_delta[0], n->weight[0]);
	/* input bias */
	scale_vector(n->learning_rate, m->delta[0], n->delta[0]);
	add_vector(m->bias[0], n->delta[0], n->bias[0]);
	for (i = 1;i < depth;i++) {
		/* hidden weight */
		multiply_vector(m->delta[i], m->hidden[i - 1], n->weight_delta[i]);
		scale_matrix(n->learning_rate, n->weight_delta[i], n->weight_delta[i]);
		add_matrix(n->weight[i], n->weight_delta[i], n->weight[i]);
		/* hidden bias */
		scale_vector(n->learning_rate, m->delta[i], n->delta[i]);
		add_vector(m->bias[i], n->delta[i], n->bias[i]);
	}
	return;
}

/* Precondition:
	previous allocated Model m
	previous allocated Vector array state with #(m->depth + 1) values
   Sideeffect:
	m->input equals state[0]
	m->hidden[i] equals state[i + 1], for all i in [0, m->depth)
   Postcondition:
	None
*/
void
fetch_state_from_model(struct Model *m, struct Vector **state)
{
	int i, depth;

	depth = m->depth;
	copy_vector(m->input, state[0]);
	for (i = 0;i < depth;i++)
		copy_vector(m->hidden[i], state[i + 1]);
	return;
}

/* Precondition:
	previous allocated Model m
	previous allocated Vector array state with #(m->depth + 1) values
   Sideeffect:
	m->input equals state[0]
	m->hidden[i] equals state[i + 1], for all i in [0, m->depth)
   Postcondition:
	None
*/
void
load_state_onto_model(struct Model *m, struct Vector **state)
{
	int i, depth;

	depth = m->depth;
	copy_vector(state[0], m->input);
	for (i = 0;i < depth;i++)
		copy_vector(state[i + 1], m->hidden[i]);
	return;

}
