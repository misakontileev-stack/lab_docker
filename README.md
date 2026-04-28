## Laboratory work V

Данная лабораторная работа посвещена изучению фреймворков для тестирования на примере **GTest**

```sh
$ open https://github.com/google/googletest
```

## Tasks

- [ ] 1. Создать публичный репозиторий с названием **lab05** на сервисе **GitHub**
- [ ] 2. Выполнить инструкцию учебного материала
- [ ] 3. Ознакомиться со ссылками учебного материала
- [ ] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```sh
$ export GITHUB_USERNAME=<имя_пользователя>
$ alias gsed=sed # for *-nix system
```

```sh
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .

```sh
~/misakontileev/workspace ~/misakontileev/workspace ~/misakontileev/workspace ~/misakontileev/workspace
```

```sh
$ source scripts/activate
```

```sh
$ git clone https://github.com/misakontileev-stack/lab_04_1 projects/lab05
```

```sh
Клонирование в «projects/lab05»...
remote: Enumerating objects: 61, done.
remote: Counting objects: 100% (61/61), done.
remote: Compressing objects: 100% (37/37), done.
remote: Total 61 (delta 16), reused 55 (delta 10), pack-reused 0 (from 0)
Получение объектов: 100% (61/61), 9.12 КиБ | 9.13 МиБ/с, готово.
Определение изменений: 100% (16/16), готово.
```

```sh
$ cd projects/lab05
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab05
```

```sh
$ mkdir third-party
$ git submodule add https://github.com/google/googletest third-party/gtest

```sh
Клонирование в «/home/misha/misakontileev/workspace/projects/lab05/third-party/gtest»...
remote: Enumerating objects: 28627, done.
remote: Counting objects: 100% (61/61), done.
remote: Compressing objects: 100% (46/46), done.
remote: Total 28627 (delta 32), reused 15 (delta 15), pack-reused 28566 (from 2)
Получение объектов: 100% (28627/28627), 13.74 МиБ | 31.00 КиБ/с, готово.
Определение изменений: 100% (21273/21273), готово.
```

```sh
$ cd third-party/gtest && git checkout release-1.8.1 && cd ../..
```

```sh
Примечание: переключение на «release-1.8.1».

Вы сейчас в состоянии «отсоединённого указателя HEAD». Можете осмотреться,
внести экспериментальные изменения и зафиксировать их, также можете
отменить любые коммиты, созданные в этом состоянии, не затрагивая другие
ветки, переключившись обратно на любую ветку.

Если хотите создать новую ветку для сохранения созданных коммитов, можете
сделать это (сейчас или позже), используя команду switch с параметром -c.
Например:

  git switch -c <новая-ветка>

Или отмените эту операцию с помощью:

  git switch -

Отключите этот совет, установив переменную конфигурации
advice.detachedHead в значение false

HEAD сейчас на 2fe3bd99 Merge pull request #1433 from dsacre/fix-clang-warnings
```

```sh
$ git add third-party/gtest
$ git commit -m"added gtest framework"
```
```sh
$ gsed -i '/option(BUILD_EXAMPLES "Build examples" OFF)/a\
option(BUILD_TESTS "Build tests" OFF)
' CMakeLists.txt
$ cat >> CMakeLists.txt <<EOF

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB \${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check \${\${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check \${PROJECT_NAME} gtest_main)
  add_test(NAME check COMMAND check)
endif()
EOF
```

```sh
$ mkdir tests
$ cat > tests/test1.cpp <<EOF
#include <print.hpp>

#include <gtest/gtest.h>

TEST(Print, InFileStream)
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text);
}
EOF
```

