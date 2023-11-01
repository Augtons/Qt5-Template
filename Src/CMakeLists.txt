project("${EXECUTABLE_NAME}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(MAIN_DIR "${PROJECT_SOURCE_DIR}/Main")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/Test")
set(RESOURCES_DIR "${PROJECT_SOURCE_DIR}/Resources")
set(QRC_DIR "${RESOURCES_DIR}/Files")
set(TRANSLATIONS_DIR "${RESOURCES_DIR}/Translations")

find_package(Qt5 COMPONENTS REQUIRED ${QT_COMPONENTS} LinguistTools)
list_add_prefix(QT_LIBS "Qt::" ${QT_COMPONENTS})

# 扫描本地化翻译文件
set(LOCALE_PREFIX "${PROJECT_NAME}")
list(LENGTH QT_PROJECT_LOCALES localeNums)
if(localeNums LESS_EQUAL 0)
    list(APPEND QT_PROJECT_LOCALES "en_US")
endif()
foreach(locale IN LISTS QT_PROJECT_LOCALES)
    list(APPEND LOCALIZATION_FILES "${TRANSLATIONS_DIR}/${LOCALE_PREFIX}_${locale}.ts")
    list(APPEND quoted_locale_names "\"${locale}\"")
endforeach()
# 把所有 Locale 名转成 C 数组
list(JOIN quoted_locale_names ", " LOCALES_NAME_ARRAY)

# 自定义 Target: 本地化
qt5_create_translation(QM_FILES ${PROJECT_SOURCE_DIR} ${LOCALIZATION_FILES})
add_custom_target(UpdateTranslation ALL DEPENDS ${QM_FILES})

# 解析 *.qrc 资源文件
file(GLOB_RECURSE QRC_FILES "${QRC_DIR}/*.qrc")
file(GLOB_RECURSE BIG_QRC_FILES "${QRC_DIR}/*.big.qrc")
qt5_add_resources(RESOURCES_FILES ${QRC_FILES})
qt5_add_big_resources(BIG_RESOURCES_FILE ${BIG_QRC_FILES})

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
target_compile_definitions(MainLibrary PUBLIC -DLOCALE_PREFIX="${LOCALE_PREFIX}")
target_compile_definitions(MainLibrary PUBLIC -DLOCALES_NAME_ARRAY=${LOCALES_NAME_ARRAY})

# Target: 主程序入口
if (WIN32 AND ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_executable(${PROJECT_NAME} WIN32 EntryPoint.cpp ${RESOURCES_FILES} ${BIG_RESOURCES_FILE})
else()
    add_executable(${PROJECT_NAME} EntryPoint.cpp ${RESOURCES_FILES} ${BIG_RESOURCES_FILE})
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC MainLibrary)

# TODO 自动化测试
# if(ENABLE_TEST)
#     下载 GoogleTest 依赖
#     add_subdirectory(TEST_DIR)
# endif()
