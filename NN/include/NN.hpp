#pragma	once

#include "util.h"
#include "Layer.hpp"
#include "Loss.hpp"
#include "Optimizer.hpp"

class NN {
public:
	std::vector<Layer> layers;
	NN(std::vector<size_t> sizes, const Function& activation);
	void feedForward(Vector input);
	Vector predict(Vector input) const;
	Vector getOutput() const;
	void backPropagation(Vector loss);
	void fit(const Matrix& trainX, const Matrix& trainY, int epochs, int batch_size, Optimizer* optimizer, Loss* loss);
};

