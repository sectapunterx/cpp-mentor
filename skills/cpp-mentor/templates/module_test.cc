#include "{{NS}}/{{MODULE}}/{{FILE}}.h"

#include <gtest/gtest.h>

#include <string>

namespace {

using {{NS}}::{{MODULE}}::{{CLASS}};

// suite_name == the class under test.
// test_name  == MethodName_StateUnderTest_ExpectedBehavior.

TEST({{CLASS}}, Name_ConstructedWithIdentifier_ReturnsIt) {
  const {{CLASS}} object("sample");
  EXPECT_EQ(object.name(), "sample");
}

TEST({{CLASS}}, Process_EmptyInput_ReturnsError) {
  const {{CLASS}} object("sample");
  const auto result = object.Process({});
  ASSERT_FALSE(result.has_value());
  EXPECT_FALSE(result.error().empty());
}

}  // namespace
