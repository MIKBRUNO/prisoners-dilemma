#include <stdexcept>
#include "StrategyFactory.h"

namespace PrisonersDilemma {

	Strategy* StrategyFactory::createStrategyByString(const std::string& strat) {
		if (strat == "cooperate") {
			return new CooperateStartegy();
		}
		else {
			throw std::invalid_argument("bad strategy name");
		}
	}

}
