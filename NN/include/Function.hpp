#pragma once

#include "util.h"
#include "Vector.hpp"

class Function {
private:
	std::function<real(real)> fun;
public:
	Function(const std::function<real(real)>& f);
	Function(const Function& fun);
	real operator()(const real& x) const;
	Vector operator()(const Vector& x) const;
	Function derivative();
};

