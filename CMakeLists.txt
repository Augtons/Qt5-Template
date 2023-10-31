cmake_minimum_required(VERSION 3.16)

set(QT_PROJECT_NAME "PROJECT_NAME")
set(EXECUTABLE_NAME "HelloWorld")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project("${QT_PROJECT_NAME}")

file(GLOB_RECURSE MODULES "CMake/*.cmake")
foreach(item IN LISTS MODULES)
    include(${item})
endforeach()

add_subdirectory(Dependencies)
add_subdirectory(Src)
