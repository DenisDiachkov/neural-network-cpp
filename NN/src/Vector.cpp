#include "..\include\Vector.hpp"
#include "..\include\Matrix.hpp"

Vector::Vector() : vals() {};
Vector::Vector(const std::vector<real>& v) : vals(v) {}
Vector::Vector(int size, real val) : vals(size, val) {}
std::vector<real>::const_iterator Vector::begin() const { return vals.cbegin(); };
std::vector<real>::const_iterator Vector::end() const { return vals.cend(); };
std::vector<real>::iterator Vector::begin() { return vals.begin(); };
std::vector<real>::iterator Vector::end() { return vals.end(); };
real& Vector::operator[](int idx) { return vals[idx]; }
const real& Vector::operator[](int idx) const { return vals[idx]; }
unsigned Vector::size() const { return vals.size(); }

Vector Vector::operator-(const Vector& v) const {
	assert(this->size() == v.size());
	Vector res(this->size());
	for (int i = 0; i < this->size(); ++i)
		res[i] = this->vals[i] - v.vals[i];
	return res;
}

void Vector::operator-=(const Vector& v) {
	assert(this->size() == v.size());
	for (int i = 0; i < this->size(); ++i)
		this->vals[i] -= v.vals[i];
}

Vector Vector::operator*(const Vector& v) const {
	assert(this->size() == v.size());
	Vector res(this->size());
	for (int i = 0; i < this->size(); ++i)
		res[i] = this->vals[i] * v.vals[i];
	return res;
}

void Vector::operator*=(const Vector& v) {
	assert(this->size() == v.size());
	for (int i = 0; i < this->size(); ++i)
		this->vals[i] *= v.vals[i];
}

Vector operator*(const real& a, const Vector& v){
	Vector res(v.size());
	for (int i = 0; i < v.size(); ++i)
		res[i] = a * v.vals[i];
	return res;
}

Vector Vector::operator+(const Vector& v) const {
	assert(this->size() == v.size());
	Vector res(this->size());
	for (int i = 0; i < this->size(); ++i)
		res[i] = this->vals[i] + v.vals[i];
	return res;
}

void Vector::operator+=(const Vector& v) {
	assert(this->size() == v.size());
	for (int i = 0; i < this->size(); ++i)
		this->vals[i] += v.vals[i];
}

Vector Vector::operator*(const Matrix& b) const {
	assert(b.size()[0] == this->size());
	Vector res = Vector(b.size()[1]);
	for (int j = 0; j < b.size()[1]; ++j) {
		for (int i = 0; i < b.size()[0]; ++i) {
			res[j] += b[i].vals[j] * this->vals[i];
		}
	}
	return res;
}

Matrix Vector::cartesianProduct(const Vector& b) {
	Matrix m(this->size(), Vector(b.size()));
	for (int i = 0; i < this->size(); ++i)
		for (int j = 0; j < b.size(); ++j)
			m[i][j] = this->vals[i] * b.vals[j];
	return m;
}

real Vector::dot(const Vector& b) const {
	assert(this->size() == b.size());
	real res = 0;
	for (int i = 0; i < this->size(); ++i)
		res += this->vals[i] * b.vals[i];
	return res;
}

real Vector::mean() {
	return this->operator*(Matrix(this->size(), Vector(1,1)))[0] / this->size();
}

Vector Vector::abs() {
	Vector res(this->vals.size());
	for (int i = 0; i < res.size(); ++i)
		res[i] = fabsl(this->vals[i]);
	return res;
}