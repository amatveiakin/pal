#include "pal/zip.h"

#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"


using namespace pal;

TEST(ZipTest, Zip) {
  std::vector<int> a{1, 2, 3};
  std::vector<std::string> b{"one", "two", "three"};
  EXPECT_THAT(zip(a, b), testing::ElementsAre(
    testing::Pair(1, "one"),
    testing::Pair(2, "two"),
    testing::Pair(3, "three")
  ));
}
