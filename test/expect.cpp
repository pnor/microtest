#include "lib/microtest/expect.hpp"
#include <gtest/gtest.h>

TEST(ExpectEqualsTest, ExpectGenericTypes) {
  EXPECT_EQ(microtest::expectEquals(1, 1), true);
  EXPECT_EQ(microtest::expectEquals(0, 0), true);
  EXPECT_EQ(microtest::expectEquals(false, false), true);
  EXPECT_EQ(microtest::expectEquals(true, true), true);
  int x = 10;
  EXPECT_EQ(microtest::expectEquals(&x, &x), true);

  EXPECT_EQ(microtest::expectEquals(0, 1), false);
  EXPECT_EQ(microtest::expectEquals(0, 1), false);
  EXPECT_EQ(microtest::expectEquals(true, false), false);
  EXPECT_EQ(microtest::expectEquals(true, false), false);
  int y = 10;
  EXPECT_EQ(microtest::expectEquals(&y, &x), false);
  EXPECT_EQ(microtest::expectEquals(&x, &y), false);
}

TEST(ExpectEqualsTest, ExpectFloats) {
  EXPECT_EQ(microtest::expectEquals(1.0, 1.0, 0.0000001), true);
  EXPECT_EQ(microtest::expectEquals(1.0, 1.1, 1.01), true);

  EXPECT_EQ(microtest::expectEquals(0.0, 1.0, 0.000001), false);
  EXPECT_EQ(microtest::expectEquals(0.0, 1.1, 0.9), false);
}

TEST(ExpectEqualsTest, ExpectArrays) {
  std::vector<int> vecA = {1, 2, 3, 4, 5};
  std::vector<int> vecB = {1, 2, 3, 4, 5};
  EXPECT_EQ(microtest::expectVectorEquals(vecA, vecB), true);

  std::vector<int> vecC = {true, false, true, false};
  std::vector<int> vecD = {true, false, true, false};
  EXPECT_EQ(microtest::expectVectorEquals(vecC, vecD), true);

  std::vector<int> vecE = {1, 2, 3};
  std::vector<int> vecF = {1, 2, 3, 4};
  EXPECT_EQ(microtest::expectVectorEquals(vecE, vecF), false);

  std::vector<int> vecG = {1, 2};
  std::vector<int> vecH = {2, 1};
  EXPECT_EQ(microtest::expectVectorEquals(vecG, vecH), false);

  std::vector<int> vecI = {false, false, true};
  std::vector<int> vecJ = {false, false, false};
  EXPECT_EQ(microtest::expectVectorEquals(vecI, vecJ), false);
}
