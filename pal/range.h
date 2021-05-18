#pragma once

#include "check.h"


namespace pal {

class Range {
public:
  class iterator {
  public:
    using difference_type = int;
    using value_type = int;
    using pointer = const int*;
    using reference = const int&;
    using iterator_category = std::forward_iterator_tag;

    iterator(int value) : value_(value) {}
    iterator& operator++() { ++value_; return *this; }
    iterator operator++(int) { auto old_iter = *this; ++value_; return old_iter; }
    int operator*() const { return value_; }
    const int* operator->() const { return &value_; }
    bool operator==(const iterator& other) const = default;
    bool operator!=(const iterator& other) const = default;
  private:
    int value_;
  };

  using value_type = int;
  using const_iterator = iterator;

  Range(int from, int to) : from_(from), to_(to) {
    if (from_ > to_) {
      from_ = to_;
    }
  }

  iterator begin() const { return iterator(from_); }
  iterator end()   const { return iterator(to_); }

private:
  int from_;
  int to_;
};

inline Range range(int to) {
  return Range(0, to);
}
inline Range range(int from, int to) {
  return Range(from, to);
}

inline Range range_incl(int to) {
  return Range(0, to + 1);
}
inline Range range_incl(int from, int to) {
  return Range(from, to + 1);
}


// Usage:
//   for (EACH : range(...)) { ... }
#ifdef __GNUC__
#  define EACH  __attribute__((unused)) auto&& _loop_counter_
#else
#  define EACH  auto&& _loop_counter_
#endif

}  // namespace pal
