#include "lib/microtest/mutation.hpp"
#include <gtest/gtest.h>
#include <string>

// ===== Test Function to be mutated ===============

// Available Mutations
static const std::string PAREN_OPEN_PUSH = "parenOpenPush";
static const std::string BRACKET_OPEN_CLOSE_CHECK = "bracketOpenCloseCheck";
static const std::string BRACKET_CLOSE = "bracketClose";
static const std::string SQUARE_OPEN_CLOSE_CHECK = "squareOpenCloseCheck";
static const std::string SQUARE_CLOSE = "squareClose";
static const std::string PAREN_OPEN_CLOSE_CHECK = "parenOpenCloseCheck";
static const std::string PAREN_CLOSE = "parenClose";
static const std::string BRACKET_OPEN_PUSH = "bracketOpenPush";
static const std::string SQUARE_OPEN_PUSH = "squareOpenPush";
static const std::string INC_SIZE = "incSize";

/** A valid solution of the leetcode problem #20
 * https://leetcode.com/problems/valid-parentheses/description/
 * It has been modified with potential mutation points, that will be tested
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid. An input string is valid if:
 *
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 */
static bool isValidParenthesesString(const std::string &s) {
  std::vector<char> stack;
  for (const auto &c : s) {
    if (microtest::MutationTest::equalityMutable(c, '(', PAREN_OPEN_PUSH) ||
        microtest::MutationTest::equalityMutable(c, '[', SQUARE_OPEN_PUSH) ||
        microtest::MutationTest::equalityMutable(c, '{', BRACKET_OPEN_PUSH)) {
      stack.push_back(c);
    } else if (microtest::MutationTest::equalityMutable(c, ')', PAREN_CLOSE)) {
      if (stack.empty() || microtest::MutationTest::inequalityMutable(
                               stack.back(), '(', PAREN_OPEN_CLOSE_CHECK)) {
        return false;
      }
      stack.pop_back();
    } else if (microtest::MutationTest::equalityMutable(c, ']', SQUARE_CLOSE)) {
      if (stack.empty() || microtest::MutationTest::inequalityMutable(
                               stack.back(), '[', SQUARE_OPEN_CLOSE_CHECK)) {
        return false;
      }
      stack.pop_back();
    } else if (microtest::MutationTest::equalityMutable(c, '}',
                                                        BRACKET_CLOSE)) {
      if (stack.empty() || microtest::MutationTest::inequalityMutable(
                               stack.back(), '{', BRACKET_OPEN_CLOSE_CHECK)) {
        return false;
      }
      stack.pop_back();
    }
  }
  std::vector<int>::size_type stackSize = stack.size();
  microtest::MutationTest::incrementMutable<std::vector<int>::size_type>(
      stackSize, INC_SIZE);
  return stackSize == 0;
}

// ===== Test Suite for the Function ===============

static bool testCase1() { return isValidParenthesesString("()") == true; }
static bool testCase2() { return isValidParenthesesString(")") == false; }
static bool testCase3() { return isValidParenthesesString("({})") == true; }
static bool testCase4() { return isValidParenthesesString("[({})]") == true; }
static bool testCase5() { return isValidParenthesesString("[](){}") == true; }
static bool testCase6() { return isValidParenthesesString("[(})]") == false; }
static bool testCase7() { return isValidParenthesesString("[([]])") == false; }
static bool testCase8() { return isValidParenthesesString("") == true; }

static std::vector<std::function<bool()>> testFunctions = {
    testCase1, testCase2, testCase3, testCase4,
    testCase5, testCase6, testCase7, testCase8};

// ===== Google Testing Mutations Test

TEST(SanityTest, TestFunctionPassesTestsInGeneral) {
  for (const std::function<bool()> &f : testFunctions) {
    EXPECT_TRUE(f());
  }
}

TEST(MutationTests, NoMutations) {
  std::vector<microtest::MutationResult> results =
      microtest::MutationTest::runMutationTests(testFunctions, {});

  bool ranOneTest = false;
  for (const auto &res : results) {
    ranOneTest = true;
    EXPECT_EQ(res.second.testsFailed, 0);
  }
  EXPECT_TRUE(ranOneTest);
}

TEST(MutationTests, OneMutation) {
  std::vector<microtest::MutationResult> results =
      microtest::MutationTest::runMutationTests(testFunctions, {INC_SIZE});

  int testsRan = 0;
  int testsFailed = 0;
  for (const auto &res : results) {
    testsRan += 1;
    testsFailed += res.second.testsFailed;
  }
  EXPECT_EQ(testsRan, 2);
  EXPECT_TRUE(testsFailed > 0);
}
