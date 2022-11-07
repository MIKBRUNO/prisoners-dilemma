add_library(${LIB_NAME} "Strategy.cpp" "Strategy.h"
"Simulation.cpp" "Simulation.h" "StrategyFactory.cpp" "StrategyFactory.h")
add_executable(${EXEC_NAME} main.cpp)
target_link_libraries(${EXEC_NAME} ${LIB_NAME})