#include <iostream>
#include <cmath>
#include "..\include\NN.hpp"


int main() {
	
	
	Vector v(std::vector<real>{1,2,3});
	std::cout << v.mean() << std::endl;
	//std::cout << derivative([](real r) {return r * r; })(3.0L) << std::endl;
	NN nn = NN({ 3,5, 100, 5, 2}, Function([](real r) { return 1 / (1 + exp(-r)) ; }), 4123);
	Matrix X = Matrix(std::vector<std::vector<real>>{ {.1, .2, .3}, { .9, .3, 0 }, { 1,1,1 }});
	Matrix Y = Matrix(std::vector<std::vector<real>>{ {1,1}, { 0.5, 0.5 }, { 0,0 }});
	
	nn.fit(X, Y, 1000, 10);
	//	int t = 100; 
	// while(t--)nn.backPropagation((Vector(std::vector<real>{.4, 0.3 }) - (nn.predict(Vector(std::vector<real>{ 1, 1 })))), 1);

	std::cout << nn.predict((Vector(std::vector<real>{ 1, 1, 1 })))[0] << " " << nn.predict(Vector(std::vector<real>{ 1, 1, 1 }))[1];
}