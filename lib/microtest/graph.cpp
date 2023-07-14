#include "graph.hpp"
#include <iostream>

namespace microtest {

// ====== Graph Tracking ======
GraphTrackingMarker GraphTest::startGraphTracking() {
  return GraphTrackingMarker();
}

void GraphTest::graphNode(const std::string s) {
  GraphTest &gt = GraphTest::getInstance();
  gt.nodesPassed.insert(s);
}

bool GraphTest::checkCoverage(const std::vector<std::string> &nodes) {
  GraphTest &gt = GraphTest::getInstance();
  for (const auto &node : nodes) {
    if (gt.nodesPassed.find(node) == gt.nodesPassed.end()) {
      return false;
    }
  }
  return true;
}

// ===== GraphTrackingMarker ======

GraphTrackingMarker::~GraphTrackingMarker() {
  GraphTest &gt = GraphTest::getInstance();
  gt.nodesPassed = std::set<std::string>();
}

} // namespace microtest
