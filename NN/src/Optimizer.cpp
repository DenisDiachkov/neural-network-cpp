#include "..\include\Optimizer.hpp"
#include "..\include\NN.hpp"

Optimizer::Optimizer(NN& nn, real lr) : lr(lr), nn(nn) {
	this->t = 0;
	this->lr = lr;
	this->nn = nn;
}

void Optimizer::zero_grad()
{
	for (Layer& layer : this->nn.layers) {
		layer.grads = 0;
		layer.biases_grads = 0;
	}
}

void Optimizer::limit_weights(real l, real r)
{
	for (Layer& layer : this->nn.layers) {
		layer.weights.limit(l, r);
		layer.biases_weights.limit(l, r);
	}
}

Adam::Adam(NN& nn, real lr, real beta_1, real beta_2, real epsilon) :
	Optimizer(nn, lr), beta_1(beta_1), beta_2(beta_2), epsilon(epsilon)
{
	this->m.reserve(nn.layers.size()-1);
	this->v.reserve(nn.layers.size()-1);
	this->bias_m.reserve(nn.layers.size()-1);
	this->bias_v.reserve(nn.layers.size()-1);
	for (auto layer = nn.layers.cbegin(); layer != --nn.layers.cend(); ++layer) {
		this->m.push_back(Matrix(layer->size(), layer->next_size(), 0.0L));
		this->v.push_back(Matrix(layer->size(), layer->next_size(), 0.0L));
		this->bias_m.push_back(Vector(layer->next_size(), 0.0L));
		this->bias_v.push_back(Vector(layer->next_size(), 0.0L));
	}
}

void Adam::step()
{
	++this->t;
	for (int i = 0; i < nn.layers.size() - 1; ++i) {
		//m = b1 * m + (1 - b2) * g
		m[i] = beta_1 * m[i] + (1.0L - beta_1) * (nn.layers[i].grads);
		//v = b2 * v + (1 - b2) * g^2
		v[i] = beta_2 * v[i] + (1.0L - beta_2) * (nn.layers[i].grads.pow(2.0L));
		//mh = m / (1 - b1^t)
		Matrix m_hat(powl(1.0L - powl(beta_1, (real)t), -1.0L) * m[i]);
		//vh = v / (1 - b2^t)
		Matrix v_hat(powl(1.0L - powl(beta_2, (real)t), -1.0L) * v[i]);
		//w += lr * mh / (sqrt(vh) + eps)
		nn.layers[i].weights -= lr * m_hat.hadamardProduct((v_hat.pow(0.5L) + this->epsilon).pow(-1.0L));

		//m = b1 * m + (1 - b2) * g
		bias_m[i] = beta_1 * bias_m[i] + (1.0L - beta_1) * (nn.layers[i].biases_grads);
		//v = b2 * v + (1 - b2) * g^2
		bias_v[i] = beta_2 * bias_v[i] + (1.0L - beta_2) * (nn.layers[i].biases_grads.pow(2.0L));
		//mh = m / (1 - b1^t)
		Vector bias_m_hat(powl(1.0L - powl(beta_1, (real)t), 1.0L) * bias_m[i]);
		//vh = v / (1 - b2^t)
		Vector bias_v_hat(powl(1.0L - powl(beta_2, (real)t), 1.0L) * bias_v[i]);
		//w -= lr * mh / (sqrt(vh) + eps)
		nn.layers[i].biases_weights -= lr * bias_m_hat.hadamardProduct((bias_v_hat.pow(0.5L) + this->epsilon).pow(-1.0L));

	}
}

SGD::SGD(NN& nn, real lr, real momentum, real decay, bool Nesterov) : 
	Optimizer(nn, lr), 
	momentum(momentum), 
	decay(decay), 
	Nesterov(Nesterov) 
{
	this->moments.reserve(nn.layers.size()-1);
	this->bias_moments.reserve(nn.layers.size()-1);
	for (auto layer = nn.layers.cbegin(); layer != --nn.layers.cend(); ++layer) {
		this->moments.push_back(Matrix(layer->size(), layer->next_size(), 0.0L));
		this->bias_moments.push_back(Vector(layer->next_size()));
	}
}

void SGD::step() {
	++t;
	real adjust_lr = this->lr;
	if (decay > 0)
		adjust_lr /= (1.0L + decay * t);

	for (int i = 0; i < nn.layers.size() - 1; ++i) {
		Matrix velocity = momentum * moments[i] - adjust_lr * nn.layers[i].grads;
		Vector bias_velocity = momentum * bias_moments[i] - adjust_lr * nn.layers[i].biases_grads;
		moments[i] = velocity;
		bias_moments[i] = bias_velocity;

		if (Nesterov) {
			nn.layers[i].weights += momentum * velocity - adjust_lr * nn.layers[i].grads;
			nn.layers[i].biases_weights += momentum * bias_velocity - adjust_lr * nn.layers[i].biases_grads;
		}
		else {
			nn.layers[i].weights += velocity;
			nn.layers[i].biases_weights += bias_velocity;
		}
	}
}

