#include "mutation.hpp"

static void microtest::MutationTest::runMutationTests(
    std::vector<std::function<bool()>> testFunctions,
    std::vector<std::string> tags) {
  // TODO
  //
  // create list of all tag combos (combinatorix)
  // for each combo, run test suite
  // record if it killed or survived
  //
  // return results
}

static void
microtest::MutationTest::setAllTags(const std::vector<std::string> &tags) {
  allTags.clear();
  for (const auto &t : tags) {
    allTags.insert(t);
  }
}

microtest::MutationTest::setActiveTags(const std::vector<std::string> &tags) {
  activeTags.clear();
  for (const auto &t : tags) {
    activeTags.insert(t);
  }
}
