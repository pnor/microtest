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
  // Threre are 2 predicates in `stringCompose`. We test this function when all
  // 2 predicates evaluate to both true or false in at least one test.

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

TEST(ClauseTesting, isOdd) {
  // For the simple function `isOdd`, there is only 1 clause:
  // `x % 2 == 2`
  // we can do expectations on the 2 possible values

  EXPECT_EQ(microtest::expectEquals(isOdd(1), true), true);
  EXPECT_EQ(microtest::expectEquals(isOdd(0), false), true);
}

TEST(ClauseTesting, stringCompose) {
  // Threre are 3 predicates in `stringCompose`:
  // - `sayOne`
  // - `sayTwo`
  // - `dontSayOne`

  // `sayOne` == true, `sayTwo` == true, `dontSayOne` == true
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(true, true, true), "two"),
            true);
  // `sayOne` == true, `sayTwo` == true, `dontSayOne` == false
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(true, true, false), "one two"),
            true);

  // `sayOne` == true, `sayTwo` == false, `dontSayOne` == true
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(true, false, true), ""),
            true);
  // `sayOne` == true, `sayTwo` == false, `dontSayOne` == false
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(true, false, false), "one "),
            true);

  // `sayOne` == false, `sayTwo` == true, `dontSayOne` == true
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(false, true, true), "two"),
            true);
  // `sayOne` == false, `sayTwo` == true, `dontSayOne` == false
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(false, true, false), "two"),
            true);

  // `sayOne` == false, `sayTwo` == false, `dontSayOne` == true
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(false, false, true), ""),
            true);
  // `sayOne` == false, `sayTwo` == false, `dontSayOne` == false
  EXPECT_EQ(microtest::expectEquals<std::string>(
                stringCompose(false, false, false), ""),
            true);
}
