#pragma once

#include <iostream>
#include <vector>

namespace microtest {

/**
   Asserts that `expected` is equal to `actual`
 */
template <typename N> bool expectEquals(N expected, N actual) {
  if (expected != actual) {
    std::cout << expected << " was not equal to " << actual << std::endl;
    return false;
  }
  return true;
}

bool expectEquals(float expected, float actual, float epsilon);

template <typename N>
bool expectVectorEquals(const std::vector<N> &expected,
                        const std::vector<N> &actual) {
  if (expected.size() != actual.size()) {
    std::cout << "expected and actual not of equal length" << std::endl;
    return false;
  }

  for (int i = 0; i < expected.size(); i++) {
    bool res = expectEquals(expected[i], actual[i]);
    if (!res) {
      return false;
    }
  }
  return true;
}

} // namespace microtest
