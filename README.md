# Qt 5 CMake 工程模板
支持:

- 自动生成本地化语言文件 (`*.qm`)
- 资源文件 (`*.qrc`) 管理
- 集成自动化测试 (`Google Test`)，默认关闭，可手动启动

**目录：**

- [一、创建工程](#一创建工程)
  - [1、基本](#1基本)
  - [2、【可选】添加资源文件](#2可选添加资源文件)
  - [3、【可选】使用 Qt 语言家进行本地化](#3可选使用-qt-语言家进行本地化)
- [二、自动化测试](#二自动化测试-google-test)
  - [1、启用单元测试](#1启用单元测试)
  - [2、编写单元测试](#2编写单元测试)
  - [3、运行单元测试](#3运行单元测试)

# 一、创建工程
## 1、基本
**1. 克隆本仓库**

**2. 设置工程名，可执行文件名，依赖库**

在工程根目录的 `/CMakeLists.txt`

```cmake
set(QT_PROJECT_NAME "<你的工程名>")
set(EXECUTABLE_NAME "<你的主可执行文件名>")

# Qt 子模块会被以 Qt:: 为前缀，用 target_link_libraries 添加到 target
# 中括号部分可不填，如你的工程不需要三方库，则直接 set(OTHER_LIBS)
set(QT_COMPONENTS [<QT子模块> ...])
set(OTHER_LIBS [<你的三方库> ...])
```
例如
```cmake
# 工程名
set(QT_PROJECT_NAME "ProjectName")

# 可执行文件名
set(EXECUTABLE_NAME "ProjectNameApp")

# 依赖的 Qt 模块
set(QT_COMPONENTS Core Gui Widgets)

# 依赖的三方库
set(OTHER_LIBS OpenSSL)
```

**3. 编写程序本体**

按照本项目规范，程序本体的源文件应该在 `/Src/Main` 及其子目录下。
构建系统会自动扫描其下的源文件，头文件目录，添加到构建系统。
这些源代码将允许入口点调用，也支持单元测试中调用。

你可以使用 `QtCreator` 的 UI 设计器，把 `*.ui` 文件放进去，构建系统会生成对应的 UI 代码。

整个应用程序的入口点在 `/Src/EntryPoint.cpp` 下。

> 之所以这样设计，分离入口点，是为了更好地适配单元测试。

## 2、【可选】添加资源文件
按照本工程的规范，请放置资源文件到 `/Src/Resources/Files` 下，**支持自由创建子目录进行分组**。

之后请按照 Qt 规范，编写 `qrc` 文件，或者用 `QtCreator` 生成，放到此处或其任意子目录下。
**构建系统会自动扫描所有 `qrc` 文件**并添加到构建系统。

`qrc` 文件中所有 `file` 字段的路径，既支持以 `qrc` 文件的相对路径填写，也支持以对应文件绝对路径填写。

Qt 的资源文件有两种方式，一种是集成到代码里，另一种是生成独立的二进制文件。
前者适用于较小的文件，**后者适用于较大的文件**。

在本工程里，你可以指定 `*.qrc` 和 `*.big.qrc` **两种格式**的 `qrc`，本项目的 CMake 会分别扫描，并分别按两种方式编译资源。

**对于大文件，推荐使用 `*.big.qrc`！**

> 你也可以修改 `/Src/CMakeLists.txt` 的 `set` 来更改规定的资源文件扫描目录

## 3、【可选】使用 Qt 语言家进行本地化

在工程根目录的 `/CMakeLists.txt` 中，声明工程所需本地化的语言

> 你也可以对此功能视而不见，而直接把你想要的语言放到源码里和 UI 设计文件里，测试正常即可。

```cmake
set(QT_PROJECT_LOCALES "zh_CN" "en_US")
```

构建一次项目，即可在 `/Src/Resources/Translations` 下生成 `*.ts (xml)` 文件，即翻译文件
可用 Qt 语言家 (`Linguist`) 软件进行编辑。

你可使用本项目自动生成的名为 `UpdateTranslation` 的 CMake Target 进行更新翻译。

# 二、自动化测试 (Google Test)
## 1、启用单元测试
在工程根目录的 `/CMakeLists.txt`
```cmake
option(ENABLE_TEST "Enable Unit Test" OFF)
```
然后设置 Google Test 的仓库和版本
在工程根目录的 `/Src/Test/CMakeLists.txt`

```cmake
set(GOOGLE_TEST_REPO "https://github.com/google/googletest.git")
set(GOOGLE_TEST_VERSION "v1.14.0")
```

## 2、编写单元测试
按照本项目规范，程序本体的源文件应该在 `/Src/Test` 及其子目录下。构建系统会自动扫描。

## 3、运行单元测试
使用支持 CMake 单元测试的 IDE 运行单元测试 (如 CLion, QtCreator)

或直接构建 `<可执行文件名>_Test` 这个 Target，
然后直接运行测试对应的可执行文件，或通过 Google Test 的 filter 指定运行的测试。
