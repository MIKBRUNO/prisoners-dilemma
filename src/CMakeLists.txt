set(EXEC_NAME dilemma)
add_library(dillema_lib "Strategy.cpp" "Strategy.h"
"Simulation.cpp" "Simulation.h" "StrategyFactory.cpp" "StrategyFactory.h")
add_executable(${EXEC_NAME} main.cpp)
target_link_libraries(${EXEC_NAME} dillema_lib)