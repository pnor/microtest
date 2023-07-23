#include "lib/microtest/mutation.hpp"
#include <gtest/gtest.h>
#include <string>

// ===== Test Function to be mutated ===============

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
    if (c == '(' || c == '[' || c == '{') {
      stack.push_back(c);
    } else if (c == ')') {
      if (stack.empty() || stack.back() != '(') {
        return false;
      }
      stack.pop_back();
    } else if (c == ']') {
      if (stack.empty() || stack.back() != '[') {
        return false;
      }
      stack.pop_back();
    } else if (c == '}') {
      if (stack.empty() || stack.back() != '{') {
        return false;
      }
      stack.pop_back();
    }
  }
  std::vector<int>::size_type stackSize = stack.size();
  microtest::MutationTest::incrementMutable<std::vector<int>::size_type>(
      stackSize, "incSize");
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
