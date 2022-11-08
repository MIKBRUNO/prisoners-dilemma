# tests gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable( ${TEST_NAME} "tests.cpp" "StrategyTests.cpp" )

target_link_libraries(
    ${TEST_NAME}
    GTest::gtest_main
    )
target_link_libraries(${TEST_NAME} ${LIB_NAME})

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
