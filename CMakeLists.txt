cmake_minimum_required (VERSION 2.8)
project (PrisonersDilemma)

set(EXEC_NAME dilemma)
set(LIB_NAME dillema_lib)
set(TEST_NAME tests)

add_subdirectory (src) 

enable_testing()

add_subdirectory ("test")

