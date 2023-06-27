cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  microtest_src
  main.cpp
)

target_link_libraries(
  microtest_src
  PRIVATE
  microtest
)

target_include_directories(
  microtest_src
  PUBLIC
  ${microtest_main_SOURCE_DIR}
  ${microtest_main_SOURCE_DIR}/lib/microtest
)
