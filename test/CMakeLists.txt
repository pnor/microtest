cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
  microtest_test
  expect.cpp
  graph.cpp
  logic.cpp
)

target_link_libraries(
  microtest_test
  PRIVATE
  gtest_main
  microtest
)

target_include_directories(
  microtest_test
  PUBLIC
  ${microtest_main_SOURCE_DIR}
  ${microtest_main_SOURCE_DIR}/lib/microtest
)
