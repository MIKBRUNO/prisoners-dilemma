cmake_minimum_required (VERSION 3.14)
project (PrisonersDilemma)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(EXEC_NAME dilemma)
set(LIB_NAME dillema_lib)
set(TEST_NAME tests)

add_subdirectory (src) 

enable_testing()

add_subdirectory ("test")

