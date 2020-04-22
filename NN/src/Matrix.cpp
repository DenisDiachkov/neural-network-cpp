#include "..\include\Matrix.hpp"
#include "..\include\Vector.hpp"

void Matrix::init_iterators(const std::vector<Vector>& v) {
	this->_begin = const_cast<std::vector<Vector>*>(&v)->begin();
	this->_end = const_cast<std::vector<Vector>*>(&v)->end();
	this->_cbegin = v.cbegin();
	this->_cend = v.cend();
}

Matrix Matrix::RandomMatrix(size_t size0, size_t size1) {
	Matrix res(size0, size1);
	for (Vector& vec : res) {
		for (real& i : vec) {
			i = getRandomRealPositive();
		}
	}
	return res;
}

Matrix::Matrix() {}

Matrix::Matrix(size_t size) : vals(size) {
	init_iterators(this->vals);
}

Matrix::Matrix(const Matrix& m) : vals(m.vals)
{
	init_iterators(this->vals);
}

Matrix& Matrix::operator=(const Matrix& m)
{
	this->vals = m.vals;
	init_iterators(this->vals);
	return *this;
}

Matrix::Matrix(size_t size, const Vector& vec) : vals(size, vec) {
	init_iterators(this->vals);
}
Matrix::Matrix(size_t size0, size_t size1, real val) : vals(size0, Vector(size1, val)) {
	init_iterators(this->vals);
}
Matrix::Matrix(const std::vector<Vector>& v) : vals(v) {
	init_iterators(this->vals);
}

Matrix::Matrix(const std::vector<std::vector<real> >& v) : vals(v.size(), Vector(v[0].size())) {
	init_iterators(this->vals);
	for (size_t i = 0; i < this->size()[0]; ++i)
		for (size_t j = 0; j < this->operator[](i).size(); ++j)
			this->operator[](i)[j] = v[i][j];
}

Matrix Matrix::subMatrixRef(size_t l, size_t r) const{
#ifdef __123_NN_DEBUG
	assert(l < r);
	assert(r <= this->size()[0]);
#endif
	Matrix res;
	res._begin = (const_cast<Matrix*>(this)->begin() + l);
	res._cbegin = (this->begin() + l);
	res._end = (const_cast<Matrix*>(this)->begin() + r);
	res._cend = (this->begin() + r);

	return res;
}

Matrix Matrix::subMatrixCopy(size_t l, size_t r) const {
#ifdef __123_NN_DEBUG
	assert(l < r);
	assert(r <= this->size()[0]);
#endif
	return Matrix(std::vector<Vector>(this->begin() + l, this->begin() + r));
}

std::vector<Vector>::const_iterator Matrix::begin() const { 
	return this->_cbegin;
};

std::vector<Vector>::const_iterator Matrix::end() const { 
	return this->_cend;
};

std::vector<Vector>::iterator Matrix::begin() { 
	return this->_begin; 
};

std::vector<Vector>::iterator Matrix::end() { 
	return this->_end; 
};

Vector& Matrix::operator[](size_t idx) {
	return *(this->_begin + idx);
}
const Vector& Matrix::operator[](size_t idx) const {
	return *(this->_cbegin + idx);
}
 
std::vector<size_t> Matrix::size() const {
	return std::vector<size_t>{ (size_t)(this->_cend - this->_cbegin), this->operator[](0).size() };
};

Vector Matrix::operator*(const Vector& v) const {
	Vector res(this->size()[0]);
	for (size_t i = 0; i < this->size()[0]; ++i)
		res[i] = this->operator[](i).dot(v);
	return res;
}

Matrix Matrix::operator+(const Matrix& m) const {
#ifdef __123_NN_DEBUG
	assert(this->size()[0] == m.size()[0]);
#endif
	Matrix res = *this;
	return res += m;
}

Matrix Matrix::operator+(real r) const
{
	Matrix res = *this;
	return res += r;
}

Matrix Matrix::operator-(const Matrix& m) const
{
#ifdef __123_NN_DEBUG
	assert(this->size()[0] == m.size()[0]);
#endif
	Matrix res = *this;
	return res -= m;
}

Matrix& Matrix::operator-=(const Matrix& m){
#ifdef __123_NN_DEBUG
	assert(this->size()[0] == m.size()[0]);
#endif
	for (size_t i = 0; i < this->size()[0]; ++i) {
		this->operator[](i) -= m[i];
	}
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
#ifdef __123_NN_DEBUG
	assert(this->size()[0] == m.size()[0]);
#endif
	for (size_t i = 0; i < this->size()[0]; ++i)
		this->operator[](i) += m[i];
	return *this;
}

Matrix& Matrix::operator+=(real r)
{
	for(Vector&v : *this)
		v += r;
	return *this;
}

Matrix& Matrix::operator=(real r)
{
	for (Vector& v : *this)
		v = r;
	return *this;
}

Matrix Matrix::pow(real p) const
{
	Matrix res(this->size()[0]);
	for (size_t i = 0; i < this->size()[0]; ++i)
		res[i] = this->operator[](i).pow(p);

	return res;
}

Matrix Matrix::hadamardProduct(const Matrix& m)
{
	Matrix res(this->size()[0]);
	for (size_t i = 0; i < this->size()[0]; ++i) {
		res[i] = this->operator[](i).hadamardProduct(m[i]);
	}
	return res;
}

Matrix operator*(const real& a, const Matrix& v) {
	Matrix res(v.size()[0]);
	for (size_t i = 0; i < v.size()[0]; ++i)
		res[i] = a * v[i];
	return res;
}

void Matrix::limit(real low, real high){
	for (Vector& v : *this) {
		v.limit(low, high);
	}
}

void Matrix::addRow(Vector&& v) {
	this->vals.push_back(std::forward<Vector>(v));
	init_iterators(this->vals);
}

void Matrix::print() const {
	for (const Vector& v : *this) {
		for (const real& i : v) {
			printf("%0.6f  ", i);
		}
		printf("\n");
	}
}
