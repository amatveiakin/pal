#pragma once

#include <array>

#include "string.h"
#include "math.h"
#include "range.h"


namespace pal {

template<typename T>
class Vector2 {
public:
  using value_type = T;
  static constexpr size_t size = 2;

  Vector2() { coords_.fill(0); }
  Vector2(std::array<T, size> coords) : coords_{std::move(coords)} {}
  Vector2(T x, T y) : coords_{std::move(x), std::move(y)} {}
  template<typename SrcT>
  explicit Vector2(const Vector2<SrcT>& other) {
    for (int i : range(size))  coords_[i] = static_cast<T>(other[i]);
  }

  const std::array<T, size>& coords() const { return coords_; };
  std::array<T, size>&       coords()       { return coords_; };
  const T& operator[](size_t idx) const { return coords_[idx]; }
  T&       operator[](size_t idx)       { return coords_[idx]; }
  const T& dx() const { return coords_[0]; }
  T&       dx()       { return coords_[0]; }
  const T& dy() const { return coords_[1]; }
  T&       dy()       { return coords_[1]; }

  template<typename ResultT = T>
  ResultT length_sqr() const {
    ResultT ret = 0;
    for (int i : range(size))  ret += sqr(static_cast<ResultT>(coords_[i]));
    return ret;
  }

  bool operator==(const Vector2& other) const = default;
  bool operator!=(const Vector2& other) const = default;

private:
  std::array<T, size> coords_;
};

template<typename T>
Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs) {
  for (int i : range(Vector2<T>::size))  lhs[i] += rhs[i];
  return lhs;
}
template<typename T>
Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs) {
  for (int i : range(Vector2<T>::size))  lhs[i] -= rhs[i];
  return lhs;
}

template<typename T>
Vector2<T>& operator*=(Vector2<T>& vector, T scalar) {
  for (int i : range(Vector2<T>::size))  vector[i] *= scalar;
  return vector;
}
template<typename T>
Vector2<T>& operator/=(Vector2<T>& vector, T scalar) {
  for (int i : range(Vector2<T>::size))  vector[i] /= scalar;
  return vector;
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& vector) {
  Vector2<T> ret;
  for (int i : range(Vector2<T>::size))  ret[i] = -vector[i];
  return ret;
}

template<typename T>
Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs) {
  lhs += rhs;
  return lhs;
}
template<typename T>
Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs) {
  lhs -= rhs;
  return lhs;
}

template<typename T>
Vector2<T> operator*(Vector2<T> vector, const T& scalar) {
  vector *= scalar;
  return vector;
}
template<typename T>
Vector2<T> operator*(const T& scalar, Vector2<T> vector) {
  vector *= scalar;
  return vector;
}
template<typename T>
Vector2<T> operator/(Vector2<T> vector, const T& scalar) {
  vector /= scalar;
  return vector;
}


template<typename T>
class Point2 {
public:
  using value_type = T;
  static constexpr size_t size = 2;

  Point2() {}
  Point2(std::array<T, size> coords) : vec_{std::move(coords)} {}
  Point2(T x, T y) : vec_{std::move(x), std::move(y)} {}
  template<typename SrcT>
  explicit Point2(const Point2<SrcT>& other) : vec_(Vector2<SrcT>(other.coords())) {}

  const std::array<T, size>& coords() const { return vec_.coords(); };
  std::array<T, size>&       coords()       { return vec_.coords(); };
  const T& operator[](size_t idx) const { return vec_[idx]; }
  T&       operator[](size_t idx)       { return vec_[idx]; }
  const T& x() const { return vec_.dx(); }
  T&       x()       { return vec_.dx(); }
  const T& y() const { return vec_.dy(); }
  T&       y()       { return vec_.dy(); }

  bool operator==(const Point2& other) const = default;
  bool operator!=(const Point2& other) const = default;

private:
  Vector2<T> vec_;

  template<typename U> friend Point2<U>& operator+=(Point2<U>& point, const Vector2<U>& vector);
  template<typename U> friend Point2<U>& operator-=(Point2<U>& point, const Vector2<U>& vector);
  template<typename U> friend Vector2<U> operator-(Point2<U> lhs, const Point2<U>& rhs);
};

template<typename T>
Point2<T>& operator+=(Point2<T>& point, const Vector2<T>& vector) {
  point.vec_ += vector;
  return point;
}
template<typename T>
Point2<T>& operator-=(Point2<T>& point, const Vector2<T>& vector) {
  point.vec_ -= vector;
  return point;
}

template<typename T>
Point2<T> operator+(Point2<T> point, const Vector2<T>& vector) {
  point += vector;
  return point;
}
template<typename T>
Point2<T> operator+(const Vector2<T>& vector, Point2<T> point) {
  point += vector;
  return point;
}
template<typename T>
Point2<T> operator-(Point2<T> point, const Vector2<T>& vector) {
  point -= vector;
  return point;
}

template<typename T>
Vector2<T> operator-(Point2<T> lhs, const Point2<T>& rhs) {
  return lhs.vec_ - rhs.vec_;
}


template<typename T>
T distance_sqr(const Vector2<T>& a, const Vector2<T>& b) {
  return (a - b).length_sqr();
}
template<typename T>
T distance_sqr(const Point2<T>& a, const Point2<T>& b) {
  return (a - b).length_sqr();
}

template<typename T>
std::string to_string(const Vector2<T> v) {
  return absl::StrCat("(", to_string(v.dx()), ", ", to_string(v.dy()), ")");
}
template<typename T>
std::string to_string(const Point2<T> v) {
  return absl::StrCat("(", to_string(v.x()), ", ", to_string(v.y()), ")");
}

using Vector2i = Vector2<int>;
using Vector2d = Vector2<double>;

using Point2i = Point2<int>;
using Point2d = Point2<double>;

}  // namespace pal