```sh
$ cmake -H. -B_build -DBUILD_TESTS=ON
$ cmake --build _build

```sh
[  5%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 10%] Linking CXX static library libgtest.a
[ 10%] Built target gtest
[ 15%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 20%] Linking CXX static library libgtest_main.a
[ 20%] Built target gtest_main
[ 25%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[ 30%] Linking CXX executable check
[ 30%] Built target check
[ 35%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 40%] Linking CXX static library libformatter.a
[ 40%] Built target formatter
[ 45%] Building CXX object formatter_ex/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 50%] Linking CXX static library libformatter_ex.a
[ 50%] Built target formatter_ex
[ 55%] Building CXX object solver_lib/CMakeFiles/solver_lib.dir/solver.cpp.o
[ 60%] Linking CXX static library libsolver_lib.a
[ 60%] Built target solver_lib
[ 65%] Building CXX object hello_world/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 70%] Linking CXX executable hello_world
[ 70%] Built target hello_world
[ 75%] Building CXX object solver/CMakeFiles/solver.dir/equation.cpp.o
[ 80%] Linking CXX executable solver
[ 80%] Built target solver
[ 85%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 90%] Linking CXX static library libgmock.a
[ 90%] Built target gmock
[ 95%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library libgmock_main.a
[100%] Built target gmock_main
```
```
$ cmake --build _build --target test
```

```sh
Running tests...
Test project /home/misha/misakontileev/workspace/projects/lab05/_build
    Start 1: check
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

```sh
$ _build/check
```

```sh
Running main() from /home/misha/misakontileev/workspace/projects/lab05/third-party/gtest/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from Print
[ RUN      ] Print.InFileStream
[       OK ] Print.InFileStream (0 ms)
[----------] 1 test from Print (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

```
$ cmake --build _build --target test -- ARGS=--verbose
```
```sh
Running tests...
UpdateCTestConfiguration  from :/home/misha/misakontileev/workspace/projects/lab05/_build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/misha/misakontileev/workspace/projects/lab05/_build/DartConfiguration.tcl
Test project /home/misha/misakontileev/workspace/projects/lab05/_build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: check

1: Test command: /home/misha/misakontileev/workspace/projects/lab05/_build/check
1: Working Directory: /home/misha/misakontileev/workspace/projects/lab05/_build
1: Test timeout computed to be: 10000000
1: Running main() from /home/misha/misakontileev/workspace/projects/lab05/third-party/gtest/googletest/src/gtest_main.cc
1: [==========] Running 1 test from 1 test case.
1: [----------] Global test environment set-up.
1: [----------] 1 test from Print
1: [ RUN      ] Print.InFileStream
1: [       OK ] Print.InFileStream (0 ms)
1: [----------] 1 test from Print (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test case ran. (0 ms total)
1: [  PASSED  ] 1 test.
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```
```sh
$ gsed -i 's/lab04/lab05/g' README.md
$ mkdir -p .github/workflows
$ cat > .github/workflows/ci.yml << 'EOF'
name: CI

on:
  push:
    branches: [ master, main ]
  pull_request:
    branches: [ master, main ]

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
      with:
        submodules: recursive
    
    - name: Configure CMake
      run: cmake -B _build -DBUILD_TESTS=ON
    
    - name: Build
      run: cmake --build _build
    
    - name: Run tests
      run: cmake --build _build --target test -- ARGS=--verbose
EOF
```

```sh
$ travis lint
```

```sh
$ git add .travis.yml
$ git add tests
$ git add -p
$ git commit -m"added tests"
$ git push origin master
```

```sh
$ travis login --auto
$ travis enable
```

```sh
$ mkdir artifacts
$ sleep 20s && gnome-screenshot --file artifacts/screenshot.png
# for macOS: $ screencapture -T 20 artifacts/screenshot.png
# open https://github.com/${GITHUB_USERNAME}/lab05
```


## Homework

### Задание
1. Создайте `CMakeList.txt` для библиотеки *banking*.
2. Создайте модульные тесты на классы `Transaction` и `Account`.
    * Используйте mock-объекты.
    * Покрытие кода должно составлять 100%.
3. Настройте сборочную процедуру на **TravisCI**.
4. Настройте [Coveralls.io](https://coveralls.io/).

