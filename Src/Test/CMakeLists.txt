set(GOOGLE_TEST_REPO "https://github.com/google/googletest.git")
set(GOOGLE_TEST_VERSION "v1.14.0")

message("Enable Google Test")
include(FetchContent)

# 下载 Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY  ${GOOGLE_TEST_REPO}
    GIT_TAG         ${GOOGLE_TEST_VERSION}
)
set(gtest_force_shared_crt ON CACHE BOOL "gtest_force_shared_crt" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Target: 测试程序入口
set(TEST_SRC_EXPRESSIONS "*.ui" "*.c" "*.cpp" "*.hpp" "*.cc")
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true ${TEST_SRC_EXPRESSIONS})
list(APPEND TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})
foreach (item IN LISTS TEST_SOURCES)
    if (IS_DIRECTORY ${item})
        list(APPEND TEST_INCLUDE_DIR ${item})
        continue()
    endif()
    list(APPEND TEST_SRC ${item})
endforeach()

add_executable(${PROJECT_NAME}_Test ${TEST_SRC} ${LOCALIZATION_FILES} ${RESOURCES_FILES} ${BIG_RESOURCES_FILE})
target_include_directories(${PROJECT_NAME}_Test PUBLIC ${TEST_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}_Test PUBLIC MainLibrary GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_Test)
