cmake_minimum_required (VERSION 2.8)
project (PrisonersDilemma)
add_subdirectory (src) 
add_subdirectory (test)

# enable_testing ()
# add_test (NAME MyTest COMMAND Test)

# # executable
# set(EXEC_NAME dilemma)
# set(
#     SOURCES
    
#     )

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")

#     # coverage; make coverage
#     set(CMAKE_CXX_FLAGS_DEBUG "--coverage")
#     set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/${EXEC_NAME}.dir)
#     add_custom_target(
#         coverage
#         COMMAND mkdir -p coverage
#         COMMAND ${CMAKE_MAKE_PROGRAM}
#         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#         )
#     add_custom_command(
#         TARGET coverage
#         COMMAND echo "=================== COVERAGE ===================="
#         COMMAND lcov -t "${EXEC_NAME}" -o ${EXEC_NAME}.info -c -d ${OBJECT_DIR} --rc lcov_branch_coverage=1
#         COMMAND genhtml -o report ${EXEC_NAME}.info --rc lcov_branch_coverage=1;
#         COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
#         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
#         )

#     add_dependencies(coverage ${EXEC_NAME})

# endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

# # tests gtest
# include(FetchContent)
# FetchContent_Declare(
#         googletest
#         GIT_REPOSITORY https://github.com/google/googletest.git
#         GIT_TAG release-1.12.1
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# enable_testing()

# add_executable(${EXEC_NAME} ${SOURCES})

# target_link_libraries(
#     ${EXEC_NAME}
#     GTest::gtest_main
#     )

# include(GoogleTest)
# gtest_discover_tests(${EXEC_NAME})

# # ${CMAKE_BINARY_DIR}/CMakeFiles/tester.dir/
