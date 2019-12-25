#ifndef VECTOR_H
#define VECTOR_H

typedef struct vectors {
	float *value;
	int size;
} vector;

vector *init_vector(int _size);
void free_vector(vector *v);
void random_vector(vector *v);
int copy_vector(vector *a, vector *o);
int add_vector(vector *a, vector *b, vector *o);
int sub_vector(vector *a, vector *b, vector *o);
int mul_vector_scalar(float l, vector *b, vector *o);
int mul_vector_had(vector *a, vector *b, vector *o);
int div_vector_had(vector *a, vector *b, vector *o);
int function_vector(vector *i, float (*func)(float), vector *o);


#endif /* VECTOR_H */
