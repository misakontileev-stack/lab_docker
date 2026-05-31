cmake_minimum_required(VERSION 3.10)
project(lab05)

include_directories(include banking /usr/include)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex)
add_subdirectory(solver_lib)
add_subdirectory(hello_world)
add_subdirectory(solver)
add_subdirectory(banking)

if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})

  # Тест для print 
  add_executable(check tests/test1.cpp)
  target_link_libraries(check ${GTEST_LIBRARIES} gtest_main pthread)
  add_test(NAME check COMMAND check)

  # Тесты для banking
  add_executable(banking_tests
      banking/tests/test_account.cpp
      banking/tests/test_transaction.cpp
  )
  target_link_libraries(banking_tests banking gtest gtest_main gmock pthread)
  add_test(NAME banking_tests COMMAND banking_tests)
endif()
include(CPackConfig.cmake)
