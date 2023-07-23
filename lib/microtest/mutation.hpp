#pragma once

#include <csignal>
#include <functional>
#include <set>
#include <string>
#include <vector>

namespace microtest {

struct MutationTestResults;

using MutationResult = std::pair<std::vector<std::string>, MutationTestResults>;

/** Class that reports the result of the test suite on a mutation. */
struct MutationTestResults {
public:
  int testsKilled;
  int testsSurvived;

  MutationTestResults(int killed, int survived)
      : testsKilled(killed), testsSurvived(survived){};

  MutationTestResults() : testsKilled(0), testsSurvived(0){};
};

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
  static std::vector<MutationResult>
  runMutationTests(std::vector<std::function<bool()>> testFunctions,
                   std::vector<std::string> tags);

  /** Returns the result of `lhs > rhs`.
   * If the tag is chosen to mutate, will instead return `lhs >= rhs`
   */
  template <typename T>
  static bool greaterThanMutatable(T lhs, T rhs, const std::string &tag) {
    MutationTest &mt = getInstance();
    if (mt.activeTags.contains(tag)) {
      return lhs >= rhs;
    } else {
      return lhs > rhs;
    }
  }

  /** Returns the result of `lhs < rhs`.
   * If the tag is chosen to mutate, will instead return `lhs <= rhs`
   */
  template <typename T>
  static bool lessThanMutable(T lhs, T rhs, const std::string &tag) {
    MutationTest &mt = getInstance();
    if (mt.activeTags.contains(tag)) {
      return lhs <= rhs;
    } else {
      return lhs < rhs;
    }
  }

  /** Returns the result of `lhs == rhs`.
   * If the tag is chosen to mutate, will instead return `lhs != rhs`
   */
  template <typename T>
  static bool equalityMutable(T lhs, T rhs, const std::string &tag) {
    MutationTest &mt = getInstance();
    if (mt.activeTags.contains(tag)) {
      return lhs != rhs;
    } else {
      return lhs == rhs;
    }
  }

  /** Returns the result of `lhs != rhs`.
   * If the tag is chosen to mutate, will instead return `lhs == rhs`
   */
  template <typename T>
  static bool inequalityMutable(T lhs, T rhs, const std::string &tag) {
    MutationTest &mt = getInstance();
    if (mt.activeTags.contains(tag)) {
      return lhs == rhs;
    } else {
      return lhs != rhs;
    }
  }

  /** When this mutation is active, increments `number` by 1. */
  template <typename T>
  static void incrementMutable(T &number, const std::string &tag) {
    MutationTest &mt = getInstance();
    if (mt.activeTags.contains(tag)) {
      number += 1;
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
