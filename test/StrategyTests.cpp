#include <gtest/gtest.h>
#include "../src/Simulation.h"

using namespace PrisonersDilemma;

TEST(StrategyTests, CooperateStartegyTest) {
	auto s = CooperateStrategy();
	std::vector<std::array<Decision, 3>> history;
	std::array<Strategy*, 3> competitors = {nullptr, nullptr, nullptr};
	ASSERT_EQ((s.decide(history, competitors)), Decision::COOPERATE);
}

TEST(StrategyTests, GoByMajorityStrategyTest) {
	auto s = GoByMajorityStrategy();
	std::array<Strategy*, 3> competitors = {&s, nullptr, nullptr};
	std::vector<std::array<Decision, 3>> history;
	ASSERT_EQ((s.decide(history, competitors)), Decision::COOPERATE);
	history = {
		{Decision::DEFECT, Decision::COOPERATE, Decision::COOPERATE}
	};
	ASSERT_EQ((s.decide(history, competitors)), Decision::COOPERATE);
	history = {
		{Decision::COOPERATE, Decision::DEFECT, Decision::DEFECT},
		{Decision::DEFECT, Decision::COOPERATE, Decision::DEFECT}
	};
	ASSERT_EQ((s.decide(history, competitors)), Decision::DEFECT);
}
