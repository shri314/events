#include <gtest/gtest.h>

#include "foo.h"

#include <sstream>

TEST(test_basic, check_working) {
   std::ostringstream oss;
   oss << foo();
   ASSERT_EQ(oss.str(), "1947-08-15");
}
