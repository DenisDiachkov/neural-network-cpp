#include "..\include\Function.hpp"

Function::Function() {}

Function::Function(const std::function<real(real)>& f) : fun(f) {}
Function::Function(const Function& fun) : fun(fun.fun) {}

real Function::operator()(const real& x) const {
	return fun(x);
};

Vector Function::operator()(const Vector& x) const {
	Vector res(x.size());
	for (size_t i = 0; i < res.size(); ++i) {
		res[i] = fun(x[i]);
	}
	return res;
};

Function Function::derivative() const {
	return Function([this](real x) {return (this->fun(x + EPS) - this->fun(x)) / EPS; });
}
