#pragma once

#include "range.h"


namespace pal {

// Optimization potential: O(N*log(N)) sort for large N.
template<typename Container, typename Compare>
[[nodiscard]] int sort_with_sign(Container& v, const Compare& comp) {
  int sign = 1;
  for (EACH : range(v.size())) {
    for (int i : range(v.size() - 1)) {
      if (comp(v[i+1], v[i])) {
        std::swap(v[i], v[i+1]);
        sign *= -1;
      }
    }
  }
  return sign;
}

template<typename Container>
[[nodiscard]] int sort_with_sign(Container& v) {
  return sort_with_sign(v, std::less<>());
}

}  // namespace pal
