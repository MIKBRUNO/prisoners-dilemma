set(TEST_SRC "tests.cpp")
add_executable(${TEST_NAME} ${TEST_SRC})
target_link_libraries(${TEST_NAME} ${LIB_NAME})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    # coverage; make coverage
    set(OBJECT_DIR ${CMAKE_BINARY_DIR}/test/CMakeFiles/${TEST_NAME}.dir 
            #${CMAKE_BINARY_DIR}/src/CMakeFiles/${LIB_NAME}.dir
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
        COMMAND lcov -t "${TEST_NAME}" -o ${TEST_NAME}.info -c -d ${OBJECT_DIR} --rc lcov_branch_coverage=1
        COMMAND genhtml -o report ${TEST_NAME}.info --rc lcov_branch_coverage=1;
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
        )

    add_dependencies(coverage ${TEST_NAME})

endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

enable_testing()

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
