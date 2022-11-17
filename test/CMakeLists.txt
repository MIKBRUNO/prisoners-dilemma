if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    # coverage; make coverage
	set(CMAKE_CXX_FLAGS "--coverage ${CMAKE_CXX_FLAGS}")
	set(STATIC_LIBRARY_FLAGS "--coverage ${STATIC_LIBRARY_FLAGS}")

    set(OBJECT_DIR -d ${CMAKE_BINARY_DIR}/test/CMakeFiles/${TEST_NAME}.dir 
            -d ${CMAKE_BINARY_DIR}/src/CMakeFiles/${LIB_NAME}.dir
        )
    add_custom_target(
        coverage
        COMMAND mkdir -p coverage
        COMMAND ${CMAKE_MAKE_PROGRAM}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    add_custom_command(
        TARGET coverage
        COMMAND echo "=================== COVERAGE ===================="
        COMMAND lcov -t "${TEST_NAME}" -o ${TEST_NAME}.info -c ${OBJECT_DIR} --rc lcov_branch_coverage=1
        COMMAND genhtml -o report ${TEST_NAME}.info --rc lcov_branch_coverage=1;
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
        )

    add_dependencies(coverage ${TEST_NAME})

endif(CMAKE_BUILD_TYPE STREQUAL "Coverage")

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

add_executable( ${TEST_NAME} "tests.cpp" "StrategyTests.cpp" )
target_link_libraries(
    ${TEST_NAME}
    GTest::gtest_main
    )
target_link_libraries(${TEST_NAME} ${LIB_NAME})

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
