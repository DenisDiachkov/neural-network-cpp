#pragma once

#include "util.h"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Function.hpp"

class Layer {
public:
	Vector values, biases_weights, biases_grads;
	Matrix weights, grads;
	Function activation;
	Layer();
	explicit Layer(size_t size, size_t next_size, const Function& activation);
	explicit Layer(Layer&&) noexcept;
	explicit Layer(const Layer&);
	Layer& operator=(const Layer&);
	size_t size() const;
	size_t next_size() const;
	Vector estimateValues(const  Vector& v) const;
	Vector feed(const  Vector& v);
	Vector estimateError(const  Vector& error) const;
	void estimateGradients(const  Vector& error);
};
