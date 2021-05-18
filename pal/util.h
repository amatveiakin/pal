#pragma once

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_set.h"
#include "absl/container/inlined_vector.h"
#include "absl/types/span.h"

#include "check.h"
#include "range.h"


namespace pal {

// For std::visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


template<typename T>
void sort_two(T& a, T& b) {
  if (b < a) {
    std::swap(a, b);
  }
}

template<typename T>
std::vector<T> appended(std::vector<T> c, T element) {
  c.push_back(std::move(element));
  return c;
}

template<typename Container>
Container concat(Container a, Container b) {
  a.insert(a.end(), std::move_iterator(b.begin()), std::move_iterator(b.end()));
  return a;
}

template<typename Container, typename... ContainerTail>
Container concat(Container head, ContainerTail... tail) {
  return concat(head, concat(tail...));
}

template<typename DstContainer, typename SrcContainer>
void append_container(DstContainer& dst, SrcContainer&& src) {
  const size_t old_size = dst.size();
  dst.resize(old_size + src.size());
  absl::c_move(src, dst.begin() + old_size);
}

template<typename SuperContainer>
auto flatten(const SuperContainer& containers) {
  typename SuperContainer::value_type ret;
  for (const auto& c: containers) {
    ret.insert(ret.end(), c.begin(), c.end());
  }
  return ret;
}

template<typename T>
std::vector<T> slice(const std::vector<T>& v, int from, int to = -1) {
  if (to == -1) {
    to = v.size();
  }
  CHECK(0 <= from && from <= to && to <= v.size())
      << "Cannot slice vector of length " << v.size() << " from " << from << " to " << to;
  return std::vector<T>(v.begin() + from, v.begin() + to);
}

template<typename Src, typename F>
auto mapped(const Src& src, F&& func) {
  std::vector<std::invoke_result_t<F, typename Src::value_type>> dst(src.size());
  absl::c_transform(src, dst.begin(), std::forward<F>(func));
  return dst;
}

template<typename In, size_t N, typename F>
auto mapped_array(const std::array<In, N>& src, F&& func) {
  std::array<std::invoke_result_t<F, In>, N> dst;
  absl::c_transform(src, dst.begin(), func);
  return dst;
}

// Acts as `mapped(src, &to_string)`; the latter is forbidden because `to_string` is overloaded.
template<typename Src>
auto mapped_to_string(const Src& src) {
  return mapped(src, DISAMBIGUATE(to_string));
}

template<typename T, typename F>
std::vector<T> filtered(std::vector<T> src, F&& func) {
  src.erase(
    std::remove_if(src.begin(), src.end(), [&](const T& element) {
      return !func(element);
    }),
    src.end()
  );
  return src;
}

template<typename Container, typename T>
bool contains_naive(const Container& c, const T& value) {
  return absl::c_find(c, value) != c.end();
}

template<typename Container, typename T>
int element_index(const Container& c, const T& value) {
  const auto it = absl::c_find(c, value);
  CHECK(it != c.end()) << dump_to_string(c) << " does not contain " << value;
  return it - c.begin();
}

template<typename T>
std::vector<T> rotated(std::vector<T> v, int n) {
  n = pos_mod(n, v.size());
  absl::c_rotate(v, v.begin() + n);
  return v;
}

template<typename Container>
Container sorted(Container c) {
  absl::c_sort(c);
  return c;
}

template<typename Container>
Container reversed(Container c) {
  absl::c_reverse(c);
  return c;
}

template<size_t N, typename T>
std::array<T, N> to_array(std::vector<T> v) {
  CHECK_EQ(v.size(), N) << dump_to_string(v);
  std::array<T, N> ret;
  absl::c_move(v, ret.begin());
  return ret;
}

template<typename Container>
auto to_vector(const Container& c) {
  return std::vector<typename Container::value_type>(c.begin(), c.end());
}

// Specializations for map types remove `const` from key
// TODO: Consider auto detection (https://stackoverflow.com/a/35293958/3092679) here and in dump_to_string.
template<typename Key, typename T, typename Compare>
auto to_vector(const std::map<Key, T, Compare>& c) {
  return std::vector<typename std::pair<Key, T>>(c.begin(), c.end());
}
template<typename Key, typename T, typename Hash, typename Eq>
auto to_vector(const absl::flat_hash_map<Key, T, Hash, Eq>& c) {
  return std::vector<typename std::pair<Key, T>>(c.begin(), c.end());
}

template<typename DstElement, typename Container>
auto to_vector(const Container& c) {
  return std::vector<DstElement>(c.begin(), c.end());
}

template<typename Container>
auto to_set(const Container& c) {
  return absl::flat_hash_set<typename Container::value_type>(c.begin(), c.end());
}

template<typename Container>
bool all_equal(const Container& c) {
  return absl::c_adjacent_find(c, std::not_equal_to<>()) == c.end();
}

template<typename Container>
auto sum(const Container& c) {
  return absl::c_accumulate(c, typename Container::value_type());
}

}  // namespace pal
