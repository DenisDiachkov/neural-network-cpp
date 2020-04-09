#include "..\include\NN.hpp"
#include <iostream>

NN::NN(std::vector<int> sizes, const Function& activation, int seed) {
	/*TODO alloc*/
	for (int i = 0; i < sizes.size() - 1; ++i)
		layers.push_back(Layer(sizes[i], sizes[i + 1], activation, seed));
	layers.push_back(Layer(sizes.back(), 0, activation, seed));
}

void NN::feedForward(Vector input) {
	assert(input.size() == layers.begin()->size());
	for (int i = 0; i < this->layers.size() - 1; ++i) {
		input = layers[i].feed(input);
	}
	layers.back().values = input;
}

Vector NN::predict(Vector input) {
	feedForward(input);
	return layers.back().values;
}

void NN::backPropagation(Vector loss, real lr) {
	for (int i = layers.size() - 2; i >= 0; --i) {
		loss *= layers.back().activation.derivative()(layers[i + 1].values);
		layers[i].estimateGradients(loss, layers[i + 1].values);
		layers[i].changeWeights(lr);

		loss = layers[i].estimateError(loss, layers[i + 1].values);
	}
}

void NN::fit(const Matrix& trainX, const Matrix& trainY, int epochs, real lr) {
	assert(trainX.size()[0] == trainY.size()[0]);
	for (int epoch = 1; epoch <= epochs; ++epoch) {
		Vector loss;
		real avg_loss = 0;
		for (int i = 0; i < trainX.size()[0]; ++i) {
			avg_loss += (loss = (trainY[i] - this->predict(trainX[i]))).abs().mean();
			this->backPropagation(loss, lr);
		}
		avg_loss /= trainX.size()[0];
		std::cout << "Epoch #" << epoch << " \tAvgLoss: " << avg_loss << std::endl;
	}

}
