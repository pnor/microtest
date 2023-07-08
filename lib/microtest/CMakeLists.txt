cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  microtest
  SHARED
  microtest.cpp
  microtest.hpp
  expect.hpp
  expect.cpp
)
