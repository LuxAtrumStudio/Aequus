#include "aequus_core.hpp"

#include "gtest/gtest.h"

TEST(AeqCore, GetVersion) {
  int major = 0, minor = 0, patch = 0;
  aequus::GetVersion(major, minor, patch);
  EXPECT_EQ(major, AEQUUS_VERSION_MAJOR);
  EXPECT_EQ(minor, AEQUUS_VERSION_MINOR);
  EXPECT_EQ(patch, AEQUUS_VERSION_PATCH);
}
