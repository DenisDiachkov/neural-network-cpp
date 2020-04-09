#pragma	once

#include "util.h"
#include "Layer.hpp"

class NN {
public:
	std::vector<Layer> layers;
	NN(std::vector<int> sizes, const Function& activation, int seed = 42);
	void feedForward(Vector input);
	Vector predict(Vector input);
	void backPropagation(Vector loss, real lr);
	void fit(const Matrix& trainX, const Matrix& trainY, int epochs, real lr);
};

