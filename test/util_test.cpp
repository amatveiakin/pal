#include "pal/util.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"


using namespace pal;

TEST(UtilTest, Mapped) {
  EXPECT_THAT(
    mapped(
      std::vector{1, 2, 3},
      [](int x) { return x + 3; }
    ),
    testing::ElementsAre(4, 5, 6)
  );
}
