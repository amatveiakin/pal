#include "lib/string.h"

#include <map>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"


using namespace pal;

TEST(StringTest, AutoDump) {
  std::map<int, std::vector<std::string>> data;
  data[87] = {"foo", "bar"};
  data[156] = {"buz"};
  const auto dump = dump_to_string(data);
  EXPECT_THAT(dump, testing::AllOf(
    testing::HasSubstr("87"),
    testing::HasSubstr("156"),
    testing::HasSubstr("foo"),
    testing::HasSubstr("bar"),
    testing::HasSubstr("buz")
  ));
}

TEST(StringTest, Trim) {
  EXPECT_EQ(trimed_left("  foo   "), "foo   ");
  EXPECT_EQ(trimed_right("  foo   "), "  foo");
  EXPECT_EQ(trimed("  foo   "), "foo");
}

TEST(StringTest, Pad) {
  EXPECT_EQ(pad_left("foo", 8), "     foo");
}

TEST(StringTest, ThousandSeparators) {
  EXPECT_EQ(to_string_with_thousand_sep(1048576), "1'048'576");
}
