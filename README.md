## Laboratory work VI

Данная лабораторная работа посвещена изучению средств пакетирования на примере **CPack**

```sh
$ open https://cmake.org/Wiki/CMake:CPackPackageGenerators
```

## Tasks

- [ ] 1. Создать публичный репозиторий с названием **lab06** на сервисе **GitHub**
- [ ] 2. Выполнить инструкцию учебного материала
- [ ] 3. Ознакомиться со ссылками учебного материала
- [ ] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```sh
$ export GITHUB_USERNAME=<имя_пользователя>

$ export GITHUB_EMAIL=<адрес_почтового_ящика>

$ alias edit=<nano|vi|vim|subl>

$ alias gsed=sed # for *-nix system
```

```sh
$ cd ${GITHUB_USERNAME}/workspace

$ pushd .

$ source scripts/activate
```

```sh
$ git clone https://github.com/misakontileev-stack/lab5.git projects/lab06
```

```sh
Клонирование в «projects/lab06»...
remote: Enumerating objects: 369, done.
remote: Counting objects: 100% (369/369), done.
remote: Compressing objects: 100% (181/181), done.
remote: Total 369 (delta 135), reused 359 (delta 125), pack-reused 0 (from 0)
Получение объектов: 100% (369/369), 1.52 МиБ | 5.12 МиБ/с, готово.
Определение изменений: 100% (135/135), готово.
```

```
$ cd projects/lab06

$ git remote remove origin

$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab06
```

```sh
$ gsed -i '/project(print)/a\

set(PRINT_VERSION_STRING "v\${PRINT_VERSION}")

' CMakeLists.txt

$ gsed -i '/project(print)/a\

set(PRINT_VERSION\

  \${PRINT_VERSION_MAJOR}.\${PRINT_VERSION_MINOR}.\${PRINT_VERSION_PATCH}.\${PRINT_VERSION_TWEAK})

' CMakeLists.txt

$ gsed -i '/project(print)/a\

set(PRINT_VERSION_TWEAK 0)

' CMakeLists.txt

$ gsed -i '/project(print)/a\

set(PRINT_VERSION_PATCH 0)

' CMakeLists.txt

$ gsed -i '/project(print)/a\

set(PRINT_VERSION_MINOR 1)

' CMakeLists.txt

$ gsed -i '/project(print)/a\

set(PRINT_VERSION_MAJOR 0)

' CMakeLists.txt

$ git diff

```

```sh
$ touch DESCRIPTION && nano DESCRIPTION
```

Вставляем такой текст:

```sh
Lab06 project: example of CPack usage.
```

```sh
$ touch ChangeLog.md

$ export DATE="`LANG=en_US date +'%a %b %d %Y'`"

$ cat > ChangeLog.md <<EOF

* ${DATE} ${GITHUB_USERNAME} <${GITHUB_EMAIL}> 0.1.0.0

- Initial RPM release

EOF
```

```sh
$ cat > CPackConfig.cmake <<EOF

include(InstallRequiredSystemLibraries)

EOF
```

```sh
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_PACKAGE_CONTACT ${GITHUB_EMAIL})

set(CPACK_PACKAGE_VERSION_MAJOR \${PRINT_VERSION_MAJOR})

set(CPACK_PACKAGE_VERSION_MINOR \${PRINT_VERSION_MINOR})

set(CPACK_PACKAGE_VERSION_PATCH \${PRINT_VERSION_PATCH})

set(CPACK_PACKAGE_VERSION_TWEAK \${PRINT_VERSION_TWEAK})

set(CPACK_PACKAGE_VERSION \${PRINT_VERSION})

set(CPACK_PACKAGE_DESCRIPTION_FILE \${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")

EOF
```

```sh
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RESOURCE_FILE_LICENSE \${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)

set(CPACK_RESOURCE_FILE_README \${CMAKE_CURRENT_SOURCE_DIR}/README.md)

EOF
```

```sh
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RPM_PACKAGE_NAME "print-devel")

set(CPACK_RPM_PACKAGE_LICENSE "MIT")

set(CPACK_RPM_PACKAGE_GROUP "print")

set(CPACK_RPM_CHANGELOG_FILE \${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)

set(CPACK_RPM_PACKAGE_RELEASE 1)

EOF
```

