#include "..\include\Vector.hpp"
#include "..\include\Matrix.hpp"

void Vector::init_iterators(const std::vector<real>& v) {
	this->_begin = const_cast<std::vector<real>*>(&v)->begin();
	this->_end = const_cast<std::vector<real>*>(&v)->end();
	this->_cbegin = v.cbegin();
	this->_cend = v.cend();
}

Vector::Vector() {
};

Vector::Vector(const std::vector<real>& v) : vals(v) {
	init_iterators(this->vals);
}

Vector::Vector(size_t size, real val) : vals(size, val) {
	init_iterators(this->vals);
}

Vector& Vector::operator=(const Vector& v) {
	this->vals = v.vals;
	init_iterators(this->vals);
	return *this;
}

Vector::Vector(const Vector& v){
	this->vals = v.vals;
	init_iterators(this->vals);
}

std::vector<real>::const_iterator Vector::begin() const { 
	return this->_cbegin; 
};
std::vector<real>::const_iterator Vector::end() const { 
	return this->_cend; 
};

std::vector<real>::iterator Vector::begin() { 
	return this->_begin; 
};

std::vector<real>::iterator Vector::end() { 
	return this->_end; 
};

real& Vector::operator[](size_t idx) {
	return *(this->_begin + idx);
}
const real& Vector::operator[](size_t idx) const {
	return *(this->_cbegin + idx);
}
unsigned Vector::size() const { 
	return (unsigned)(this->_cend - this->_cbegin);
}

Vector Vector::operator-(const Vector& v) const {
#ifdef __123_NN_DEBUG
	assert(this->size() == v.size());
#endif
	Vector res(this->size());
	for (size_t i = 0; i < this->size(); ++i)
		res[i] = this->operator[](i) - v[i];
	return res;
}

void Vector::operator-=(const Vector& v) {
#ifdef __123_NN_DEBUG
	assert(this->size() == v.size());
#endif
	for (size_t i = 0; i < this->size(); ++i)
		this->operator[](i) -= v[i];
}

Vector Vector::operator*(const Vector& v) const {
#ifdef __123_NN_DEBUG
	assert(this->size() == v.size());
#endif
	Vector res(this->size());
	for (size_t i = 0; i < this->size(); ++i)
		res[i] = this->operator[](i) * v[i];
	return res;
}

void Vector::operator*=(const Vector& v) {
#ifdef __123_NN_DEBUG
	assert(this->size() == v.size());
#endif
	for (size_t i = 0; i < this->size(); ++i)
		this->operator[](i) *= v[i];
}

Vector operator*(const real& a, const Vector& v){
	Vector res(v.size());
	for (size_t i = 0; i < v.size(); ++i)
		res[i] = a * v[i];
	return res;
}

Vector Vector::operator+(const Vector& v) const {
#ifdef __123_NN_DEBUG
	assert(this->size() == v.size());
#endif
	Vector res(this->size());
	for (size_t i = 0; i < this->size(); ++i)
		res[i] = this->operator[](i) + v[i];
	return res;
}

void Vector::operator+=(const Vector& v) {
#ifdef __123_NN_DEBUG
	assert(this->size() == v.size());
#endif
	for (size_t i = 0; i < this->size(); ++i)
		this->operator[](i) += v[i];
}

Vector Vector::operator+(real r) const
{
	Vector res(this->size());
	for (size_t i = 0; i < res.size(); ++i)
		res[i] = this->operator[](i) + r;
	return res;
}

void Vector::operator+=(real r)
{
	for (real& i : *this)
		i += r;
}

Vector Vector::operator*(const Matrix& b) const {
#ifdef __123_NN_DEBUG
	assert(b.size()[0] == this->size());
#endif
	Vector res = Vector(b.size()[1]);
	for (int j = 0; j < b.size()[1]; ++j) {
		for (int i = 0; i < b.size()[0]; ++i) {
			res[j] += b[i][j] * this->operator[](i);
		}
	}
	return res;
}

void Vector::operator=(real r)
{
	for (real& i : *this)
		i = r;
}

Matrix Vector::cartesianProduct(const Vector& b) {
	Matrix m(this->size(), Vector(b.size()));
	for (size_t i = 0; i < this->size(); ++i)
		for (size_t j = 0; j < b.size(); ++j)
			m[i][j] = this->operator[](i) * b[j];
	return m;
}

real Vector::dot(const Vector& b) const {
#ifdef __123_NN_DEBUG
	assert(this->size() == b.size());
#endif
	real res = 0;
	for (size_t i = 0; i < this->size(); ++i)
		res += this->operator[](i) * b[i];
	return res;
}

real Vector::mean() const {
	return this->operator*(Matrix(this->size(), Vector(1,1)))[0] / this->size();
}

Vector Vector::abs() const {
	Vector res(this->size());
	for (size_t i = 0; i < res.size(); ++i)
		res[i] = fabsl(this->operator[](i));
	return res;
}

Vector Vector::pow(real p) const
{
	Vector res(this->size());
	for (size_t i = 0; i < this->size(); ++i) {
		res[i] = powl(this->operator[](i), p);
	}
	return res;
}

Vector Vector::hadamardProduct(const Vector& m)
{
	Vector res(this->size());
	for (size_t i = 0; i < this->size(); ++i) {
		res[i] = this->operator[](i) * m[i];
	}
	return res;
}

void Vector::limit(real low, real high){
	for (real& i : *this) {
		i = std::max(low, std::min(high, i));
	}
}
