#pragma once

#include "absl/container/flat_hash_map.h"


namespace pal {

// Sample usage:
//    return foo(arg1, ..., argN);
// =>
//    static CallCache<Arg1, ... ArgN> call_cache;
//    return call_cache.apply(&foo, arg1, ..., argN);
//
template<typename Value, typename... Args>
class CallCache {
public:
  template<typename F>
  Value apply(F&& func, Args... args) {
    const std::tuple<Args...> args_tuple{std::move(args)...};
    const auto it = cache_.find(args_tuple);
    if (it != cache_.end()) {
      return it->second;
    } else {
      Value ret = std::apply(std::forward<F>(func), args_tuple);
      cache_[args_tuple] = ret;
      return ret;
    }
  }

private:
  absl::flat_hash_map<std::tuple<Args...>, Value> cache_;
};

}  // namespace pal
