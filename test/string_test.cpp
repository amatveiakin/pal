#include "pal/string.h"

#include <map>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"


using namespace pal;


class ClassA {};
class ClassB {};
class ClassC {};

std::string to_string(const ClassB&) { return "to_string_B"; };

std::string to_string(const ClassC&) { return "to_string_C"; };
std::string dump_to_string_impl(const ClassC&) { return "dump_to_string_impl_C"; };


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

TEST(StringTest, DumpPriority) {
  EXPECT_THAT(dump_to_string(ClassA{}), testing::HasSubstr("ClassA"));
  EXPECT_THAT(dump_to_string(ClassB{}), testing::HasSubstr("to_string_B"));
  EXPECT_THAT(dump_to_string(ClassC{}), testing::HasSubstr("dump_to_string_impl_C"));
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
