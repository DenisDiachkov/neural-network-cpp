#include "..\include\Matrix.hpp"
#include "..\include\Vector.hpp"

Matrix::Matrix(unsigned size) : vals(size) {}
Matrix::Matrix(unsigned size, Vector vec) : vals(size, vec) {}
Matrix::Matrix(unsigned size0, unsigned size1, real val) : vals(size0, Vector(size1, val)) {}
Matrix::Matrix(const std::vector<Vector>& v) : vals(v) {}

Matrix::Matrix(const std::vector<std::vector<real> >& v) {
	this->vals = std::vector<Vector>(v.size(), Vector(v[0].size()));
	for (int i = 0; i < v.size(); ++i)
		for (int j = 0; j < v[i].size(); ++j)
			vals[i][j] = v[i][j];
}

std::vector<Vector>::const_iterator Matrix::begin() const { 
	return vals.cbegin(); 
};

std::vector<Vector>::const_iterator Matrix::end() const { 
	return vals.cend(); 
};

std::vector<Vector>::iterator Matrix::begin() { 
	return vals.begin(); 
};

std::vector<Vector>::iterator Matrix::end() { 
	return vals.end(); 
};

Vector& Matrix::operator[](int idx) { 
	return vals[idx]; 
}
const Vector& Matrix::operator[](int idx) const { 
	return vals[idx]; 
}

std::vector<unsigned> Matrix::size() const { 
	return std::vector<unsigned>{ (unsigned)this->vals.size(), this->vals[0].size() }; 
};

Vector Matrix::operator*(const Vector& v) const {
	Vector res(this->vals.size());
	for (int i = 0; i < this->vals.size(); ++i)
		res[i] = this->vals[i].dot(v);
	return res;
}

Matrix Matrix::operator+(const Matrix& m) const {
	assert(this->vals.size() == m.vals.size());
	Matrix res(this->vals.size());
	for (int i = 0; i < this->vals.size(); ++i)
		res[i] = this->vals[i] + m.vals[i];
	return res;
}

void Matrix::operator+=(const Matrix& m) {
	assert(this->vals.size() == m.vals.size());
	for (int i = 0; i < this->vals.size(); ++i)
		this->vals[i] += m.vals[i];
}

Matrix operator*(const real& a, const Matrix& v) {
	Matrix res(v.size()[0]);
	for (int i = 0; i < v.size()[0]; ++i)
		res[i] = a * v.vals[i];
	return res;
}
