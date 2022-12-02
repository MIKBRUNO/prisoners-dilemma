#include <gtest/gtest.h>
#include <vector>
#include <cstring>
#include "../src/Simulation.h"
#include "../src/StrategyFactory.h"

using namespace PrisonersDilemma;
using namespace std;

TEST(PrisonerTest, SimTest) {
    vector<Decision> h;
    Prisoner p("prisoner1", "cooperate");
    Strategy* coop = StrategyFactory::createStrategyByString(p.getStrategy().name());
    ASSERT_TRUE(0 == strcmp(p.name().c_str(), "prisoner1"));
    ASSERT_TRUE(0 == strcmp(coop->name(), "cooperate"));
    ASSERT_EQ(coop->decide(h, h, h), p.decide(h, h, h));
    Prisoner pp (p);
    ASSERT_TRUE(pp.name() == p.name().c_str());
    Prisoner ppp (move(p));
}
