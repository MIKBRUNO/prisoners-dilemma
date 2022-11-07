cmake_minimum_required (VERSION 2.8)
project (PrisonersDilemma)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "--coverage")
	set(STATIC_LIBRARY_FLAGS "--coverage --whole-archive")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

set(EXEC_NAME dilemma)
set(LIB_NAME dillema_lib)
set(TEST_NAME tests)





add_subdirectory (src) 
add_subdirectory ("test")
