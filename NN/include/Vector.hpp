#pragma once

#include "util.h"

class Vector {
private:
	std::vector<real>::iterator _begin, _end;
	std::vector<real>::const_iterator _cbegin, _cend;
	std::vector<real> vals;
	void init_iterators(const std::vector<real>& v);
public:
	Vector();
	explicit Vector(const std::vector<real>& v);
	explicit Vector(size_t size, real val = 0.0L);
	Vector(const Vector&);
	Vector& operator=(const Vector&);
	std::vector<real>::const_iterator begin() const;
	std::vector<real>::const_iterator end() const;
	std::vector<real>::iterator begin();
	std::vector<real>::iterator end();
	real& operator[](size_t idx);
	const real& operator[](size_t idx) const;
	unsigned size() const;
	Vector operator-(const Vector& v) const;
	void operator-=(const Vector& v);
	Vector operator*(const Vector& v) const;
	void operator*=(const Vector& v);
	friend Vector operator*(const real& a, const Vector& v);
	Vector operator+(const Vector& v) const;
	void operator+=(const Vector& v);
	Vector operator+(real r) const;
	void operator+=(real r);
	Vector operator*(const Matrix& b) const;
	void operator=(real r);
	Matrix cartesianProduct(const Vector& b);
	real dot(const Vector& b) const;
	real mean() const ;
	Vector abs() const ;
	Vector pow(real p) const;
	Vector hadamardProduct(const Vector& m);
	void limit(real low = -1.0 + EPS, real high = 1.0L - EPS);
};