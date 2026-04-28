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
```

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
```

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
```

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
$ git add .

$ git commit -m "Update files"

$ git push origin master
```

```sh
$ mkdir artifacts

$ sleep 20s && gnome-screenshot --file artifacts/screenshot.png

# for macOS: $ screencapture -T 20 artifacts/screenshot.png

# open https://github.com/${GITHUB_USERNAME}/lab05
```

## Report

```sh
$ popd

$ export LAB_NUMBER=05

$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}

$ mkdir reports/lab${LAB_NUMBER}

$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md

$ cd reports/lab${LAB_NUMBER}

$ edit REPORT.md

$ gist REPORT.md
```


## Homework

### Задание
1. Создайте `CMakeList.txt` для библиотеки *banking*.
2. Создайте модульные тесты на классы `Transaction` и `Account`.
    * Используйте mock-объекты.
    * Покрытие кода должно составлять 100%.
3. Настройте сборочную процедуру на **TravisCI**.
4. Настройте [Coveralls.io](https://coveralls.io/).

```sh
$ cd banking

$ nano CMakeLists.txt
```

Записывает такой текст:

```sh
cmake_minimum_required(VERSION 3.10)
project(banking)

# Путь к заголовкам
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(banking STATIC
    Account.cpp
    Transaction.cpp
)
```

```sh
$ mkdir tests

$ cd tests

$ mkdir mocks

$ cd mocks

$ nano MockAccount.hpp
```
```sh
#ifndef MOCK_ACCOUNT_HPP
#define MOCK_ACCOUNT_HPP

#include "Account.h"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

#endif
```

```sh
$ nano MockTransaction.hpp
```

```sh
#ifndef MOCK_TRANSACTION_HPP
#define MOCK_TRANSACTION_HPP

#include "Transaction.h"
#include <gmock/gmock.h>

class MockTransaction : public Transaction {
public:
    MockTransaction() : Transaction() {}
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

#endif
```

```sh
$ cd ..

$ nano test_account.cpp
```

```sh
#include <gtest/gtest.h>
#include "Account.h"

TEST(AccountTest, Constructor) {
    Account acc(1, 100);
    EXPECT_EQ(acc.id(), 1);
    EXPECT_EQ(acc.GetBalance(), 100);
}

TEST(AccountTest, LockAndChangeBalance) {
    Account acc(1, 100);
    acc.Lock();
    acc.ChangeBalance(50);
    EXPECT_EQ(acc.GetBalance(), 150);
    acc.Unlock();
}

TEST(AccountTest, ChangeBalanceWithoutLockThrows) {
    Account acc(1, 100);
    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
}

TEST(AccountTest, LockTwiceThrows) {
    Account acc(1, 100);
    acc.Lock();
    EXPECT_THROW(acc.Lock(), std::runtime_error);
}
}

TEST(AccountTest, UnlockWithoutLockDoesNothing) {
    Account acc(1, 100);
    EXPECT_NO_THROW(acc.Unlock());  // Unlock не бросает исключений
    // После Unlock можно заблокировать снова
    EXPECT_NO_THROW(acc.Lock());
}
```

```sh
$ nano test_transaction.cpp
```

```sh
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"
#include "mocks/MockAccount.hpp"
#include "mocks/MockTransaction.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;
using ::testing::AtLeast;

// Тест: попытка перевода на тот же счёт -> исключение
TEST(TransactionTest, SameAccountThrows) {
    MockAccount acc(1, 1000);
    Transaction tx;
    EXPECT_THROW(tx.Make(acc, acc, 200), std::logic_error);
}

// Тест: отрицательная сумма -> исключение
TEST(TransactionTest, NegativeSumThrows) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tx;
    EXPECT_THROW(tx.Make(from, to, -100), std::invalid_argument);
}
}

// Тест: сумма меньше 100 -> исключение
TEST(TransactionTest, SumTooSmallThrows) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tx;
    EXPECT_THROW(tx.Make(from, to, 50), std::logic_error);
}

// Тест: комиссия слишком большая -> возврат false
TEST(TransactionTest, FeeTooLargeReturnsFalse) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction tx;
    tx.set_fee(100);  // fee=100, 2*fee=200 > sum=150
    EXPECT_FALSE(tx.Make(from, to, 150));
}

// Успешный перевод (через моки)
TEST(TransactionTest, SuccessfulTransfer) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    // Ожидаем блокировку обоих счетов
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    // Ожидаем вызов Credit(to, sum) -> to.ChangeBalance(sum)
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    // Ожидаем Debit(from, sum+fee) -> from.ChangeBalance(-(sum+fee))
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);  // сумма 200 + fee 1 = 201
    // Разблокировка через деструктор Guard
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);Transaction tx;
    tx.set_fee(1);
    EXPECT_TRUE(tx.Make(from, to, 200));
}

// Недостаточно средств на from
TEST(TransactionTest, InsufficientFunds) {
    MockAccount from(1, 100);
    MockAccount to(2, 500);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(150)).Times(1);   // Credit
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(100));
    // Debit не выполнится, поэтому ChangeBalance(from) не будет
    // После неудачи делается откат: to.ChangeBalance(-150)
    EXPECT_CALL(to, ChangeBalance(-150)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    Transaction tx;
    tx.set_fee(1);
    EXPECT_FALSE(tx.Make(from, to, 150));
}

// Проверка, что SaveToDataBase вызывается
TEST(TransactionTest, SaveToDataBaseIsCalled) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    MockTransaction tx;   // мок транзакции, переопределяем SaveToDataBase

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);
    EXPECT_CALL(tx, SaveToDataBase(_, _, 200)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);
tx.set_fee(1);
    EXPECT_TRUE(tx.Make(from, to, 200));
}
```

```sh
$ nano CMakeLists.txt
```

В корне папки обновим CMakeLists.txt и теперь там такой код:

```sh
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
```

```sh
$ rm -rf _build

$ cmake -H. -B_build -DBUILD_TESTS=ON
```

Вывод:
```sh
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Deprecation Warning at formatter_lib/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at formatter_ex/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at solver_lib/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.
CMake Deprecation Warning at solver_lib/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at hello_world/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at solver/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Found GTest: /usr/lib/x86_64-linux-gnu/cmake/GTest/GTestConfig.cmake (found version "1.14.0")  
-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /home/misha/misakontileev/workspace/projects/lab05/_build
```

```sh 
$ cmake --build _build
```
```sh
[  5%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[ 11%] Linking CXX executable check
[ 11%] Built target check
[ 16%] Building CXX object banking/CMakeFiles/banking.dir/Account.cpp.o
[ 22%] Building CXX object banking/CMakeFiles/banking.dir/Transaction.cpp.o
[ 27%] Linking CXX static library libbanking.a
[ 27%] Built target banking
[ 33%] Building CXX object CMakeFiles/banking_tests.dir/banking/tests/test_account.cpp.o
[ 38%] Building CXX object CMakeFiles/banking_tests.dir/banking/tests/test_transaction.cpp.o
[ 44%] Linking CXX executable banking_tests
[ 44%] Built target banking_tests
[ 50%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 55%] Linking CXX static library libformatter.a
[ 55%] Built target formatter
[ 61%] Building CXX object formatter_ex/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 66%] Linking CXX static library libformatter_ex.a
[ 66%] Built target formatter_ex
[ 72%] Building CXX object solver_lib/CMakeFiles/solver_lib.dir/solver.cpp.o
[ 77%] Linking CXX static library libsolver_lib.a
[ 77%] Built target solver_lib
[ 83%] Building CXX object hello_world/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 88%] Linking CXX executable hello_world
[ 88%] Built target hello_world
[ 94%] Building CXX object solver/CMakeFiles/solver.dir/equation.cpp.o
[100%] Linking CXX executable solver
[100%] Built target solver
```

```sh
$ _build/check

$ cmake --build _build --target test -- ARGS=--verbose
```
```sh
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
1: Running main() from ./googletest/src/gtest_main.cc
1: [==========] Running 1 test from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 1 test from Print
1: [ RUN      ] Print.InFileStream
1: [       OK ] Print.InFileStream (0 ms)
1: [----------] 1 test from Print (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test suite ran. (0 ms total)
1: [  PASSED  ] 1 test.
1/2 Test #1: check ............................   Passed    0.00 sec
test 2
    Start 2: banking_tests
2: Test command: /home/misha/misakontileev/workspace/projects/lab05/_build/banking_tests
2: Working Directory: /home/misha/misakontileev/workspace/projects/lab05/_build
2: Test timeout computed to be: 10000000
2: Running main() from ./googletest/src/gtest_main.cc
2: [==========] Running 12 tests from 2 test suites.
2: [----------] Global test environment set-up.
2: [----------] 5 tests from AccountTest
2: [ RUN      ] AccountTest.Constructor
2: [       OK ] AccountTest.Constructor (0 ms)
2: [ RUN      ] AccountTest.LockAndChangeBalance
2: [       OK ] AccountTest.LockAndChangeBalance (0 ms)
2: [ RUN      ] AccountTest.ChangeBalanceWithoutLockThrows
2: [       OK ] AccountTest.ChangeBalanceWithoutLockThrows (0 ms)
2: [ RUN      ] AccountTest.LockTwiceThrows
2: [       OK ] AccountTest.LockTwiceThrows (0 ms)
2: [ RUN      ] AccountTest.UnlockWithoutLockDoesNothing
2: [       OK ] AccountTest.UnlockWithoutLockDoesNothing (0 ms)
2: [----------] 5 tests from AccountTest (0 ms total)
2: 
2: [----------] 7 tests from TransactionTest
2: [ RUN      ] TransactionTest.SameAccountThrows
2: [       OK ] TransactionTest.SameAccountThrows (0 ms)
2: [ RUN      ] TransactionTest.NegativeSumThrows
2: [       OK ] TransactionTest.NegativeSumThrows (0 ms)
2: [ RUN      ] TransactionTest.SumTooSmallThrows
2: [       OK ] TransactionTest.SumTooSmallThrows (0 ms)
2: [ RUN      ] TransactionTest.FeeTooLargeReturnsFalse
2: [       OK ] TransactionTest.FeeTooLargeReturnsFalse (0 ms)
2: [ RUN      ] TransactionTest.SuccessfulTransfer
2: 1 send to 2 $200
2: Balance 1 is 1000
2: Balance 2 is 
2: GMOCK WARNING:
2: Uninteresting mock function call - returning default value.
2:     Function call: GetBalance()
2:           Returns: 0
2: NOTE: You can safely ignore the above warning unless this call should not happen.  Do not suppress it by blindly adding an EXPECT_CALL() if you don't mean to enforce the call. >
2: 0
2: [       OK ] TransactionTest.SuccessfulTransfer (0 ms)
2: [ RUN      ] TransactionTest.InsufficientFunds
2: 1 send to 2 $150
2: Balance 1 is 100
2: Balance 2 is 
2: GMOCK WARNING:
2: Uninteresting mock function call - returning default value.
2:     Function call: GetBalance()
2:           Returns: 0
2: NOTE: You can safely ignore the above warning unless this call should not happen.  Do not suppress it by blindly adding an EXPECT_CALL() if you don't mean to enforce the call. >
2: 0
2: [       OK ] TransactionTest.InsufficientFunds (0 ms)
2: [ RUN      ] TransactionTest.SaveToDataBaseIsCalled
2: [       OK ] TransactionTest.SaveToDataBaseIsCalled (0 ms)
2: [----------] 7 tests from TransactionTest (0 ms total)
2: 
2: [----------] Global test environment tear-down
2: [==========] 12 tests from 2 test suites ran. (0 ms total)
2: [  PASSED  ] 12 tests.
2/2 Test #2: banking_tests ....................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```

```sh
$ gcovr -r .. --gcov-ignore-errors=no_working_dir_found --exclude '.*tests.*' --exclude '.*mocks.*' --exclude '.*print.hpp' --print-summary
```

```sh
(INFO) Reading coverage data...
(INFO) Writing coverage report...
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: ..
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
_build/CMakeFiles/3.28.3/CompilerIdCXX/CMakeCXXCompilerId.cpp
                                               9       0     0%   844,846-849,851,865-866,868
banking/Account.cpp                           13      13   100%
banking/Account.h                              1       1   100%
banking/Transaction.cpp                       33      33   100%
banking/Transaction.h                          1       1   100%
```

```sh
$ cd .github/workflows

$ nano ci.yml
```

Исправленный ci.yml:
```sh
name: CI

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4
        with:
          submodules: recursive

      - name: Install dependencies
        run: sudo apt-get update && sudo apt-get install -y cmake lcov gcovr libgtest-dev libgmock-dev

      - name: Configure CMake with coverage
        run: cmake -B _build -DBUILD_TESTS=ON -DCMAKE_CXX_FLAGS="--coverage -O0 -g -w"

      - name: Build
        run: cmake --build _build

      - name: Run tests
        working-directory: _build
        run: ctest --verbose

      - name: Install gcovr (if not already)
        run: sudo apt-get install -y gcovr

      - name: Collect coverage with gcovr
        working-directory: _build
        run: |
          gcovr -r .. --gcov-ignore-errors=no_working_dir_found \
            --filter '.*banking/.*' \
            --exclude '.*tests.*' \
            --exclude '.*mocks.*' \
            --exclude '.*print.hpp' \
            --xml coverage.xml
 - name: Upload coverage to Coveralls
        uses: coverallsapp/github-action@v2
        with:
          file: _build/coverage.xml
          repo-token: zXEE4h7x4nOKrgunhP3snjm140BLxsT7aoJb
```

```sh
$ git add .

$ git commit -n "Update files"

$ git push origin master
```

