#pragma once

#include <csignal>
#include <functional>
#include <set>
#include <string>
#include <vector>

namespace microtest {

class MutationTest {
public:
  MutationTest(MutationTest const &) = delete;
  void operator=(MutationTest const &) = delete;

  /**
   * Runs mutation tests by mutating every combination of possible mutations
   * marked in `tags` and running every test in `testFunctions`.
   *
   * Records the number of mutations that were "killed" by the test suite (at
   * least one test failed/returned false).
   */
  static void runMutationTests(std::vector<std::function<bool()>> testFunctions,
                               std::vector<std::string> tags);

  /** Returns the result of `lhs > rhs`.
   * If the tag is chosen to mutate, will instead return `lhs >= rhs`
   */
  template <typename N>
  static bool greaterThanMutatable(N lhs, N rhs, const std::string &tag) {
    MutationTest &mt = getInstance();
    if (mt.activeTags.contains(tag)) {
      return lhs > rhs;
    } else {
      return lhs >= rhs;
    }
  }

private:
  std::set<std::string> activeTags;
  std::set<std::string> allTags;

  static MutationTest &getInstance() {
    static MutationTest instance;
    return instance;
  }

  MutationTest() {}

  void setAllTags(const std::vector<std::string> &tags);

  void setActiveTags(const std::vector<std::string> &tags);
};

}; // namespace microtest
