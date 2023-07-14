#include "lib/microtest/graph.hpp"
#include <gtest/gtest.h>

// ===== Functions to test coverage =====

/** Returns true if `x` >= 0 and false otherwise */
static bool isPositive(const int &x) {
  microtest::GraphTest::graphNode("1");
  if (x >= 0) {
    microtest::GraphTest::graphNode("2");
    return true;
  } else {
    microtest::GraphTest::graphNode("3");
    return false;
  }
}
/** Returns true if all numbers in `numbers` are divisible by 2, and false
 * otherwise */
static bool onlyEvenNumbers(const std::vector<int> &numbers) {
  microtest::GraphTest::graphNode("1");
  for (const auto &x : numbers) {
    microtest::GraphTest::graphNode("2");
    if (x % 2 != 0) {
      return false;
    }
  }
  microtest::GraphTest::graphNode("3");
  return true;
}

/** Returns 0 if x is in 0..10, 1 if x is in [11..50] and 2 if x is in
 * [51..100]. Returns -1 otherwise. */
static int ranges(const int &x) {
  microtest::GraphTest::graphNode("1");

  if (x >= 0 && x <= 10) {
    microtest::GraphTest::graphNode("2");
    return 0;
  } else if (x >= 11 && x <= 50) {
    microtest::GraphTest::graphNode("3");
    return 1;
  } else if (x >= 51 && x <= 100) {
    microtest::GraphTest::graphNode("4");
    return 2;
  } else {
    microtest::GraphTest::graphNode("5");
    return -1;
  }
}

// ===== Test Suite =====

TEST(GraphCoverageTest, isPositiveFunctionFullCoverage) {
  // Start tracking coverage
  // - persists paths taking for the duration of the returned object's
  // lifetime
  microtest::GraphTrackingMarker tracking =
      microtest::GraphTest::startGraphTracking();

  // Run some tests on some inputs
  EXPECT_EQ(isPositive(1), true);
  EXPECT_EQ(isPositive(4), true);
  EXPECT_EQ(isPositive(0), true);
  EXPECT_EQ(isPositive(-1), false);
  EXPECT_EQ(isPositive(-999), false);

  // Check coverage
  EXPECT_EQ(microtest::GraphTest::checkCoverage({"1", "2", "3"}), true);
}

TEST(GraphCoverageTest, isPositiveFunctionBadCoverage) {
  // Start tracking coverage
  microtest::GraphTrackingMarker tracking =
      microtest::GraphTest::startGraphTracking();

  // Run some tests on some inputs
  EXPECT_EQ(isPositive(1), true);
  EXPECT_EQ(isPositive(10000), true);

  // Check coverage
  EXPECT_EQ(microtest::GraphTest::checkCoverage({"1", "2", "3"}), false);
}

TEST(GraphCoverageTest, repeatedPaths) {
  // Start tracking coverage
  microtest::GraphTrackingMarker tracking =
      microtest::GraphTest::startGraphTracking();

  // Run some tests on some inputs
  EXPECT_EQ(onlyEvenNumbers({2, 4, 6, 8}), true);
  EXPECT_EQ(onlyEvenNumbers({}), true);
  EXPECT_EQ(onlyEvenNumbers({1, 2, 3, 4}), false);

  // Check coverage
  EXPECT_EQ(microtest::GraphTest::checkCoverage({"1", "2", "3"}), true);
}

TEST(GraphCoverageTest, manyPaths) {
  // Start tracking coverage
  microtest::GraphTrackingMarker tracking =
      microtest::GraphTest::startGraphTracking();

  // Run some tests on some inputs
  EXPECT_EQ(ranges(0), 0);
  EXPECT_EQ(ranges(13), 1);
  EXPECT_EQ(ranges(89), 2);
  EXPECT_EQ(ranges(10000), -1);
  EXPECT_EQ(ranges(-10000), -1);

  // Check coverage
  EXPECT_EQ(microtest::GraphTest::checkCoverage({"1", "2", "3", "4", "5"}),
            true);
}

TEST(GraphCoverageTest, manyPathsBadCoverage) {
  // Start tracking coverage
  microtest::GraphTrackingMarker tracking =
      microtest::GraphTest::startGraphTracking();

  // Run some tests on some inputs
  EXPECT_EQ(ranges(0), 0);
  EXPECT_EQ(ranges(10000), -1);

  // Check coverage
  EXPECT_EQ(microtest::GraphTest::checkCoverage({"1", "2", "3", "4", "5"}),
            false);
}

/** Test the RAII aspect of Graph testing, where the object's drop functinoality
 * clears progress on the test condition. */
TEST(GraphCoverageTest, GraphTestRAII) {
  {
    // Start tracking coverage
    microtest::GraphTrackingMarker tracking =
        microtest::GraphTest::startGraphTracking();

    // Run some tests on some inputs
    EXPECT_EQ(ranges(0), 0);
    EXPECT_EQ(ranges(13), 1);
    EXPECT_EQ(ranges(89), 2);
    EXPECT_EQ(ranges(10000), -1);
    EXPECT_EQ(ranges(-10000), -1);

    // Check coverage
    EXPECT_EQ(microtest::GraphTest::checkCoverage({"1", "2", "3", "4", "5"}),
              true);
  }

  {
    // Start tracking coverage
    microtest::GraphTrackingMarker tracking =
        microtest::GraphTest::startGraphTracking();

    // Run some tests on some inputs
    EXPECT_EQ(ranges(0), 0);
    EXPECT_EQ(ranges(89), 2);

    // Check coverage
    EXPECT_EQ(microtest::GraphTest::checkCoverage({"1", "2", "3", "4", "5"}),
              false);
  }
}
