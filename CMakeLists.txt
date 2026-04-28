cmake_minimum_required(VERSION 3.10)
project(lab05)

# Добавляем путь к заголовочным файлам
include_directories(include)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex)
add_subdirectory(solver_lib)
add_subdirectory(hello_world)
add_subdirectory(solver)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check gtest_main gtest pthread)
  add_test(NAME check COMMAND check)
endif()
