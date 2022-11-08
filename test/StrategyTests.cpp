#include <gtest/gtest.h>
#include "../src/Simulation.h"

using namespace PrisonersDilemma;

TEST(StrategyTests, CooperateStartegyTest) {
	auto s = CooperateStartegy();
	ASSERT_EQ((s.decide()), Decision::COOPERATE);
}