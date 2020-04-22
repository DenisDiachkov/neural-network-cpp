#pragma once

#include "util.h"

class Matrix {
private:
	std::vector<Vector> vals;
	std::vector<Vector>::iterator _begin, _end;
	std::vector<Vector>::const_iterator _cbegin, _cend;

	void init_iterators(const std::vector<Vector>& v);

public:

	static Matrix RandomMatrix(size_t size0, size_t size1);

	Matrix();
	explicit Matrix(const std::vector<Vector>& v);
	explicit Matrix(const std::vector<std::vector<real> >& v);
	explicit Matrix(size_t size0, size_t size1, real val = 0.0L);
	explicit Matrix(size_t size, const Vector& vec);
	explicit Matrix(size_t size);
	Matrix(const Matrix &);
	Matrix& operator=(const Matrix&);

	Matrix subMatrixRef(size_t l, size_t r) const;
	Matrix subMatrixCopy(size_t l, size_t t) const;

	std::vector<Vector>::const_iterator begin() const;
	std::vector<Vector>::const_iterator end() const;
	std::vector<Vector>::iterator begin();
	std::vector<Vector>::iterator end();
	Vector& operator[](size_t idx);
	const Vector& operator[](size_t idx) const;
	std::vector<size_t> size() const;
	Vector operator*(const Vector& v) const;
	Matrix operator+(const Matrix& m) const;
	Matrix operator+(real r) const;
	Matrix operator-(const Matrix& m) const;
	Matrix& operator-=(const Matrix& m);
	Matrix& operator+=(const Matrix& m);
	Matrix& operator+=(real r);
	Matrix& operator=(real r);
	friend Matrix operator*(const real& a, const Matrix& v);
	Matrix pow(real p) const;
	Matrix hadamardProduct(const Matrix& m);

	void limit(real low = -1.0 + EPS, real high = 1.0 - EPS);
	void addRow(Vector&& v);

	void print() const;
};

