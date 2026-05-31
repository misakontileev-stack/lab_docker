cmake_minimum_required(VERSION 3.10)
project(solver)

# Версия проекта (используется в CPack)
set(PRINT_VERSION_MAJOR 0)    # можно переименовать в SOLVER_VERSION_... но для совместимости с CPackConfig оставим как есть
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION "${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK}")
set(PRINT_VERSION_STRING "solver ${PRINT_VERSION}")

add_subdirectory(solver_lib)
add_subdirectory(solver)

# Установка исполняемого файла и библиотеки (для пакета)
install(TARGETS solver_lib solver
        RUNTIME DESTINATION bin      # для solver.exe
        LIBRARY DESTINATION lib      # для .so/.dylib
        ARCHIVE DESTINATION lib)     # для .a

install(DIRECTORY include/ DESTINATION include)   # если у solver есть публичные заголовки

include(CPackConfig.cmake)
