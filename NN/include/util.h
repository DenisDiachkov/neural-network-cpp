#pragma once

#include <random>
#include <functional>
#include <vector>
#include <assert.h>
#include <cmath>

typedef long double real;
const real EPS = sqrtl(std::numeric_limits<real>::epsilon());

inline real getRandomReal() {
	static std::mt19937 GENERATOR_ENGINE = std::mt19937(32);
	static std::uniform_real_distribution<double> DISTRIBUTION(0.0, 1.0);

	return DISTRIBUTION(GENERATOR_ENGINE);
}

