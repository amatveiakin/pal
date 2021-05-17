#pragma once

#include <vector>

#include "absl/algorithm/container.h"


namespace pal {

// Optimization potential: sort only if necessary to avoid copying.

template<typename T>
void keep_unique_sorted(std::vector<T>& v) {
  v.erase(std::unique(v.begin(), v.end()), v.end());
}

template<typename Container>
int num_distinct_elements_sorted(Container v) {
  absl::c_sort(v);
  return std::unique(v.begin(), v.end()) - v.begin();
}
template<typename Container>
int num_distinct_elements_unsorted(Container v) {
  absl::c_sort(v);
  return num_distinct_elements_sorted(v);
}

template<typename Container>
bool all_unique_sorted(const Container& v) {
  return absl::c_adjacent_find(v) == v.end();
}
template<typename Container>
bool all_unique_unsorted(Container v) {
  absl::c_sort(v);
  return all_unique_sorted(v);
}

template<typename T>
std::vector<T> set_intersection(const std::vector<T>& a, const std::vector<T>& b) {
  std::vector<T> ret;
  absl::c_set_intersection(sorted(a), sorted(b), std::back_inserter(ret));
  return ret;
}

template<typename T>
int set_intersection_size(const std::vector<T>& a, const std::vector<T>& b) {
  // Optimization potential: Use a fake iterators that counts instead of back_inserter.
  return set_intersection(a, b).size();
}

template<typename T>
std::vector<T> set_intersection(const std::vector<std::vector<T>>& sets) {
  CHECK(!sets.empty());
  std::vector<int> ret = sets.front();
  absl::c_sort(ret);
  for (auto one_set : absl::MakeConstSpan(sets).subspan(1)) {
    absl::c_sort(one_set);
    std::vector<int> new_ret;
    absl::c_set_intersection(ret, one_set, std::back_inserter(new_ret));
    ret = std::move(new_ret);
  }
  return ret;
}

template<typename T>
int set_intersection_size(const std::vector<std::vector<T>>& sets) {
  return set_intersection(sets).size();
}

template<typename T>
std::vector<T> set_union(const std::vector<T>& a, const std::vector<T>& b) {
  std::vector<T> ret;
  absl::c_set_union(sorted(a), sorted(b), std::back_inserter(ret));
  return ret;
}

template<typename T>
std::vector<T> set_union(const std::vector<std::vector<T>>& sets) {
  return keep_unique_sorted(sorted(flatten(sets)));
}

template<typename T>
std::vector<T> set_difference(const std::vector<T>& a, const std::vector<T>& b) {
  std::vector<T> ret;
  absl::c_set_difference(sorted(a), sorted(b), std::back_inserter(ret));
  return ret;
}

}  // namespace pal
