#include "lib/range.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "lib/util.h"


using namespace pal;

TEST(RangeTest, Basic) {
  EXPECT_THAT(to_vector(range(7)), testing::ElementsAre(0, 1, 2, 3, 4, 5, 6));
  EXPECT_THAT(to_vector(range(3, 7)), testing::ElementsAre(3, 4, 5, 6));
  EXPECT_THAT(to_vector(range_incl(7)), testing::ElementsAre(0, 1, 2, 3, 4, 5, 6, 7));
  EXPECT_THAT(to_vector(range_incl(3, 7)), testing::ElementsAre(3, 4, 5, 6, 7));
}
