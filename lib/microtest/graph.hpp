#pragma once

#include <set>
#include <string>
#include <vector>

namespace microtest {

class GraphTrackingMarker {
public:
  GraphTrackingMarker() {}
  ~GraphTrackingMarker();
};

class GraphTest {
public:
  GraphTest(GraphTest const &) = delete;
  void operator=(GraphTest const &) = delete;

  /** Starts tracking nodes passed in other functions */
  static GraphTrackingMarker startGraphTracking();

  /** Place a tracking graph node on a function*/
  static void graphNode(std::string name);

  /** Checks if a function has passed all nodes listed based on strings */
  static bool checkCoverage(const std::vector<std::string> &nodes);

private:
  std::set<std::string> nodesPassed;

  static GraphTest &getInstance() {
    static GraphTest instance;
    return instance;
  }

  GraphTest() {}

  friend class GraphTrackingMarker;
};

} // namespace microtest
