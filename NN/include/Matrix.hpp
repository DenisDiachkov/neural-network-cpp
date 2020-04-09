#pragma once

#include "util.h"
class Vector;

class Matrix {
public:
	std::vector<Vector> vals;
	Matrix(const std::vector<Vector>& v);
	Matrix(const std::vector<std::vector<real> >& v);
	Matrix(unsigned size0, unsigned size1, real val = 0.0L);
	Matrix(unsigned size, Vector vec);
	Matrix(unsigned size);

	std::vector<Vector>::const_iterator begin() const;
	std::vector<Vector>::const_iterator end() const;
	std::vector<Vector>::iterator begin();
	std::vector<Vector>::iterator end();
	Vector& operator[](int idx);
	const Vector& operator[](int idx) const;
	std::vector<unsigned> size() const;
	Vector operator*(const Vector& v) const;
	Matrix operator+(const Matrix& m) const;
	void operator+=(const Matrix& m);
	friend Matrix operator*(const real& a, const Matrix& v);
};

