#pragma once
#include "util.h"
#include "Function.hpp"

class Loss {
public:
	virtual real operator()(Vector diff) const = 0;
	virtual Vector derivative(Vector diff) const = 0;

};

class CrossEntropyLoss : public Loss {
public:
	real operator()(Vector diff) const override ;

};

class MSELoss : public Loss {
public:
	real operator()(Vector diff) const override;
	Vector derivative(Vector diff) const override;
};

class L1Loss : public Loss {
public:
	real operator()(Vector diff) const override;
};