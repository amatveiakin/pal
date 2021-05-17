#pragma once

#include <array>
#include <vector>

#include "check.h"


namespace pal {

template<typename T>
std::vector<T> removed_slice(std::vector<T> v, int from, int to = -1) {
  if (to == -1) {
    to = v.size();
  }
  CHECK(0 <= from && from <= v.size());
  CHECK(0 <= to && to <= v.size());
  v.erase(v.begin() + from, v.begin() + to);
  return v;
}

template<typename T>
std::vector<T> removed_index(std::vector<T> v, int index) {
  v.erase(v.begin() + index);
  return v;
}

template<typename T>
std::vector<T> removed_indices(std::vector<T> v, std::vector<int> indices) {
  absl::c_sort(indices);
  // Optimization potential: O(N) solution.
  for (auto it = indices.rbegin(); it != indices.rend(); ++it) {
    v.erase(v.begin() + *it);
  }
  return v;
}

template<typename T>
std::vector<T> choose_indices(const std::vector<T>& v, const std::vector<int>& indices) {
  std::vector<T> ret;
  ret.reserve(indices.size());
  for (int idx : indices) {
    ret.push_back(v.at(idx));
  }
  return ret;
}

template<typename T, size_t N, size_t M>
std::array<T, M> choose_indices(const std::array<T, N>& v, const std::array<int, M>& indices) {
  std::array<T, M> ret;
  for (int i : range(indices.size())) {
    ret[i] = v.at(indices[i]);
  }
  return ret;
}

template<typename T, typename MaskT>
std::vector<T> choose_by_mask(const std::vector<T>& v, const std::vector<MaskT>& mask) {
  CHECK_EQ(v.size(), mask.size());
  std::vector<T> ret;
  for (int i : range(v.size())) {
    if (mask[i]) {
      ret.push_back(v[i]);
    }
  }
  return ret;
}

}  // namespace pal
