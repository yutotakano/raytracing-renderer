#include "vector.h"

#include <cmath>

/** Vector2f */

Vector2f::Vector2f() : x_(0), y_(0) {}
Vector2f::Vector2f(float x, float y) : x_(x), y_(y) {}

float Vector2f::x() const { return x_; }
float Vector2f::y() const { return y_; }

void Vector2f::set_x(float x) { x_ = x; }
void Vector2f::set_y(float y) { y_ = y; }

float Vector2f::length() const { return std::sqrt(x_ * x_ + y_ * y_); }

Vector2f Vector2f::operator+(const Vector2f& other) const {
  return Vector2f(x_ + other.x_, y_ + other.y_);
}

Vector2f& Vector2f::operator+=(const Vector2f& other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

Vector2f Vector2f::operator-(const Vector2f& other) const {
  return Vector2f(x_ - other.x_, y_ - other.y_);
}

Vector2f& Vector2f::operator-=(const Vector2f& other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}

Vector2f Vector2f::operator*(float scalar) const {
  return Vector2f(x_ * scalar, y_ * scalar);
}

Vector2f& Vector2f::operator*=(float scalar) {
  x_ *= scalar;
  y_ *= scalar;
  return *this;
}

Vector2f Vector2f::operator*(const Vector2f& other) const {
  return Vector2f(x_ * other.x_, y_ * other.y_);
}

Vector2f& Vector2f::operator*=(const Vector2f& other) {
  x_ *= other.x_;
  y_ *= other.y_;
  return *this;
}

Vector2f Vector2f::operator/(float scalar) const {
  return Vector2f(x_ / scalar, y_ / scalar);
}

Vector2f& Vector2f::operator/=(float scalar) {
  x_ /= scalar;
  y_ /= scalar;
  return *this;
}

Vector2f Vector2f::operator/(const Vector2f& other) const {
  return Vector2f(x_ / other.x_, y_ / other.y_);
}

Vector2f& Vector2f::operator/=(const Vector2f& other) {
  x_ /= other.x_;
  y_ /= other.y_;
  return *this;
}

float Vector2f::dot(const Vector2f& other) const {
  return x_ * other.x_ + y_ * other.y_;
}

float Vector2f::cross(const Vector2f& other) const {
  return x_ * other.y_ - y_ * other.x_;
}

Vector2f Vector2f::normalized() const {
  float len = length();
  return Vector2f(x_ / len, y_ / len);
}


/** Vector3f */


Vector3f::Vector3f() : x_(0), y_(0), z_(0) {}
Vector3f::Vector3f(float x, float y, float z) : x_(x), y_(y), z_(z) {}

float Vector3f::x() const { return x_; }
float Vector3f::y() const { return y_; }
float Vector3f::z() const { return z_; }

void Vector3f::set_x(float x) { x_ = x; }
void Vector3f::set_y(float y) { y_ = y; }
void Vector3f::set_z(float z) { z_ = z; }

float Vector3f::length() const { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

Vector3f Vector3f::operator+(const Vector3f& other) const {
  return Vector3f(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector3f& Vector3f::operator+=(const Vector3f& other) {
  x_ += other.x_;
  y_ += other.y_;
  z_ += other.z_;
  return *this;
}

Vector3f Vector3f::operator-(const Vector3f& other) const {
  return Vector3f(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Vector3f& Vector3f::operator-=(const Vector3f& other) {
  x_ -= other.x_;
  y_ -= other.y_;
  z_ -= other.z_;
  return *this;
}

Vector3f Vector3f::operator*(float scalar) const {
  return Vector3f(x_ * scalar, y_ * scalar, z_ * scalar);
}

Vector3f& Vector3f::operator*=(float scalar) {
  x_ *= scalar;
  y_ *= scalar;
  z_ *= scalar;
  return *this;
}

Vector3f Vector3f::operator*(const Vector3f& other) const {
  return Vector3f(x_ * other.x_, y_ * other.y_, z_ * other.z_);
}

Vector3f& Vector3f::operator*=(const Vector3f& other) {
  x_ *= other.x_;
  y_ *= other.y_;
  z_ *= other.z_;
  return *this;
}

Vector3f Vector3f::operator/(float scalar) const {
  return Vector3f(x_ / scalar, y_ / scalar, z_ / scalar);
}

Vector3f& Vector3f::operator/=(float scalar) {
  x_ /= scalar;
  y_ /= scalar;
  z_ /= scalar;
  return *this;
}

Vector3f Vector3f::operator/(const Vector3f& other) const {
  return Vector3f(x_ / other.x_, y_ / other.y_, z_ / other.z_);
}

Vector3f& Vector3f::operator/=(const Vector3f& other) {
  x_ /= other.x_;
  y_ /= other.y_;
  z_ /= other.z_;
  return *this;
}

bool Vector3f::operator==(const Vector3f& other) const {
  return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
}

float Vector3f::dot(const Vector3f& other) const {
  return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

Vector3f Vector3f::cross(const Vector3f& other) const {
  return Vector3f(y_ * other.z_ - z_ * other.y_,
          z_ * other.x_ - x_ * other.z_,
          x_ * other.y_ - y_ * other.x_);
}

Vector3f Vector3f::normalized() const {
  float len = length();
  return Vector3f(x_ / len, y_ / len, z_ / len);
}

Vector3f Vector3f::clamp(const Vector3f& vec, float min, float max) {
  return Vector3f(std::clamp(vec.x_, min, max),
          std::clamp(vec.y_, min, max),
          std::clamp(vec.z_, min, max));
}

float Vector3f::operator[](int index) const {
  if (index < 0 || index > 2) {
    throw std::out_of_range("Vector3f index out of range");
  }
  
  return (&x_)[index];
}


/** Vector4f */


Vector4f::Vector4f() : x_(0), y_(0), z_(0), w_(0) {}
Vector4f::Vector4f(float x, float y, float z, float w) : x_(x), y_(y), z_(z), w_(w) {}

float Vector4f::x() const { return x_; }
float Vector4f::y() const { return y_; }
float Vector4f::z() const { return z_; }
float Vector4f::w() const { return w_; }

void Vector4f::set_x(float x) { x_ = x; }
void Vector4f::set_y(float y) { y_ = y; }
void Vector4f::set_z(float z) { z_ = z; }
void Vector4f::set_w(float w) { w_ = w; }

float Vector4f::length() const { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_); }

Vector4f Vector4f::operator+(const Vector4f& other) const {
  return Vector4f(x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_);
}

Vector4f& Vector4f::operator+=(const Vector4f& other) {
  x_ += other.x_;
  y_ += other.y_;
  z_ += other.z_;
  w_ += other.w_;
  return *this;
}

Vector4f Vector4f::operator-(const Vector4f& other) const {
  return Vector4f(x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_);
}

Vector4f& Vector4f::operator-=(const Vector4f& other) {
  x_ -= other.x_;
  y_ -= other.y_;
  z_ -= other.z_;
  w_ -= other.w_;
  return *this;
}

Vector4f Vector4f::operator*(float scalar) const {
  return Vector4f(x_ * scalar, y_ * scalar, z_ * scalar, w_ * scalar);
}

Vector4f& Vector4f::operator*=(float scalar) {
  x_ *= scalar;
  y_ *= scalar;
  z_ *= scalar;
  w_ *= scalar;
  return *this;
}

Vector4f Vector4f::operator*(const Vector4f& other) const {
  return Vector4f(x_ * other.x_, y_ * other.y_, z_ * other.z_, w_ * other.w_);
}

Vector4f& Vector4f::operator*=(const Vector4f& other) {
  x_ *= other.x_;
  y_ *= other.y_;
  z_ *= other.z_;
  w_ *= other.w_;
  return *this;
}

Vector4f Vector4f::operator/(float scalar) const {
  return Vector4f(x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar);
}

Vector4f& Vector4f::operator/=(float scalar) {
  x_ /= scalar;
  y_ /= scalar;
  z_ /= scalar;
  w_ /= scalar;
  return *this;
}

Vector4f Vector4f::operator/(const Vector4f& other) const {
  return Vector4f(x_ / other.x_, y_ / other.y_, z_ / other.z_, w_ / other.w_);
}

Vector4f& Vector4f::operator/=(const Vector4f& other) {
  x_ /= other.x_;
  y_ /= other.y_;
  z_ /= other.z_;
  w_ /= other.w_;
  return *this;
}

float Vector4f::dot(const Vector4f& other) const {
  return x_ * other.x_ + y_ * other.y_ + z_ * other.z_ + w_ * other.w_;
}

Vector4f Vector4f::normalized() const {
  float len = length();
  return Vector4f(x_ / len, y_ / len, z_ / len, w_ / len);
}


/** Matrix3f */


Matrix3f::Matrix3f() {
  for (int i = 0; i < 9; ++i) {
    data_[i] = 0;
  }
}

Matrix3f::Matrix3f(float data[9]) {
  for (int i = 0; i < 9; ++i) {
    data_[i] = data[i];
  }
}

float Matrix3f::operator()(int row, int col) const {
  return data_[row * 3 + col];
}

float& Matrix3f::operator()(int row, int col) {
  return data_[row * 3 + col];
}

Vector3f Matrix3f::operator*(const Vector3f& vec) const {
  return Vector3f(data_[0] * vec.x() + data_[1] * vec.y() + data_[2] * vec.z(),
          data_[3] * vec.x() + data_[4] * vec.y() + data_[5] * vec.z(),
          data_[6] * vec.x() + data_[7] * vec.y() + data_[8] * vec.z());
}

Matrix3f Matrix3f::operator*(const Matrix3f& other) const {
  Matrix3f result;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      float sum = 0;
      for (int k = 0; k < 3; ++k) {
        sum += (*this)(i, k) * other(k, j);
      }
      result(i, j) = sum;
    }
  }
  return result;
}

Matrix3f Matrix3f::transposed() const {
  Matrix3f result;
  for (int i = 0; i < 3; ++i) {
    for (int j = i; j < 3; ++j) {
      result(i, j) = (*this)(j, i);
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}


/** Matrix4f */


Matrix4f::Matrix4f() {
  for (int i = 0; i < 16; ++i) {
    data_[i] = 0;
  }
}

Matrix4f::Matrix4f(float data[16]) {
  for (int i = 0; i < 16; ++i) {
    data_[i] = data[i];
  }
}

float Matrix4f::operator()(int row, int col) const {
  return data_[row * 4 + col];
}

float& Matrix4f::operator()(int row, int col) {
  return data_[row * 4 + col];
}

Vector4f Matrix4f::operator*(const Vector4f& vec) const {
  return Vector4f(data_[0] * vec.x() + data_[1] * vec.y() + data_[2] * vec.z() + data_[3] * vec.w(),
          data_[4] * vec.x() + data_[5] * vec.y() + data_[6] * vec.z() + data_[7] * vec.w(),
          data_[8] * vec.x() + data_[9] * vec.y() + data_[10] * vec.z() + data_[11] * vec.w(),
          data_[12] * vec.x() + data_[13] * vec.y() + data_[14] * vec.z() + data_[15] * vec.w());
}

Matrix4f Matrix4f::operator*(const Matrix4f& other) const {
  Matrix4f result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      float sum = 0;
      for (int k = 0; k < 4; ++k) {
        sum += (*this)(i, k) * other(k, j);
      }
      result(i, j) = sum;
    }
  }
  return result;
}

Matrix4f Matrix4f::transposed() const {
  Matrix4f result;
  for (int i = 0; i < 4; ++i) {
    for (int j = i; j < 4; ++j) {
      result(i, j) = (*this)(j, i);
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}
