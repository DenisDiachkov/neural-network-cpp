#pragma once

#include "util.h"

class Matrix;

class Vector {
private:
	std::vector<real> vals;
public:
	Vector();
	Vector(const std::vector<real>& v);
	Vector(int size, real val = 0.0L);
	std::vector<real>::const_iterator begin() const;
	std::vector<real>::const_iterator end() const;
	std::vector<real>::iterator begin();
	std::vector<real>::iterator end();
	real& operator[](int idx);
	const real& operator[](int idx) const;
	unsigned size() const;
	Vector operator-(const Vector& v) const;
	void operator-=(const Vector& v);
	Vector operator*(const Vector& v) const;
	void operator*=(const Vector& v);
	friend Vector operator*(const real& a, const Vector& v);
	Vector operator+(const Vector& v) const;
	void operator+=(const Vector& v);
	Vector operator*(const Matrix& b) const;
	Matrix cartesianProduct(const Vector& b);
	real dot(const Vector& b) const;
	real mean();
	Vector abs();
};