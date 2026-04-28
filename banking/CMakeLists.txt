cmake_minimum_required(VERSION 3.10)
project(banking)

# Путь к заголовкам
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(banking STATIC
    Account.cpp
    Transaction.cpp
)
