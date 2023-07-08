#include "expect.hpp"

#include <cmath>

namespace microtest {

bool expectEquals(float expected, float actual, float epsilon) {
  if (abs(expected - actual) <= epsilon) {
    return true;
  }
  std::cout << expected << "was not close to " << actual
            << " within epsilon = " << epsilon << std::endl;
  return false;
}

} // namespace microtest
