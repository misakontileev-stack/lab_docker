# CMake generated Testfile for 
# Source directory: /home/misha/misakontileev/workspace/projects/lab05
# Build directory: /home/misha/misakontileev/workspace/projects/lab05/_build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(check "/home/misha/misakontileev/workspace/projects/lab05/_build/check")
set_tests_properties(check PROPERTIES  _BACKTRACE_TRIPLES "/home/misha/misakontileev/workspace/projects/lab05/CMakeLists.txt;20;add_test;/home/misha/misakontileev/workspace/projects/lab05/CMakeLists.txt;0;")
subdirs("formatter_lib")
subdirs("formatter_ex")
subdirs("solver_lib")
subdirs("hello_world")
subdirs("solver")
subdirs("third-party/gtest")
