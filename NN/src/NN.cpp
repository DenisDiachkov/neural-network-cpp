#include "..\include\NN.hpp"

NN::NN(std::vector<size_t> sizes, const Function& activation) {
	layers.reserve(sizes.size());
	for (size_t i = 0; i < sizes.size() - 1; ++i)
		layers.push_back(std::move(Layer(sizes[i], sizes[i + 1], activation)));
	layers.push_back(std::move(Layer(sizes.back(), 0, activation)));
}

void NN::feedForward(Vector input) {
#ifdef __123_NN_DEBUG
	assert(input.size() == layers.begin()->size());
#endif
	for (size_t i = 0; i < this->layers.size() - 1; ++i) {
		input = layers[i].feed(input); 
	}
	layers.back().values = input;
}

Vector NN::predict(Vector input) const {
	for (size_t i = 0; i < this->layers.size() - 1; ++i) {
		input = layers[i].estimateValues(input);
	}
	return this->layers.back().activation(input);
}

Vector NN::getOutput() const
{
	return this->layers.back().activation(this->layers.back().values);
}

void NN::backPropagation(Vector loss) {
#ifdef __123_NN_DEBUG
	assert(layers.size() > 1U);
#endif
	for(size_t i = layers.size() - 1; i --> 0;) {
		loss *= layers.back().activation.derivative()(layers[i + 1].values);
		layers[i].estimateGradients(loss);

		loss = layers[i].estimateError(loss);
	}
}

void NN::fit(const Matrix& trainX, const Matrix& trainY, int epochs, int batch_size, Optimizer *optimizer, Loss *loss) {
#ifdef __123_NN_DEBUG
	assert(trainX.size()[0] == trainY.size()[0]);
#endif
	optimizer->lr /= batch_size;
	const size_t DATA_SIZE = trainX.size()[0];
	for(size_t epoch = 1; epoch <= epochs; ++epoch) {
		real avg_loss = 0;
		for(size_t i = 0; i < DATA_SIZE; i += batch_size) {
			real batch_loss = 0;
			for(size_t j = i; j < std::min(i + batch_size, DATA_SIZE); ++j) {
				this->feedForward(trainX[j]);
				Vector diff = this->getOutput() - trainY[j];
				this->backPropagation(loss->derivative(diff));
				avg_loss += (*loss)(diff);
				batch_loss += (*loss)(diff);
			}
			optimizer->step();
			optimizer->zero_grad();
			printf("\r%.15f of the %zu epoch, batch loss = %.15f", i * 100.L / DATA_SIZE, epoch, batch_loss / batch_size);
		}
		avg_loss /= trainX.size()[0];
		std::cout << "\tEpoch #" << epoch << " \tAvgLoss: " << avg_loss << std::endl;
	}
	optimizer->lr *= batch_size;
}
