#include "mutation.hpp"
#include <iostream>

// ===== Helper =====

namespace microtest {
std::vector<std::vector<std::string>>
generatePermutations(const std::vector<std::string> &arr, int index) {
  if (index == static_cast<int>(arr.size())) {
    return {{}}; // Return an empty permutation for an empty array
  }

  std::vector<std::vector<std::string>> result;
  std::vector<std::vector<std::string>> subPermutations =
      generatePermutations(arr, index + 1);
  std::string currentElement = arr[index];

  // Include the current element
  for (const auto &subPermutation : subPermutations) {
    std::vector<std::string> newPermutation = subPermutation;
    newPermutation.insert(newPermutation.begin(), currentElement);
    result.push_back(newPermutation);
  }

  // Exclude the current element
  result.insert(result.end(), subPermutations.begin(), subPermutations.end());

  return result;
}

std::vector<std::vector<std::string>>
getAllPermutations(const std::vector<std::string> &arr) {
  return generatePermutations(arr, 0);
}

// ===== Header =====

std::vector<MutationResult>
MutationTest::runMutationTests(std::vector<std::function<bool()>> testFunctions,
                               std::vector<std::string> tags) {
  // create list of all tag combos (combinatorix)
  std::vector<std::vector<std::string>> tagCombinations =
      getAllPermutations(tags);

  // for each combo, run test suite
  // record if it killed or survived
  std::vector<MutationResult> resultVec;

  MutationTest &mt = MutationTest::getInstance();
  for (const std::vector<std::string> &tagCombo : tagCombinations) {
    mt.setActiveTags(tagCombo);
    int failed = 0;
    for (const auto &f : testFunctions) {
      failed = f() ? failed : failed + 1;
    }
    MutationTestResults testResult(failed, testFunctions.size() - failed);
    resultVec.push_back(std::make_pair(tagCombo, testResult));
  }

  return resultVec;
}

void MutationTest::setActiveTags(const std::vector<std::string> &tags) {
  activeTags.clear();
  for (const auto &t : tags) {
    activeTags.insert(t);
  }
}

}; // namespace microtest
