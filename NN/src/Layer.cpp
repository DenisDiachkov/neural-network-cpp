#include "..\include\Layer.hpp"

Layer::Layer(int size, int next_size, const Function& activation, int seed) :
	values(size),
	biases_weights(next_size),
	biases_grads(next_size),
	weights(size, Vector(next_size)),
	grads(size, Vector(next_size)),
	activation(activation)
{
	for (real& i : values)
		i = getRandomReal();
	for (real& i : biases_weights)
		i = getRandomReal();
	for (Vector& i : weights)
		for (real& j : i)
			j = getRandomReal();
}

int Layer::size() const {
	return this->values.size();
}

int Layer::next_size() const {
	return this->weights[0].size();
}

Vector Layer::estimateValues(const  Vector& v) const {
	assert(v.size() == this->size());
	Vector activated_val = this->activation(v);
	return activated_val * this->weights + this->biases_weights;
}

Vector Layer::feed(const  Vector& v) {
	assert(v.size() == this->size());
	return estimateValues(this->values = v);
}

Vector Layer::estimateError(const  Vector& error, const  Vector& next_vals) const {
	assert(error.size() == this->next_size());
	assert(next_vals.size() == this->next_size());

	return this->weights * error;
}

void Layer::estimateGradients(const  Vector& error, const  Vector& next_vals) {
	this->grads = this->activation(this->values).cartesianProduct(error);
	this->biases_grads += error;
}

void Layer::changeWeights(real lr) {
	this->weights += lr * this->grads;
	this->grads = Matrix(this->size(), Vector(this->next_size()));
	this->biases_weights += this->biases_grads;
	this->biases_grads = Vector(this->next_size());
}