```sh
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")

set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")

set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

EOF
```

```sh
$ cat >> CPackConfig.cmake <<EOF

include(CPack)

EOF
```

```sh
$ cat >> CMakeLists.txt <<EOF

include(CPackConfig.cmake)

EOF
```

```sh
$ gsed -i 's/lab05/lab06/g' README.md
```

```sh
$ git add .

$ git commit -m"added cpack config"
```

```sh
[master e2eceaf] added cpack config
 6 files changed, 167 insertions(+), 800 deletions(-)
 create mode 100644 .README.md.swp
 create mode 100644 CPackConfig.cmake
 create mode 100644 ChangeLog.md
 create mode 100644 DESCRIPTION
```

```sh
$ git tag v0.1.0.0

$ git push origin master --tags
```

```sh
Username for 'https://github.com': misakontileev
Password for 'https://misakontileev@github.com': 
Перечисление объектов: 377, готово.
Подсчет объектов: 100% (377/377), готово.
При сжатии изменений используется до 4 потоков
Сжатие объектов: 100% (178/178), готово.
Запись объектов: 100% (377/377), 1.53 МиБ | 3.18 МиБ/с, готово.
Всего 377 (изменений 137), повторно использовано 368 (изменений 135), повторно использовано пакетов 0
remote: Resolving deltas: 100% (137/137), done.
To https://github.com/misakontileev-stack/lab06.git
 * [new branch]      master -> master
 * [new tag]         v0.1.0.0 -> v0.1.0.0
```

```sh
$ mkdir -p .github/workflows

$ nano .github/workflows/ci.yml
```

```sh
name: CI

on: [push, pull_request]  # Запускать при пуше и создании pull request

jobs:
  build:
    runs-on: ubuntu-latest  # Используем последнюю версию Ubuntu

    steps:
    - uses: actions/checkout@v4  # "Выкачиваем" код из репозитория

    - name: Configure
      run: cmake -B build -DCMAKE_BUILD_TYPE=Release

    - name: Build
      run: cmake --build build --config Release

    - name: Package with CPack
      run: cpack --config build/CPackConfig.cmake -G DEB  # Упаковываем в .deb

    - name: Upload Artifact
      uses: actions/upload-artifact@v4  # Сохраняем готовый пакет как артефакт сборки
      with:
        name: my-project-package
        path: build/*.deb
```

Создаем пустой файл

```sh
$ nano LICENSE
```

```sh
$ cmake -H. -B_build
```

```sh
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


-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/misha/misakontileev/workspace/projects/lab06/_build
```


```sh
$ cmake --build _build
```

```sh
[  7%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 15%] Linking CXX static library libformatter.a
[ 15%] Built target formatter
[ 23%] Building CXX object formatter_ex/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 30%] Linking CXX static library libformatter_ex.a
[ 30%] Built target formatter_ex
[ 38%] Building CXX object solver_lib/CMakeFiles/solver_lib.dir/solver.cpp.o
[ 46%] Linking CXX static library libsolver_lib.a
[ 46%] Built target solver_lib
[ 53%] Building CXX object hello_world/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 61%] Linking CXX executable hello_world
[ 61%] Built target hello_world
[ 69%] Building CXX object solver/CMakeFiles/solver.dir/equation.cpp.o
[ 76%] Linking CXX executable solver
[ 76%] Built target solver
[ 84%] Building CXX object banking/CMakeFiles/banking.dir/Account.cpp.o
[ 92%] Building CXX object banking/CMakeFiles/banking.dir/Transaction.cpp.o
[100%] Linking CXX static library libbanking.a
[100%] Built target banking
```

```sh
$ cd _build

$ cpack -G "TGZ"
```

```sh
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: lab05
CPack: - Install project: lab05 []
CPack: Create package
CPack: - package: /home/misha/misakontileev/workspace/projects/lab06/_build/lab05-0.1.1-Linux.tar.gz generated.
```

```sh
$ cd ..
```

```sh
$ cmake -H. -B_build -DCPACK_GENERATOR="TGZ"
```

