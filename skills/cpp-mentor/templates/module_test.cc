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

// The failure case, asserted the way this project reports failures
// ({{ERROR_POLICY}}). Adapt the two assertions below to that policy: an empty
// optional, a non-zero error code, an error-state result, or
// EXPECT_THROW — one of them, never a mix.
TEST({{CLASS}}, Process_EmptyInput_ReportsFailure) {
  const {{CLASS}} object("sample");
  const auto result = object.Process({});
  EXPECT_FALSE(static_cast<bool>(result));
}

}  // namespace
