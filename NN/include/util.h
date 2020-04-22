#pragma once

#include <random>
#include <functional>
#include <vector>
#include <assert.h>
#include <cmath>
#include <memory>
#include <iostream>
#include <algorithm>
#include <conio.h>
#define __123_NN_DEBUG 1

typedef long double real;
class Vector;
class Matrix;

const real EPS = 1e-7;// sqrtl(std::numeric_limits<real>::epsilon());


inline real getRandomReal() {
	static std::mt19937 GENERATOR_ENGINE = std::mt19937(32);
	static std::uniform_real_distribution<double> DISTRIBUTION(-1.0, 1.0);

	return DISTRIBUTION(GENERATOR_ENGINE);
}

inline real getRandomRealPositive() {
	static std::mt19937 GENERATOR_ENGINE = std::mt19937(32);
	static std::uniform_real_distribution<double> DISTRIBUTION(0.0, 1.0);

	return DISTRIBUTION(GENERATOR_ENGINE);
}

