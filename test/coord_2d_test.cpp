#include "pal/coord_2d.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"


using namespace pal;

TEST(Coord2D, Arithmetic) {
  Vector2i a(1, 2);
  Vector2i b;
  b.dx() = 3;
  b.dy() = 4;
  Vector2i c = a + b;
  EXPECT_EQ(c.dx(), 4);
  EXPECT_EQ(c.dy(), 6);
  c /= 3;
  EXPECT_EQ(c.dx(), 1);
  EXPECT_EQ(c.dy(), 2);
}

TEST(Coord2D, Len) {
  Vector2d v(1, 2.5);
  EXPECT_EQ(v.len_sqr(), 7.25);
  EXPECT_EQ(v.len_sqr<int>(), 5);
}
