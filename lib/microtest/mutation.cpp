#include "mutation.hpp"

// ===== Helper =====

namespace microtest {
static inline constexpr std::vector<std::vector<std::string>>
stringCombinationsOfSize(const std::vector<std::string> &strings,
                         int startIndex, int size) {
  // TODO ?? this work
  if (static_cast<int>(strings.size()) - startIndex - size < 0) {
    return {};
  } else if (size <= 0) {
    return {{}};
  }

  std::vector<std::vector<std::string>> results;

  for (int i = startIndex; i < strings.size() - size; i++) {
    std::string cur = strings.at(i);
    std::vector<std::vector<std::string>> rest =
        stringCombinationsOfSize(strings, startIndex + 1, size);
    for (auto &res : rest) {
      res.push_back(cur);
      results.push_back(res);
    }
  }

  return results;
}

// ===== Header =====

/**
 * Return all combinations of strings in `strings`
 */
static std::vector<std::vector<std::string>>
stringCombinations(const std::vector<std::string> &strings) {
  std::vector<std::vector<std::string>> results;
  for (int i = 0; i < strings.size(); i++) {
    std::vector<std::vector<std::string>> strs =
        stringCombinationsOfSize(strings, 0, i);
    results.insert(results.end(), strs.begin(), strs.end());
  }
  return results;
}

std::vector<MutationResult>
MutationTest::runMutationTests(std::vector<std::function<bool()>> testFunctions,
                               std::vector<std::string> tags) {
  // create list of all tag combos (combinatorix)
  std::vector<std::vector<std::string>> tagCombinations =
      stringCombinations(tags);

  // for each combo, run test suite
  // record if it killed or survived
  std::vector<MutationResult> resultVec;

  for (const std::vector<std::string> &tagCombo : tagCombinations) {
    int killed = 0;
    for (const auto &f : testFunctions) {
      killed = f() ? killed : killed + 1;
    }
    MutationTestResults testResult(killed, testFunctions.size() - killed);
    resultVec.push_back(std::make_pair(tagCombo, testResult));
  }

  return resultVec;
}

void MutationTest::setAllTags(const std::vector<std::string> &tags) {
  allTags.clear();
  for (const auto &t : tags) {
    allTags.insert(t);
  }
}

void MutationTest::setActiveTags(const std::vector<std::string> &tags) {
  activeTags.clear();
  for (const auto &t : tags) {
    activeTags.insert(t);
  }
}

}; // namespace microtest
