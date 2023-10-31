project("${EXECUTABLE_NAME}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 配置依赖 Qt 库
set(QT_COMPONENTS Core Gui Widgets)
set(OTHER_LIBS)

set(MAIN_DIR "${PROJECT_SOURCE_DIR}/Main")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/Test")
set(RESOURCES_DIR "${PROJECT_SOURCE_DIR}/Resources")
set(TRANSLATIONS_DIR "${RESOURCES_DIR}/Translations")

find_package(Qt5 COMPONENTS REQUIRED ${QT_COMPONENTS} LinguistTools)
list_add_prefix(QT_LIBS "Qt::" ${QT_COMPONENTS})

# 扫描本地化翻译文件
file(GLOB_RECURSE LOCALIZATION_FILES "${TRANSLATIONS_DIR}/*.ts")

# 自定义 Target: 本地化
list(LENGTH LOCALIZATION_FILES localizationFileNums)
if(localizationFileNums GREATER 0)
    qt5_create_translation(QM_FILES ${PROJECT_SOURCE_DIR} ${LOCALIZATION_FILES})
    add_custom_target(UpdateTranslation ALL DEPENDS ${QM_FILES})
endif()

# Target: 主程序
list_add_prefix(SRC_EXPRESSIONS "${MAIN_DIR}/" "*.ui" "*.c" "*.cpp" "*.hpp" "*.cc")
file(GLOB_RECURSE MAIN_SOURCES LIST_DIRECTORIES true ${SRC_EXPRESSIONS})
list(APPEND MAIN_SOURCES "${MAIN_DIR}")
foreach (item IN LISTS MAIN_SOURCES)
    if (IS_DIRECTORY ${item})
        list(APPEND MAIN_INCLUDE_DIR ${item})
        continue()
    endif()
    list(APPEND MAIN_SRC ${item})
endforeach()

add_library(MainLibrary STATIC ${MAIN_SRC} ${LOCALIZATION_FILES})
target_include_directories(MainLibrary PUBLIC ${MAIN_INCLUDE_DIR})
target_link_libraries(MainLibrary PUBLIC ${QT_LIBS} ${OTHER_LIBS})

# Target: 主程序入口
if (WIN32 AND ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_executable(${PROJECT_NAME} WIN32 EntryPoint.cpp)
else()
    add_executable(${PROJECT_NAME} EntryPoint.cpp)
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC MainLibrary)

# TODO 自动化测试
# if(ENABLE_TEST)
#     下载 GoogleTest 依赖
#     add_subdirectory(TEST_DIR)
# endif()
