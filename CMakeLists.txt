cmake_minimum_required (VERSION 2.8)
project (PrisonersDilemma)

set(EXEC_NAME dilemma)
set(LIB_NAME dillema_lib)
set(TEST_NAME tests)

add_subdirectory (src) 
add_subdirectory ("test")


enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
