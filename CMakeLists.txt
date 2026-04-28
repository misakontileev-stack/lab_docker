cmake_minimum_required(VERSION 3.10)
project(lab05)

include_directories(include)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex)
add_subdirectory(solver_lib)
add_subdirectory(hello_world)
add_subdirectory(solver)

if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
  
  file(GLOB TEST_SOURCES tests/*.cpp)
  add_executable(check ${TEST_SOURCES})
  target_link_libraries(check ${GTEST_LIBRARIES} gtest_main pthread)
  add_test(NAME check COMMAND check)
endif()
