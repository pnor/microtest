#include "lib/microtest/expect.hpp"
#include <gtest/gtest.h>
#include <string>

/**
 * Tests demonstrating clause and predicate based testing methods
 */

/** Returns `true` if `x` is not divisible by 2, and `false` otherwise. */
static bool isOdd(const int &x) {
  if (x % 2 == 1) {
    return true;
  } else {
    return false;
  }
}

/** Returns a string based on the values of the function inputs */
static std::string stringCompose(const bool &sayOne, const bool &sayTwo,
                                 const bool &dontSayOne) {
  std::string s;
  if (!dontSayOne && sayOne) {
    s += "one ";
  }
  if (sayTwo) {
    s += "two";
  }

  return s;
}

TEST(PredicateTesting, isOdd) {
  // For the simple function `isOdd`, there is only 1 predicate:
  // `x % 2 == 2`
  // we can do expectations on the 2 possible values

  EXPECT_EQ(microtest::expectEquals(isOdd(1), true), true);
  EXPECT_EQ(microtest::expectEquals(isOdd(0), false), true);
}

TEST(PredicateTesting, stringCompose) {
  // Threre are 3 predicates in `stringCompose`. We test this function when all
  // 3 predicates evaluate to both true or false in at least one test.

  // `(!dontSayOne && sayOne)` == true and `(sayTwo)` == true
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(true, true, false), "one two"),
            true);
  // `(!dontSayOne && sayOne)` == true and `(sayTwo)` == false
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(true, false, false), "one "),
            true);

  // `(!dontSayOne && sayOne)` == false and `(sayTwo)` == true
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(false, true, true), "two"),
            true);
  // `(!dontSayOne && sayOne)` == false and `(sayTwo)` == false
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(false, false, true), ""),
            true);
}
