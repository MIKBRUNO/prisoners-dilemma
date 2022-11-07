#include "../src/StrategyFactory.h"

int main(int argc, char* argv[]) {
	auto s = PrisonersDilemma::StrategyFactory::createStrategyByString("cooperate");
	if (s->decide() == PrisonersDilemma::Decision::COOPERATE)
		return 0;
	else
		return 1;
}
