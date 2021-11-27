cmake_minimum_required(VERSION 3.10)

project(disjoint_set LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(disjoint_set INTERFACE)
target_include_directories(disjoint_set INTERFACE include/)

Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.7)

FetchContent_MakeAvailable(Catch2)

add_executable(tests src/tests.cpp src/disjoint_tests.cpp)
target_link_libraries(tests PRIVATE disjoint_set)
target_link_libraries(tests PRIVATE Catch2::Catch2)
target_compile_options(tests PRIVATE
  -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
