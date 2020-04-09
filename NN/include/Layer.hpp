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
	Layer(int size, int next_size, const Function& activation, int seed = 42);
	int size() const;
	int next_size() const;
	Vector estimateValues(const  Vector& v) const;
	Vector feed(const  Vector& v);
	Vector estimateError(const  Vector& error, const  Vector& next_vals) const;
	void estimateGradients(const  Vector& error, const  Vector& next_vals);
	void changeWeights(real lr);
};
