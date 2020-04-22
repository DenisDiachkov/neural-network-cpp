#pragma once
#include "util.h"
#include "Matrix.hpp"
//#include "NN.hpp"
class NN;

class Optimizer {
protected:
	int t;
	NN& nn;
	Optimizer(NN& nn, real lr);
public:
	real lr;
	virtual void step() = 0;
	void limit_weights(real l = -1.0 + EPS, real r = 1.0 - EPS) ;
	void zero_grad() ;
};

class Adam : public Optimizer {
private:
	real beta_1, beta_2, epsilon;
	std::vector<Matrix> m;
	std::vector<Matrix> v;
	std::vector<Vector> bias_m;
	std::vector<Vector> bias_v;
public:
	Adam(NN& nn, real lr = 0.001, real beta_1 = 0.9, real beta_2 = 0.999, real epsilon = EPS);
	void step() override;
};

class SGD : public Optimizer {
private:
	std::vector<Matrix> moments;
	std::vector<Vector> bias_moments;
	real momentum, decay;
	bool Nesterov;
public:
	SGD(NN& nn, real lr = 0.001L, real momentum = 0.0L, real decay = 0.0L, bool Nesterov = false);
	void step() override;
};