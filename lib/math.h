
#pragma once

#include <check.h>


namespace pal {

inline int pos_mod(int x, int y) {
  CHECK_GT(y, 0);
  return (x % y + y) % y;
}

inline int neg_one_pow(int power) {
  CHECK_GE(power, 0);
  return 1 - power % 2 * 2;
}

inline int div_round_up(int a, int b) {
  return (a + b - 1) / b;
}

class IntegerDivisionError : public std::runtime_error {
public:
  IntegerDivisionError() : std::runtime_error("Integer division error") {}
};

inline int div_integrally(int a, int b) {
  if (a % b != 0) {
    throw IntegerDivisionError();
  }
  return a / b;
}

inline int factorial(int n) {
  CHECK_GE(n, 0);
  int ret = 1;
  for (int i = 1; i <= n; ++i) {
    ret *= i;
  }
  return ret;
}

}  // namespace pal