```sh
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


-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/misha/misakontileev/workspace/projects/lab06/_build
```

```sh
$ cmake --build _build --target package
```

```sh
[ 15%] Built target formatter
[ 30%] Built target formatter_ex
[ 46%] Built target solver_lib
[ 61%] Built target hello_world
[ 76%] Built target solver
[100%] Built target banking
Run CPack packaging tool...
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: lab05
CPack: - Install project: lab05 []
CPack: Create package
CPack: - package: /home/misha/misakontileev/workspace/projects/lab06/_build/lab05-0.1.1-Linux.tar.gz generated.
```

```sh
$ mkdir artifacts

$ mv _build/*.tar.gz artifacts

$ tree artifacts
```

```sh
artifacts
└── lab05-0.1.1-Linux.tar.gz

1 directory, 1 file
```

## Report

```sh
$ popd

$ export LAB_NUMBER=06

$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}

$ mkdir reports/lab${LAB_NUMBER}

$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md

$ cd reports/lab${LAB_NUMBER}

$ edit REPORT.md

$ gist REPORT.md
```

## Homework

После того, как вы настроили взаимодействие с системой непрерывной интеграции,</br>
обеспечив автоматическую сборку и тестирование ваших изменений, стоит задуматься</br>
о создание пакетов для измениний, которые помечаются тэгами (см. вкладку [releases](https://github.com/tp-labs/lab06/releases)).</br>
Пакет должен содержать приложение _solver_ из [предыдущего задания](https://github.com/tp-labs/lab03#задание-1)
Таким образом, каждый новый релиз будет состоять из следующих компонентов:
- архивы с файлами исходного кода (`.tar.gz`, `.zip`)
- пакеты с бинарным файлом _solver_ (`.deb`, `.rpm`, `.msi`, `.dmg`)

В качестве подсказки:
```sh
$ cat .travis.yml
os: osx
script:
...
- cpack -G DragNDrop # dmg

$ cat .travis.yml
os: linux
script:
...
- cpack -G DEB # deb

$ cat .travis.yml
os: linux
addons:
  apt:
    packages:
    - rpm
script:
...
- cpack -G RPM # rpm

$ cat appveyor.yml
platform:
- x86
- x64
build_script:
...
- cpack -G WIX # msi
```

Для этого нужно добавить ветвление в конфигурационные файлы для **CI** со следующей логикой:</br>
если **commit** помечен тэгом, то необходимо собрать пакеты (`DEB, RPM, WIX, DragNDrop, ...`) </br>
и разместить их на сервисе **GitHub**. (см. пример для [Travi CI](https://docs.travis-ci.com/user/deployment/releases))</br>


Нужно в каждом подкорневом CMakeLists.txt поменять версию CMake на 3.10, чтобы проект собирался на MacOS.

Далее меняем ci.yml, там будет такой код:

```sh
name: Create Release Packages

on:
  push:
    tags:
      - 'v*'

jobs:
  build_linux:
    name: Build Linux packages (deb, rpm)
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Install RPM build tools
        run: sudo apt-get update && sudo apt-get install -y rpm

      - name: Configure CMake
        run: cmake -B build -DCMAKE_BUILD_TYPE=Release

      - name: Build
        run: cmake --build build --config Release

      - name: Package DEB
        run: cd build && cpack -G DEB -C Release

      - name: Package RPM
        run: cd build && cpack -G RPM -C Release

      - name: Upload Linux packages
        uses: actions/upload-artifact@v4
        with:
          name: linux-packages
          path: |
            build/*.deb
            build/*.rpm
  build_windows:
    name: Build Windows package (msi)
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v4

      - name: Configure CMake
        run: cmake -B build -DCMAKE_BUILD_TYPE=Release

      - name: Build
        run: cmake --build build --config Release

      - name: Package MSI (WIX)
        run: cd build && cpack -G WIX -C Release

      - name: Upload artifact
        uses: actions/upload-artifact@v4
        with:
          name: windows-package
          path: build/*.msi

  build_macos:
    name: Build macOS package (dmg)
    runs-on: macos-latest
    steps:
      - uses: actions/checkout@v4

      - name: Configure CMake
        run: cmake -B build -DCMAKE_BUILD_TYPE=Release

      - name: Build
        run: cmake --build build --config Release

      - name: Package DMG (DragNDrop)
        run: cd build && cpack -G DragNDrop -C Release

      - name: Upload artifact
        uses: actions/upload-artifact@v4
        with:
          name: macos-package
          path: build/*.dmg
   create_release:
    name: Create GitHub Release and upload assets
    needs: [build_linux, build_windows, build_macos]
    runs-on: ubuntu-latest
    permissions:
      contents: write
    steps:
      - name: Download all artifacts
        uses: actions/download-artifact@v4
        with:
          path: artifacts

      - name: List files
        run: ls -R artifacts

      - name: Create Release
        uses: softprops/action-gh-release@v2
        with:
          files: |
            artifacts/linux-packages/*.deb
            artifacts/linux-packages/*.rpm
            artifacts/windows-package/*.msi
            artifacts/macos-package/*.dmg
          draft: false
          prerelease: false
          generate_release_notes: true
```

Вставляем такой текст в LICENSE:

```sh
MIT License

Copyright (c) 2026 misakontileev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

И создаем LICENSE.rtf для WIX:

```sh
{\rtf1\ansi\deff0 {\fonttbl {\f0 Times New Roman;}}\f0\fs24
\b MIT License\b0\line
\line
Copyright (c) 2025 misakontileev\line
\line
Permission is hereby granted, free of charge, to any person obtaining a copy\line
of this software and associated documentation files (the "Software"), to deal\line
in the Software without restriction, including without limitation the rights\line
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\line
copies of the Software, and to permit persons to whom the Software is\line
furnished to do so, subject to the following conditions:\line
\line
The above copyright notice and this permission notice shall be included in all\line
copies or substantial portions of the Software.\line
\line
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\line
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\line
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\line
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\line
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\line
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\line
SOFTWARE.\line
}
```

И также нужно поменять одну строчку в CPackConfig.cmake, теперь он такой:

```sh
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_CONTACT "misakontileev@gmail.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION ${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Quadratic equation solver")

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.rtf)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

# Для RPM
set(CPACK_RPM_PACKAGE_NAME "solver")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
set(CPACK_RPM_CHANGELOG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)

# Для DEB
set(CPACK_DEBIAN_PACKAGE_NAME "solver")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_CONTACT})
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Command-line quadratic equation solver")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

# Для Windows (WIX) и macOS (dragndrop) – общие настройки
set(CPACK_GENERATOR "ZIP;TGZ")   # базовые архивы, для конкретных платформ переопределим в CI

include(CPack)
```

И загружаем все на GitHub:

```sh
$ git add .

$ git commit -m "Update files"
```

```sh
[master 9eaa3f5] Update files
 4 files changed, 49 insertions(+), 10 deletions(-)
 create mode 100644 LICENSE.rtf
```

```sh
$ git push origin master
```

```sh
Username for 'https://github.com': misakontileev
Password for 'https://misakontileev@github.com': 
Перечисление объектов: 14, готово.
Подсчет объектов: 100% (14/14), готово.
При сжатии изменений используется до 4 потоков
Сжатие объектов: 100% (6/6), готово.
Запись объектов: 100% (8/8), 1.37 КиБ | 1.37 МиБ/с, готово.
Всего 8 (изменений 4), повторно использовано 0 (изменений 0), повторно использовано пакетов 0
remote: Resolving deltas: 100% (4/4), completed with 3 local objects.
To https://github.com/misakontileev-stack/lab06.git
   6a136ca..9eaa3f5  master -> master
```

И создаем тэг:

```sh
$ git tag v1.0.4
```

```sh
$ git push origin v1.0.4
```

```sh
Username for 'https://github.com': misakontileev
Password for 'https://misakontileev@github.com': 
Всего 0 (изменений 0), повторно использовано 0 (изменений 0), повторно использовано пакетов 0
To https://github.com/misakontileev-stack/lab06.git
 * [new tag]         v1.0.4 -> v1.0.4
```

```
Copyright (c) 2015-2021 The ISC Authors
```
