#include "..\include\no_silly_warnings_please.h"
#include <iostream>
#include <cmath>
#include "..\include\NN.hpp"
#include <chrono>
#include "..\..\mnist-master\include\mnist\mnist_reader_less.hpp"

int main() {


	// Load MNIST data
	//mnist::MNIST_dataset<uint8_t, uint8_t> dataset = mnist::read_dataset<uint8_t, uint8_t>();

	//std::cout << "Nbr of training images = " << dataset.training_images.size() << std::endl;
	//std::cout << "Nbr of training labels = " << dataset.training_labels.size() << std::endl;
	//std::cout << "Nbr of test images = " << dataset.test_images.size() << std::endl;
	//std::cout << "Nbr of test labels = " << dataset.test_labels.size() << std::endl;

	//std::vector<std::vector<real> >  trainX, trainY;

	//const size_t DATA_SIZE = 1000;

	//for (auto& img : dataset.training_images) {
	//	trainX.push_back(std::vector<real>());
	//	for (uint8_t& pix : img) {
	//		trainX.back().push_back(pix / 255.0L);
	//	}
	//	if (trainX.size() == DATA_SIZE)
	//		break;
	//}
	//for (auto& lab : dataset.training_labels) {
	//	trainY.push_back(std::vector<real>(1, lab == 0 ? 1.0L : 0));
	//	if (trainY.size() == DATA_SIZE)
	//		break;
	//}

	//Matrix X(trainX), Y(trainY);

	Matrix X(1000, 1), Y(1000, 1);
	for (int i = 0; i < 1000; ++i) {
		X[i][0] = getRandomReal();
		Y[i][0] = (sinl(X[i][0]) + 1) / 2.0L;
	}


	auto start = std::chrono::steady_clock::now();
	NN nn = NN({ X[0].size(), 100, 20,  1 }, Function([](real r) { return 1 / (1 + exp(-r)); }));

	Optimizer* optimizer = new SGD(nn, 1, 0.8, 1e-16, true);
	Loss* loss = new MSELoss();
	nn.fit(X, Y, 200, 100, optimizer, loss);
	auto end = std::chrono::steady_clock::now();

	std::cout << nn.predict(Vector(1, acos(-1) / 4))[0] << std::endl;

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds elapsed\n";
}