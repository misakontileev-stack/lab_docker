cmake_minimum_required(VERSION 3.10)
project(solver)

# Версия проекта для CPack (переменные ожидаются в CPackConfig.cmake)
set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION "${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK}")
set(PRINT_VERSION_STRING "solver ${PRINT_VERSION}")

# Подключаем библиотеки форматирования (от которых зависит solver)
add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex)

# Подключаем solver_lib и сам solver
add_subdirectory(solver_lib)
add_subdirectory(solver)

# Установка целей (чтобы пакет содержал файлы)
install(TARGETS solver_lib formatter_lib formatter_ex solver
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY include/ DESTINATION include)

# Подключаем конфигурацию CPack
include(CPackConfig.cmake)
