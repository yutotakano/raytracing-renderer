#ifndef VECTOR_H
#define VECTOR_H

#include <json/json.hpp>

/**
 * @brief A vector in 2D space.
 */
class Vector2f {
public:
  Vector2f();
  Vector2f(float x, float y);

  float x() const;
  float y() const;

  void set_x(float x);
  void set_y(float y);

  float length() const;

  Vector2f operator+(const Vector2f& other) const;
  Vector2f& operator+=(const Vector2f& other);
  Vector2f operator-(const Vector2f& other) const;
  Vector2f& operator-=(const Vector2f& other);
  Vector2f operator*(float scalar) const;
  Vector2f& operator*=(float scalar);
  Vector2f operator*(const Vector2f& other) const;
  Vector2f& operator*=(const Vector2f& other);
  Vector2f operator/(float scalar) const;
  Vector2f& operator/=(float scalar);
  Vector2f operator/(const Vector2f& other) const;
  Vector2f& operator/=(const Vector2f& other);

  float dot(const Vector2f& other) const;
  float cross(const Vector2f& other) const;

  Vector2f normalized() const;

private:
  float x_;
  float y_;
};

// Define JSON serialization for Vector2f

NLOHMANN_JSON_NAMESPACE_BEGIN
template <> struct adl_serializer<Vector2f> {
  static void to_json(json& j, const Vector2f& opt) {
    j = {opt.x(), opt.y()};
  }

  static void from_json(const json& j, Vector2f& opt) {
    opt = Vector2f(j[0], j[1]);
  }
};
NLOHMANN_JSON_NAMESPACE_END

/**
 * @brief A vector in 3D space.
 */
class Vector3f {
public:
  Vector3f();
  Vector3f(float x, float y, float z);

  float x() const;
  float y() const;
  float z() const;

  void set_x(float x);
  void set_y(float y);
  void set_z(float z);

  float length() const;

  Vector3f operator+(const Vector3f& other) const;
  Vector3f& operator+=(const Vector3f& other);
  Vector3f operator-(const Vector3f& other) const;
  Vector3f& operator-=(const Vector3f& other);
  Vector3f operator*(float scalar) const;
  Vector3f& operator*=(float scalar);
  Vector3f operator*(const Vector3f& other) const;
  Vector3f& operator*=(const Vector3f& other);
  Vector3f operator/(float scalar) const;
  Vector3f& operator/=(float scalar);
  Vector3f operator/(const Vector3f& other) const;
  Vector3f& operator/=(const Vector3f& other);

  float dot(const Vector3f& other) const;
  Vector3f cross(const Vector3f& other) const;

  Vector3f normalized() const;

  static Vector3f clamp(const Vector3f& vec, float min, float max);

private:
  float x_;
  float y_;
  float z_;
};

// Define JSON serialization for Vector3f

NLOHMANN_JSON_NAMESPACE_BEGIN
template <> struct adl_serializer<Vector3f> {
  static void to_json(json& j, const Vector3f& opt) {
    j = {opt.x(), opt.y(), opt.z()};
  }

  static void from_json(const json& j, Vector3f& opt) {
    opt = Vector3f(j[0], j[1], j[2]);
  }
};
NLOHMANN_JSON_NAMESPACE_END

/**
 * @brief A vector in 4D space.
 */
class Vector4f {
public:
  Vector4f();
  Vector4f(float x, float y, float z, float w);

  float x() const;
  float y() const;
  float z() const;
  float w() const;

  void set_x(float x);
  void set_y(float y);
  void set_z(float z);
  void set_w(float w);

  float length() const;

  Vector4f operator+(const Vector4f& other) const;
  Vector4f& operator+=(const Vector4f& other);
  Vector4f operator-(const Vector4f& other) const;
  Vector4f& operator-=(const Vector4f& other);
  Vector4f operator*(float scalar) const;
  Vector4f& operator*=(float scalar);
  Vector4f operator*(const Vector4f& other) const;
  Vector4f& operator*=(const Vector4f& other);
  Vector4f operator/(float scalar) const;
  Vector4f& operator/=(float scalar);
  Vector4f operator/(const Vector4f& other) const;
  Vector4f& operator/=(const Vector4f& other);

  float dot(const Vector4f& other) const;

  Vector4f normalized() const;

private:
  float x_;
  float y_;
  float z_;
  float w_;
};

// Define JSON serialization for Vector4f

NLOHMANN_JSON_NAMESPACE_BEGIN
template <> struct adl_serializer<Vector4f> {
  static void to_json(json& j, const Vector4f& opt) {
    j = {opt.x(), opt.y(), opt.z(), opt.w()};
  }

  static void from_json(const json& j, Vector4f& opt) {
    opt = Vector4f(j[0], j[1], j[2], j[3]);
  }
};
NLOHMANN_JSON_NAMESPACE_END

/**
 * @brief A 3x3 matrix.
 */
class Matrix3f {
public:
  Matrix3f();
  Matrix3f(float data[9]);

  float operator()(int row, int col) const;
  float& operator()(int row, int col);

  Vector3f operator*(const Vector3f& vec) const;
  Matrix3f operator*(const Matrix3f& other) const;

  Matrix3f transposed() const;

private:
  float data_[9];
};

// Define JSON serialization for Matrix3f

NLOHMANN_JSON_NAMESPACE_BEGIN
template <> struct adl_serializer<Matrix3f> {
  static void to_json(json& j, const Matrix3f& opt) {
    j = {opt(0, 0), opt(0, 1), opt(0, 2), opt(1, 0), opt(1, 1), opt(1, 2), opt(2, 0), opt(2, 1), opt(2, 2)};
  }

  static void from_json(const json& j, Matrix3f& opt) {
    float data[9] = {j[0], j[1], j[2], j[3], j[4], j[5], j[6], j[7], j[8]};
    opt = Matrix3f(data);
  }
};
NLOHMANN_JSON_NAMESPACE_END

/**
 * @brief A 4x4 matrix.
 */
class Matrix4f {
public:
  Matrix4f();
  Matrix4f(float data[16]);

  float operator()(int row, int col) const;
  float& operator()(int row, int col);

  Vector4f operator*(const Vector4f& vec) const;
  Matrix4f operator*(const Matrix4f& other) const;

  Matrix4f transposed() const;

private:
  float data_[16];
};

// Define JSON serialization for Matrix4f

NLOHMANN_JSON_NAMESPACE_BEGIN
template <> struct adl_serializer<Matrix4f> {
  static void to_json(json& j, const Matrix4f& opt) {
    j = {opt(0, 0), opt(0, 1), opt(0, 2), opt(0, 3), opt(1, 0), opt(1, 1), opt(1, 2), opt(1, 3), opt(2, 0), opt(2, 1), opt(2, 2), opt(2, 3), opt(3, 0), opt(3, 1), opt(3, 2), opt(3, 3)};
  }

  static void from_json(const json& j, Matrix4f& opt) {
    float data[12] = {j[0], j[1], j[2], j[3], j[4], j[5], j[6], j[7], j[8], j[9], j[10], j[11]};
    opt = Matrix4f(data);
  }
};
NLOHMANN_JSON_NAMESPACE_END

// A stationary point in 2D space.
using Point2f = Vector2f;
// A stationary point in 3D space.
using Point3f = Vector3f;

// A color represented by RGB values. Values could be above 1.0 for HDR.
using Color3f = Vector3f;
// A color represented by RGBA values. Values could be above 1.0 for HDR.
using Color4f = Vector4f;

#endif // VECTOR_H
