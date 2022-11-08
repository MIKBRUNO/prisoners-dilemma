cmake_minimum_required (VERSION 2.8)
project (PrisonersDilemma)

set(EXEC_NAME dilemma)
set(LIB_NAME dillema_lib)
set(TEST_NAME tests)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # coverage; make coverage
	set(CMAKE_CXX_FLAGS "--coverage")
	set(STATIC_LIBRARY_FLAGS "--coverage")

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

endif(CMAKE_BUILD_TYPE STREQUAL "Debug")




add_subdirectory (src) 
add_subdirectory ("test")
