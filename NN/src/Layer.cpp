#include "..\include\Layer.hpp"

Layer::Layer() {}

Layer::Layer(size_t size, size_t next_size, const Function& activation) :
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

Layer::Layer(Layer&& layer) noexcept :
	values(std::move(layer.values)),
	biases_weights(std::move(layer.biases_weights)),
	biases_grads(std::move(layer.biases_grads)),
	weights(std::move(layer.weights)),
	grads(std::move(layer.grads)),
	activation(std::move(layer.activation))
{
}

Layer::Layer(const Layer& layer) :
	values(layer.values),
	biases_weights(layer.biases_weights),
	biases_grads(layer.biases_grads),
	weights(layer.weights),
	grads(layer.grads),
	activation(layer.activation)
{
}

Layer& Layer::operator=(const Layer& layer)
{
	this->values = layer.values;
	this->biases_weights = layer.biases_weights;
	this->biases_grads = layer.biases_grads;
	this->weights =  layer.weights;
	this->grads = layer.grads;
	this->activation = layer.activation;
	return *this;
}

size_t Layer::size() const {
	return this->values.size();
}

size_t Layer::next_size() const {
	return (this->weights)[0].size();
}

Vector Layer::estimateValues(const  Vector& v) const {
#ifdef __123_NN_DEBUG
	assert(v.size() == this->size());
#endif
	Vector activated_val = this->activation(v);
	return activated_val * this->weights + this->biases_weights;
}

Vector Layer::feed(const  Vector& v) {
#ifdef __123_NN_DEBUG
	assert(v.size() == this->size());
#endif
	return estimateValues(this->values = v);
}

Vector Layer::estimateError(const  Vector& error) const {
#ifdef __123_NN_DEBUG
	assert(error.size() == this->next_size());
#endif
	return this->weights * error;
}

void Layer::estimateGradients(const  Vector& error) {
	this->grads = (this->activation(this->values).cartesianProduct(error));
	this->biases_grads += error;
}